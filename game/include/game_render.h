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
#include "dnf_gametypes.h"

#include "game.h"


/**
 * @brief Initializes the game renderer.
 * @param game_instance Game instance to initialize the renderer for.
 * @return True if successful, false otherwise.
 */
bool8_t init_renderer(const game *game_instance);

/**
 * @brief Draws a game frame, including the UI.
 *
 * @param game_state Current game state to render.
 * @param dt Time in milliseconds since last frame.
 * @return True if successful, false otherwise.
 */
bool8_t draw_game(const dnf_game_state *game_state, float32_t dt);
