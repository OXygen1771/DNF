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

#pragma once

#include "defines.h"
#include "renderer.h"

/**
 * @brief An enum that represents all possible player actions.
 */
typedef enum dnf_game_action
{
    // MOVEMENT

    DNF_GAME_ACTION_MOVE_FORWARD,
    DNF_GAME_ACTION_MOVE_BACKWARD,
    DNF_GAME_ACTION_MOVE_LEFT,
    DNF_GAME_ACTION_MOVE_RIGHT,

    DNF_GAME_ACTION_MOVE_UP,
    DNF_GAME_ACTION_MOVE_DOWN,

    // INTERACTIONS

    DNF_GAME_ACTION_INTERACT,       //!< Primary interaction (buttons, etc.)

    // ATTACKS

    DNF_GAME_ACTION_ATTACK1,        //!< Primary attack
    DNF_GAME_ACTION_ATTACK2,        //!< Secondary attack

    // MENU

    DNF_GAME_ACTION_MENU,           //!< Menu button

    // UTIL

    DNF_GAME_ACTION_COUNT           //!< Total number of actions
} dnf_game_action;

/**
 * @brief An enum that represents possible types of input (for different
 * raylib input checking functions).
 */
typedef enum dnf_input_type
{
    DNF_INPUT_TYPE_KEYBOARD,
    DNF_INPUT_TYPE_MOUSE,
} dnf_input_type;

/**
 * @brief A structure that represents an input binding (in raylib keycodes).
 */
typedef struct dnf_input_binding
{
    dnf_input_type input_type;  //!< Input type (keyboard/mouse)
    int32_t raylib_code;        //!< Raylib keycode (different for different types).
} dnf_input_binding;

/**
 * @brief A structure that represents the input handler interface.
 */
typedef struct dnf_input_system_handler
{
    /**
     * @brief Function pointer to check if a given action was just pressed.
     *
     * @param action Game action to check.
     */
    bool8_t (*is_pressed)(dnf_game_action action);

    /**
     * @brief Function pointer to check if a given action is currently held.
     *
     * @param action Game action to check.
     */
    bool8_t (*is_held)(dnf_game_action action);

    /**
     * @brief Function pointer to check if a given action was just released.
     *
     * @param action Game action to check.
     */
    bool8_t (*is_released)(dnf_game_action action);
} dnf_input_system_handler;


/**
 * @brief A structure that describes the engine configuration.
 */
typedef struct dnf_engine_config
{
    int32_t start_width;   //!< Initial window width.
    int32_t start_height;  //!< Initial window height.
    char *title;           //!< Window title.
} dnf_engine_config;


/**
 * @brief A structure that represents our game interface and info.
 */
typedef struct game
{
    // Current engine configuration.
    dnf_engine_config *engine_config;

    // Current input handler.
    dnf_input_system_handler *input_handler;

    // Current renderer context.
    renderer_context *renderer_context;

    // Rendering API (for calling raylib functions)
    dnf_renderer_api renderer_api;

    /**
     * @brief Function pointer to game's initialization function.
     *
     * @param game_instance Game instance info.
     * @return True if game initialized successfully.
     */
    bool8_t (*init)(struct game *game_instance);

    /**
     * @brief Function pointer to game's update function.
     *
     * @param game_instance Game instance info.
     * @param dt Time since last frame in seconds.
     * @return True if game updated successfully.
     */
    bool8_t (*update)(struct game *game_instance, float32_t dt);

    /**
     * @brief Function pointer to game's rendering function.
     *
     * @param game_instance Game instance info.
     * @param dt Time since last frame in seconds.
     * @return True if frame rendered successfully.
     */
    bool8_t (*render)(struct game *game_instance, float32_t dt);

    // Game state.
    void *game_state;
} game;
