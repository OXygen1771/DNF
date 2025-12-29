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


#include "input_system.h"

#include "raylib.h"


void core_input_system_init(DNF_InputSystemHandler* handler)
{
    // default keybinds
    handler->keybind_LUT[DNF_GAME_ACTION_MOVE_FORWARD] = KEY_W;
    handler->keybind_LUT[DNF_GAME_ACTION_MOVE_BACKWARD] = KEY_S;
    handler->keybind_LUT[DNF_GAME_ACTION_MOVE_LEFT] = KEY_A;
    handler->keybind_LUT[DNF_GAME_ACTION_MOVE_RIGHT] = KEY_D;

    handler->keybind_LUT[DNF_GAME_ACTION_INTERACT] = KEY_E;

    handler->keybind_LUT[DNF_GAME_ACTION_ATTACK1] = MOUSE_BUTTON_LEFT;
    handler->keybind_LUT[DNF_GAME_ACTION_ATTACK2] = MOUSE_BUTTON_RIGHT;

    for (int i = 0; i < DNF_GAME_ACTION_COUNT; i++)
        handler->action_states[i] = DNF_INPUT_STATE_IDLE;
}

void core_input_update(DNF_InputSystemHandler *handler)
{
    // iterating from 1 because ACTION_NONE is bound to 0 = IDLE
    for (int i = 1; i < DNF_GAME_ACTION_COUNT; i++)
    {
        // get the current key state
        bool current_down = false;
        // TODO: this WILL NOT support binding attack actions to the keyboard
        if (i <= DNF_GAME_ACTION_INTERACT)
            current_down = IsKeyDown(handler->keybind_LUT[i]);
        else if (i >= DNF_GAME_ACTION_ATTACK1 && i <= DNF_GAME_ACTION_ATTACK2)
            current_down = IsMouseButtonDown(handler->keybind_LUT[i]);

        // update action state according to the current key state
        if (current_down)
        {
            // was IDLE or RELEASED, now it is PRESSED again
            if (handler->action_states[i] <= DNF_INPUT_STATE_RELEASED)
                handler->action_states[i] = DNF_INPUT_STATE_PRESSED;
            // was PRESSED OR HELD, now it is HELD
            else
                handler->action_states[i] = DNF_INPUT_STATE_HELD;
        }
        else
        {
            // was PRESSED or HELD, now it is RELEASED
            if (handler->action_states[i] >= DNF_INPUT_STATE_PRESSED)
                handler->action_states[i] = DNF_INPUT_STATE_RELEASED;
            // was RELEASED, now it is IDLE
            else
                handler->action_states[i] = DNF_INPUT_STATE_IDLE;
        }
    }
}

DNF_InputState core_input_get_current_state(const DNF_InputSystemHandler *handler, const DNF_GameAction action)
{
    return handler->action_states[action];
}

bool core_input_action_is_pressed(const DNF_InputSystemHandler *handler, const DNF_GameAction action)
{
    return core_input_get_current_state(handler, action) == DNF_INPUT_STATE_PRESSED;
}

bool core_input_action_is_held(const DNF_InputSystemHandler *handler, const DNF_GameAction action)
{
    return core_input_get_current_state(handler, action) == DNF_INPUT_STATE_HELD;
}

bool core_input_action_is_released(const DNF_InputSystemHandler *handler, const DNF_GameAction action)
{
    return core_input_get_current_state(handler, action) == DNF_INPUT_STATE_RELEASED;
}
