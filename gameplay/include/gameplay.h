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


#ifndef DNF_GAMEPLAY_H
#define DNF_GAMEPLAY_H

#include "gameplay_api.h"
#include "input_system.h"

/**
 * @brief Updates the game state.
 *
 * @param dt Time since last update (frame).
 * @param input_handler Pointer to the input system handler.
 */
DNF_GAMEPLAY_API void gameplay_update(float dt, const DNF_InputSystemHandler *input_handler);

#endif //DNF_GAMEPLAY_H
