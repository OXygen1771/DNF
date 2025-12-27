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


#ifndef DNF_RENDERER_H
#define DNF_RENDERER_H

#include "raylib.h"

/**
 * @brief Initializes the rendering engine.
 */
void core_renderer_init(void);

/**
 * @brief Stops the rendering engine.
 */
void core_renderer_stop(void);

/**
 * @brief Clears the frame buffer with the given color.
 *
 * @param color Fill color
 */
void core_renderer_clear(Color color);

#endif //DNF_RENDERER_H
