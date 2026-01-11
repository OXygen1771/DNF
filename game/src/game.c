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


#include "game.h"

#include "game_render.h"

#include "logger.h"

#include <raymath.h>

#include <stdlib.h>


static const dnf_input_system_handler *input;

static dnf_game_state *state;
static player_t *player;

static map_data_t map;


sector_t load_sectors[] = {
    {0, 4, 0, 40},
    {4, 8, 0, 40},
    {8, 12, 0, 40},
    {12, 16, 0, 40},
    {16, 20, 0, 80},
};

wall_t load_walls[] = {
    {{100, 132}, {132, 132}, RED},
    {{132, 132}, {132, 100}, MAROON},
    {{132, 100}, {100, 100}, RED},
    {{100, 100}, {100, 132}, MAROON},

    {{164, 132}, {196, 132}, YELLOW},
    {{196, 132}, {196, 100}, GOLD},
    {{196, 100}, {164, 100}, YELLOW},
    {{164, 100}, {164, 132}, GOLD},

    {{164, 196}, {196, 196}, GREEN},
    {{196, 196}, {196, 164}, LIME},
    {{196, 164}, {164, 164}, GREEN},
    {{164, 164}, {164, 196}, LIME},

    {{100, 196}, {132, 196}, PURPLE},
    {{132, 196}, {132, 164}, VIOLET},
    {{132, 164}, {100, 164}, PURPLE},
    {{100, 164}, {100, 196}, VIOLET},

    // non-convex
    {{250, 250}, {400, 250}, BLUE},
    {{400, 250}, {270, 270}, DARKBLUE},
    {{270, 270}, {250, 400}, BLUE},
    {{250, 400}, {250, 250}, DARKBLUE}
};


bool8_t dnf_game_init(game *game_instance)
{
    input = game_instance->input_handler;

    if (!init_renderer(game_instance))
    {
        DNF_FATAL("Failed to initialize game renderer!");
        return false;
    }

    state = game_instance->game_state;
    player = &state->player;

    player->pos = (Vector3){
        .x = 120,
        .y = 150,
        .z = 30
    };
    player->cam_dir = (Vector2){
        .x = PI,
        .y = 0
    };
    DNF_DEBUG(
        "Initialized player: (%f, %f, %f), camera (%f, %f)",
        player->pos.x, player->pos.y, player->pos.z,
        player->cam_dir.x, player->cam_dir.y);

    constexpr uint32_t wall_per_sector = 5;
    constexpr uint32_t sector_n = 5;

    map.wall_count = wall_per_sector;
    map.sector_count = sector_n;
    map.walls = malloc(sizeof(wall_t) * wall_per_sector * sector_n);
    map.sectors = malloc(sizeof(sector_t) * sector_n);

    for (uint32_t s = 0; s < sector_n; s++)
    {
        map.sectors[s].wall_start = load_sectors[s].wall_start;
        map.sectors[s].wall_end = load_sectors[s].wall_end;
        map.sectors[s].base_level = load_sectors[s].base_level;
        map.sectors[s].height = load_sectors[s].height;

        Vector2 center = {0, 0};

        for (uint32_t w = map.sectors[s].wall_start; w < map.sectors[s].wall_end; w++)
        {
            map.walls[w].start = load_walls[w].start;
            map.walls[w].end = load_walls[w].end;
            map.walls[w].color = load_walls[w].color;

            center.x += (map.walls[w].start.x + map.walls[w].end.x) / 2;
            center.y += (map.walls[w].start.y + map.walls[w].end.y) / 2;
        }
        center.x /= (float32_t)(map.sectors[s].wall_end - map.sectors[s].wall_start);
        center.y /= (float32_t)(map.sectors[s].wall_end - map.sectors[s].wall_start);

        map.sectors[s].center = center;
    }

    state->map = map;

    DNF_DEBUG("Initialized map!");

    return true;
}

bool8_t dnf_game_update(game *game_instance, float32_t dt)
{
    // restrict movement
    player->pos.x = player->pos.x < 20 ? 20 : player->pos.x > 600 ? 600 : player->pos.x;
    player->pos.y = player->pos.y < 20 ? 20 : player->pos.y > 450 ? 450 : player->pos.y;

    constexpr float32_t speed = 100;
    constexpr float32_t rot_speed = 0.02f;

    // TODO: rotate player with mouse movements
    // rotate right
    if (input->is_held(DNF_GAME_ACTION_ATTACK2))
    {
        player->cam_dir.x -= rot_speed;
        if (player->cam_dir.x < -TAU)
            player->cam_dir.x += TAU;
    }
    // rotate left
    else if (input->is_held(DNF_GAME_ACTION_ATTACK1))
    {
        player->cam_dir.x += rot_speed;
        if (player->cam_dir.x > TAU)
            player->cam_dir.x -= TAU;
    }

    // move in the direction of the camera
    const float32_t dx = sinf(player->cam_dir.x) * speed * dt;
    const float32_t dy = cosf(player->cam_dir.x) * speed * dt;

    if (input->is_held(DNF_GAME_ACTION_MOVE_FORWARD))
    {
        player->pos.x += dx;
        player->pos.y += dy;
    }
    else if (input->is_held(DNF_GAME_ACTION_MOVE_BACKWARD))
    {
        player->pos.x -= dx;
        player->pos.y -= dy;
    }

    if (input->is_held(DNF_GAME_ACTION_MOVE_LEFT))
    {
        player->pos.x += dy;
        player->pos.y -= dx;
    }
    else if (input->is_held(DNF_GAME_ACTION_MOVE_RIGHT))
    {
        player->pos.x -= dy;
        player->pos.y += dx;
    }

    if (input->is_held(DNF_GAME_ACTION_MOVE_UP))
        player->pos.z += speed * dt;
    else if (input->is_held(DNF_GAME_ACTION_MOVE_DOWN))
        player->pos.z -= speed * dt;

    return true;
}

bool8_t dnf_game_render(game *game_instance, float32_t dt)
{
    return draw_game(state, dt);
}
