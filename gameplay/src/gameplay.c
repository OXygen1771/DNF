// DNF (Doomed and Forgotten): a DOOM-style first-person shooter.
// Copyright (C) 2025  Alexandr Gorbatenko
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


#include "gameplay.h"

#include "input_system.h"

#include <stdio.h>


void gameplay_update(float dt, const DNF_InputSystemHandler *input_handler)
{
    const Vector2 mouse_pos = input_handler->mouse_pos;
    const Vector2 mouse_pos_delta = input_handler->mouse_pos_delta;
    const Vector2 mouse_wheel_delta = input_handler->mouse_wheel_delta;

    if (core_input_action_is_pressed(input_handler, DNF_GAME_ACTION_ATTACK1))
        printf("MOUSE1 PRESSED\n");

    if (core_input_action_is_held(input_handler, DNF_GAME_ACTION_ATTACK1))
        printf("MOUSE1 HELD\n");

    if (core_input_action_is_released(input_handler, DNF_GAME_ACTION_ATTACK1))
        printf("MOUSE1 RELEASED\n");

    if (core_input_action_is_held(input_handler, DNF_GAME_ACTION_MOVE_FORWARD))
        printf("(%4f, %4f)\n", mouse_pos.x, mouse_pos.y);

    if (core_input_action_is_held(input_handler, DNF_GAME_ACTION_MOVE_BACKWARD))
        printf("(%4f, %4f)\n", mouse_pos_delta.x, mouse_pos_delta.y);

    if (core_input_action_is_held(input_handler, DNF_GAME_ACTION_MOVE_LEFT))
        printf("(%4f, %4f)\n", mouse_wheel_delta.x, mouse_wheel_delta.y);
}
