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

#include "engine.h"
#include "logger.h"

/**
 * @brief Game creation function.
 *
 * Fills out the engine config and game instance to use in the engine creation
 * and loop.
 *
 * @param out_config Resulting engine config.
 * @param out_game_instance Resulting game interface.
 * @return True if game creation was successful, false otherwise.
 */
bool8_t game_create(dnf_engine_config *out_config, game *out_game_instance);
