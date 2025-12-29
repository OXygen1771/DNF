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


#ifndef DNF_INPUT_SYSTEM_H
#define DNF_INPUT_SYSTEM_H

#include <stdbool.h>

/**
 * @brief An enum that represents the player's current action.
 *
 * Every possible player action has a value in this enum. These values are used
 * to map the player's key presses to their respective actions. This allows
 * remapping buttons through a settings menu possible and (hopefully) easy.
 */
typedef enum DNF_GameAction
{
    DNF_GAME_ACTION_NONE,             //!< No action (maps to no keys pressed)

    //    MOVEMENT

    DNF_GAME_ACTION_MOVE_FORWARD,
    DNF_GAME_ACTION_MOVE_BACKWARD,
    DNF_GAME_ACTION_MOVE_LEFT,
    DNF_GAME_ACTION_MOVE_RIGHT,

    //    SPECIAL INTERACTIONS

    DNF_GAME_ACTION_INTERACT,

    //    ATTACKS AND WEAPONS

    DNF_GAME_ACTION_ATTACK1,          //!< Primary attack
    DNF_GAME_ACTION_ATTACK2,          //!< Secondary attack/interaction

    //    UTIL

    DNF_GAME_ACTION_COUNT,            //!< Total number of possible actions
} DNF_GameAction;

/**
 * @brief An enum that represents the state of an input (key or mouse button).
 *
 * Currently, we only support 4 states of a button: it can be idle
 * (not interacted with), pressed or released during the current update cycle,
 * or held for more than 1 update cycle.
 */
typedef enum DNF_InputState
{
    DNF_INPUT_STATE_IDLE,             //!< Input not interacted with
    DNF_INPUT_STATE_RELEASED,         //!< Input released in the current update
    DNF_INPUT_STATE_PRESSED,          //!< Input pressed in the current update
    DNF_INPUT_STATE_HELD,             //!< Input held, but not yet released
} DNF_InputState;

/**
 * @brief A structure that represents a mapping from raylib input codes to
 * game actions.
 *
 * This InputSystemHandler is a universal struct for mapping raylib keycodes to
 * game actions.
 *
 * It should be created only once and passed between functions
 * and modules by reference. This way, the dynamic gameplay module can handle
 * the player's inputs instead of the static core module.
 */
typedef struct DNF_InputSystemHandler
{
    /* A map between raylib keycodes and game actions. */
    int keybind_LUT[DNF_GAME_ACTION_COUNT];
    /* An array containing input states of all game actions. */
    DNF_InputState action_states[DNF_GAME_ACTION_COUNT];
} DNF_InputSystemHandler;

/**
 * @brief Initializes the given input system handler.
 *
 * @param handler Pointer to an uninitialized input system handler.
 */
void core_input_system_init(DNF_InputSystemHandler *handler);

/**
 * @brief Updates the input state once per game update.
 *
 * Listens to the player's key interactions, maps them to game actions and
 * updates these actions' states, as in DNF_InputState.
 *
 * @param handler Pointer to the input system handler.
 */
void core_input_update(DNF_InputSystemHandler *handler);

/**
 * @brief Gets the input state of the key for a given action.
 *
 * @param handler Pointer to the input system handler.
 * @param action ID of an action, as in DNF_GameAction.
 * @return Input state (Idle, Pressed, Held, Released), as in DNF_InputState.
 */
DNF_InputState core_input_get_current_state(const DNF_InputSystemHandler *handler, DNF_GameAction action);

/**
 * @brief Helper to check whether the key of a given action was pressed in the
 * current game update.
 *
 * @param handler Pointer to the input system handler.
 * @param action ID of an action, as in DNF_GameAction.
 * @return true if the key was pressed during the current game update.
 */
bool core_input_action_is_pressed(const DNF_InputSystemHandler *handler, DNF_GameAction action);

/**
 * @brief Helper to check whether the key of a given action is held in the
 * current game update.
 *
 * @param handler Pointer to the input system handler.
 * @param action ID of an action, as in DNF_GameAction
 * @return true if the key is being held during the current game update.
 */
bool core_input_action_is_held(const DNF_InputSystemHandler *handler, DNF_GameAction action);

/**
 * @brief Helper to check whether the key of a given action was released in the
 * current game update.
 *
 * @param handler Pointer to the input system handler.
 * @param action ID of an action, as in DNF_GameAction.
 * @return true if the key was released during the current update
 */
bool core_input_action_is_released(const DNF_InputSystemHandler *handler, DNF_GameAction action);

#endif //DNF_INPUT_SYSTEM_H
