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


typedef struct wall_t
{
    Vector2 start;
    Vector2 end;

    Color color;
} wall_t;

typedef struct sector_t
{
    int32_t wall_start;
    int32_t wall_end;

    float32_t base_level;
    float32_t height;

    Vector2 center;

    float32_t z_depth;
} sector_t;

typedef struct map_data_t
{
    uint32_t wall_count;
    uint32_t sector_count;
    wall_t *walls;
    sector_t *sectors;
} map_data_t;
