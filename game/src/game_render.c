// DNF (Doomed and Forgotten): a DOOM-style first-person shooter.
// Copyright (C) 2025-2026  Alexandr Gorbatenko
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.


#include "game_render.h"

#include "logger.h"

#include <raymath.h>

#include <stdlib.h>
#include <string.h>


static dnf_renderer_api rapi;
static const renderer_context *ctx;
static const dnf_framebuffer *fb;

static int32_t SW2;
static int32_t SH2;

static constexpr float32_t scale = 200;


bool8_t init_renderer(const game *game_instance)
{
    rapi = game_instance->renderer_api;
    ctx = game_instance->renderer_context;
    fb = &ctx->framebuffer;

    SW2 = fb->width / 2;
    SH2 = fb->height / 2;

    return true;
}

/**
 * @brief Clears the framebuffer with a dark-blue color.
 */
void clear_framebuffer()
{
    memset(fb->pixels, 0x50, sizeof(Color) * fb->width * fb->height);
}

float32_t distance(
    const float32_t x1,
    const float32_t y1,
    const float32_t x2,
    const float32_t y2)
{
    return sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

int32_t compare_sectors(const void *a, const void *b)
{
    const sector_t *s1 = (const sector_t *)a;
    const sector_t *s2 = (const sector_t *)b;

    if (s1->z_depth > s2->z_depth) return -1;
    if (s1->z_depth < s2->z_depth) return 1;
    return 0;
}

void draw_player_top(const player_t *player)
{
    const int32_t px = (int32_t)player->pos.x;
    const int32_t py = (int32_t)player->pos.y;

    const int32_t dir_x = px + (int32_t)(20 * sinf(player->cam_dir.x));
    const int32_t dir_y = py + (int32_t)(20 * cosf(player->cam_dir.x));

    for (int32_t y = -2; y < 2; y++)
        for (int32_t x = -2; x < 2; x++)
            fb->pixels[(y + py) * fb->width + (x + px)] = RED;

    fb->pixels[dir_y * fb->width + dir_x] = RED;
}

void draw_wall(
    const wall_t wall,
    const player_t *player,
    const float32_t view_cos,
    const float32_t view_sin,
    const float32_t sec_base_level,
    const float32_t sec_height)
{
    // world space to camera space
    // translation
    const float32_t x1 = wall.start.x - player->pos.x;
    const float32_t y1 = wall.start.y - player->pos.y;
    const float32_t x2 = wall.end.x - player->pos.x;
    const float32_t y2 = wall.end.y - player->pos.y;

    // rotation
    float32_t tx1 = x1 * view_cos - y1 * view_sin;
    float32_t ty1 = y1 * view_cos + x1 * view_sin;
    float32_t tx2 = x2 * view_cos - y2 * view_sin;
    float32_t ty2 = y2 * view_cos + x2 * view_sin;

    // near clipping
    constexpr float32_t near_z = 0.1f;  // clipping plane near player
    if (ty1 < near_z && ty2 < near_z) return;
    if (ty1 < near_z || ty2 < near_z)
    {
        // clipping coefficient
        const float32_t t = (near_z - ty1) / (ty2 - ty1);
        if (ty1 < near_z)
        {
            tx1 = tx1 + t * (tx2 - tx1);
            ty1 = near_z;
        }
        else if (ty2 < near_z)
        {
            tx2 = tx1 + t * (tx2 - tx1);
            ty2 = near_z;
        }
    }

    // camera space to screen space
    const float32_t sx_b_proj = tx1 * scale / ty1;
    const float32_t ex_b_proj = tx2 * scale / ty2;

    const int32_t sx_b =  SW2 - (int32_t)sx_b_proj;
    const int32_t ex_b =  SW2 - (int32_t)ex_b_proj;

    if (sx_b >= ex_b) return;  // back of the wall

    // height
    const float32_t sz_b = sec_base_level - player->pos.z;
    const float32_t sz_t = sz_b + sec_height;

    const float32_t sy_b = (float32_t)SH2 - (sz_b * scale / ty1);
    const float32_t sy_t = (float32_t)SH2 - (sz_t * scale / ty1);
    const float32_t ey_b = (float32_t)SH2 - (sz_b * scale / ty2);
    const float32_t ey_t = (float32_t)SH2 - (sz_t * scale / ty2);

    // clip x
    int32_t x_min = sx_b;
    int32_t x_max = ex_b;
    if (x_min < 1) x_min = 1;
    if (x_max > fb->width - 1) x_max = fb->width - 1;

    // draw the wall
    const float32_t dx = (float32_t)(ex_b - sx_b);
    if (dx <= 0) return;

    for (int32_t x = x_min; x < x_max; x++)
    {
        // interpolation factor for current x
        const float32_t factor = (float32_t)(x - sx_b) / dx;

        // linear interpolation for y
        int32_t y_b = (int32_t)(sy_b + factor * (ey_b - sy_b));
        int32_t y_t = (int32_t)(sy_t + factor * (ey_t - sy_t));

        // clip y
        if (y_t < 1) y_t = 1;
        if (y_b > fb->height - 1) y_b = fb->height - 1;

        // draw the wall
        for (int32_t y = y_t; y <= y_b; y++)
            fb->pixels[y * fb->width + x] = wall.color;
    }
}

void draw_3D(const player_t *player, const map_data_t *map)
{
    const float32_t p_cos = cosf(player->cam_dir.x);
    const float32_t p_sin = sinf(player->cam_dir.x);

    // sort sectors by depth (distance from player)
    for (uint32_t s = 0; s < map->sector_count; s++)
        map->sectors[s].z_depth = distance(
            player->pos.x, player->pos.y,
            map->sectors[s].center.x, map->sectors[s].center.y);
    qsort(map->sectors, map->sector_count, sizeof(sector_t), compare_sectors);

    // draw sectors
    for (uint32_t s = 0; s < map->sector_count; s++)
    {
        const sector_t *sec = &map->sectors[s];

        for (uint32_t w = sec->wall_start; w < sec->wall_end; w++)
            draw_wall(map->walls[w], player, p_cos, p_sin,
                sec->base_level, sec->height);
    }
}

bool8_t draw_game(const dnf_game_state *game_state, const float32_t dt)
{
    // game drawing logic (framebuffer manipulation)
    clear_framebuffer();

    // real drawing
    draw_3D(&game_state->player, &game_state->map);

    // debug draw mode
    draw_player_top(&game_state->player);


    renderer_begin_frame(ctx);
    // UI drawing logic
    rapi.draw_text("DNF TEST", 10, 10, 24, GREEN);
    rapi.draw_fps(10, 40);
    renderer_end_frame(ctx);

    return true;
}
