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

#include <raylib.h>

#define WIDTH 960    //!< Render texture width.
#define WIDTH2 480   //!< Half of render texture width.
#define HEIGHT 540   //!< Render texture height.
#define HEIGHT2 270  //!< Half of render texture height.


/**
 * @brief Initializes the rendering engine.
 *
 * Creates a Texture2D that will be used to render stuff to.
 */
void core_renderer_init(void);

/**
 * @brief Stops the rendering engine.
 *
 * Unloads the render texture from the GPU.
 */
void core_renderer_stop(void);

/**
 * @brief Draws a pixel at given coordinates with a given color.
 *
 * @param x X coord (left to right)
 * @param y Y coord (top to bottom)
 * @param color raylib Color
 */
void core_renderer_draw_pixel(uint32_t x, uint32_t y, Color color);

/**
 * @brief Draws the game scene.
 */
DNF_API void core_renderer_render(void);
