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

typedef struct dnf_game_state
{
    int8_t number;
} dnf_game_state;

DNF_API bool8_t dnf_game_init(game *game_instance);

DNF_API bool8_t dnf_game_update(game *game_instance, float32_t dt);

DNF_API bool8_t dnf_game_render(game *game_instance, float32_t dt);

DNF_API void dnf_game_resize(game *game_instance, int32_t new_width, int32_t new_height);
