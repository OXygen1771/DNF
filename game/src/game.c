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


static dnf_input_system_handler *input;
static int32_t x, y = 120;

static float32_t speed = 64;

static bool8_t pressed = false;

bool8_t dnf_game_init(game *game_instance)
{
    input = game_instance->input_handler;

    return true;
}

bool8_t dnf_game_update(game *game_instance, float32_t dt)
{
    if (input->is_pressed(DNF_GAME_ACTION_ATTACK1))
        pressed = true;
    else
        pressed = false;

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
    for (int32_t i = x - 4; i < x + 4; i++)
        for (int32_t j = y - 4; j < y + 4; j++)
            core_renderer_draw_pixel(
                i + x, j + y,
                pressed ? RED : WHITE);

    core_renderer_render();
    return true;
}

void dnf_game_resize(game *game_instance, uint32_t new_width, uint32_t new_height)
{  }
