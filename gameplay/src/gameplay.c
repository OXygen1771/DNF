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
    if (core_input_action_is_pressed(input_handler, DNF_GAME_ACTION_ATTACK1))
        printf("MOUSE1 PRESSED\n");

    if (core_input_action_is_held(input_handler, DNF_GAME_ACTION_ATTACK1))
        printf("MOUSE1 HELD\n");

    if (core_input_action_is_released(input_handler, DNF_GAME_ACTION_ATTACK1))
        printf("MOUSE1 RELEASED\n");
}
