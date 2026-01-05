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

/**
 * @brief Creates a window and initializes the engine loop.
 *
 * @param game_instance Pointer to game instance.
 * @return True if started successfully, false otherwise.
 */
DNF_API bool8_t engine_init(game *game_instance);

/**
 * @brief Runs the engine loop.
 *
 * @return True if exited out of the loop successfully, false otherwise.
 */
DNF_API bool8_t engine_run(void);
