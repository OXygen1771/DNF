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


#include "input_system.h"
#include "logger.h"

#include <raylib.h>


// A LUT map from game actions to bindings.
static dnf_input_binding actions[DNF_GAME_ACTION_COUNT];

static dnf_input_system_handler *input_handler;  // a "singleton" handler
static bool8_t dnf_input_system_initialized = false;  // flag to prevent re-initialization


bool8_t binding_is_pressed(const dnf_input_binding binding)
{
    switch (binding.input_type)
    {
    case DNF_INPUT_TYPE_KEYBOARD:
        return IsKeyPressed(binding.raylib_code);
    case DNF_INPUT_TYPE_MOUSE:
        return IsMouseButtonPressed(binding.raylib_code);
    default:
        return false;
    }
}

bool8_t binding_is_held(const dnf_input_binding binding)
{
    switch (binding.input_type)
    {
        case DNF_INPUT_TYPE_KEYBOARD:
            return IsKeyDown(binding.raylib_code);
        case DNF_INPUT_TYPE_MOUSE:
            return IsMouseButtonDown(binding.raylib_code);
        default:
            return false;
    }
}

bool8_t binding_is_released(const dnf_input_binding binding)
{
    switch (binding.input_type)
    {
        case DNF_INPUT_TYPE_KEYBOARD:
            return IsKeyReleased(binding.raylib_code);
        case DNF_INPUT_TYPE_MOUSE:
            return IsMouseButtonReleased(binding.raylib_code);
        default:
            return false;
    }
}


bool8_t is_pressed(const dnf_game_action action)
{
    return binding_is_pressed(actions[action]);
}

bool8_t is_held(const dnf_game_action action)
{
    return binding_is_held(actions[action]);
}

bool8_t is_released(const dnf_game_action action)
{
    return binding_is_released(actions[action]);
}

bool8_t input_handler_init(dnf_input_system_handler* handler)
{
    if (dnf_input_system_initialized)
    {
        DNF_ERROR("Tried to initialize input system more than once!");
        return false;
    }

    // set global handler pointer
    input_handler = handler;

    // set handler function pointers
    input_handler->is_pressed = is_pressed;
    input_handler->is_held = is_held;
    input_handler->is_released = is_released;

    // set default keybinds
    // TODO: add config and change it in entrypoints, not here
    actions[DNF_GAME_ACTION_MOVE_FORWARD] = (dnf_input_binding){DNF_INPUT_TYPE_KEYBOARD, KEY_W};
    actions[DNF_GAME_ACTION_MOVE_BACKWARD] = (dnf_input_binding){DNF_INPUT_TYPE_KEYBOARD, KEY_S};
    actions[DNF_GAME_ACTION_MOVE_LEFT] = (dnf_input_binding){DNF_INPUT_TYPE_KEYBOARD, KEY_A};
    actions[DNF_GAME_ACTION_MOVE_RIGHT] = (dnf_input_binding){DNF_INPUT_TYPE_KEYBOARD, KEY_D};

    actions[DNF_GAME_ACTION_MOVE_UP] = (dnf_input_binding){DNF_INPUT_TYPE_KEYBOARD, KEY_E};
    actions[DNF_GAME_ACTION_MOVE_DOWN] = (dnf_input_binding){DNF_INPUT_TYPE_KEYBOARD, KEY_Q};

    actions[DNF_GAME_ACTION_INTERACT] = (dnf_input_binding){DNF_INPUT_TYPE_KEYBOARD, KEY_F};

    actions[DNF_GAME_ACTION_ATTACK1] = (dnf_input_binding){DNF_INPUT_TYPE_MOUSE, MOUSE_BUTTON_LEFT};
    actions[DNF_GAME_ACTION_ATTACK2] = (dnf_input_binding){DNF_INPUT_TYPE_MOUSE, MOUSE_BUTTON_RIGHT};

    actions[DNF_GAME_ACTION_MENU] = (dnf_input_binding){DNF_INPUT_TYPE_KEYBOARD, KEY_ESCAPE};

    return true;
}

void input_handler_shutdown()
{
}
