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

#include "logger.h"
#include "renderer.h"

#include <string.h>

static const dnf_input_system_handler *input;

static float32_t x = 90, y = 90;
static float32_t speed = 200;

static const renderer_context *render_ctx;

void clear_framebuffer(const dnf_framebuffer *fb, Color color)
{
    memset(fb->pixels, 0x000f, fb->width * fb->height * sizeof(Color));
}

bool8_t dnf_game_init(game *game_instance)
{
    input = game_instance->input_handler;

    render_ctx = game_instance->renderer_context;

    return true;
}

bool8_t dnf_game_update(game *game_instance, float32_t dt)
{
    if (input->is_held(DNF_GAME_ACTION_MOVE_FORWARD))
        y = y - speed * dt;
    if (input->is_held(DNF_GAME_ACTION_MOVE_BACKWARD))
        y = y + speed * dt;
    if (input->is_held(DNF_GAME_ACTION_MOVE_LEFT))
        x = x - speed * dt;
    if (input->is_held(DNF_GAME_ACTION_MOVE_RIGHT))
        x = x + speed * dt;

    return true;
}

bool8_t dnf_game_render(game *game_instance, float32_t dt)
{
    // we will draw directly to the framebuffer
    const dnf_framebuffer *fb = &(render_ctx->framebuffer);
    clear_framebuffer(fb, BLACK);

    const int32_t ix = x;
    // game drawing logic
    const int32_t iy = y;
    const int32_t i = ix < 0 ? 0 : ix > fb->width ? fb->width : ix;
    const int32_t j = iy < 0 ? 0 : iy > fb->height ? fb->height : iy;
    fb->pixels[j * fb->width + i] = RED;

    renderer_begin_frame(render_ctx);

    // UI Logic

    renderer_end_frame(render_ctx);


    return true;
}

void dnf_game_resize(game *game_instance, int32_t new_width, int32_t new_height)
{
    renderer_resize_window(game_instance->renderer_context, new_width, new_height);
}
