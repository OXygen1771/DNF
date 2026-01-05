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


/**
 * @brief Basic framebuffer with R8G8B8A8 values
 */
typedef struct dnf_framebuffer
{
    Color *pixels;  //!< Array of pixels (colors - uint8_t * 4)
    int32_t width;
    int32_t height;
} dnf_framebuffer;

/**
 * @brief A structure that represents the rendering engine API.
 *
 * It provides function pointers to rendering functions that should be
 * independent of an app (i.e. game or editor).
 *
 * It also helps with the fact that a game is basically a shared library, and it
 * can't call raylib and render to the same OpenGL context that the engine
 * renders to.
 */
typedef struct dnf_renderer_api
{
    /**
     * @brief Render text (wrapper for raylib's DrawText())
     */
    void (*draw_text)(
        const char *text,
        int32_t x,int32_t y,
        int32_t size,
        Color color);

    /**
     * @brief A special variant of DrawText() which draws current FPS.
     */
    void (*draw_fps)(int32_t x, int32_t y);
} dnf_renderer_api;

/**
 * @brief A structure that represents a rendering context.
 */
typedef struct renderer_context
{
    dnf_framebuffer framebuffer;  //!< Pixel buffer
    Texture2D target;             //!< Target texture
    Rectangle screen_rect;        //!< Actual screen size
} renderer_context;

/**
 * @brief Initializes the renderer and populates a given context.
 *
 * @param ctx Resulting rendering context.
 * @param out_width Target image width.
 * @param out_height Target image height.
 * @return True if successful, false otherwise.
 */
bool8_t renderer_init(
    renderer_context *ctx,
    int32_t out_width,
    int32_t out_height);

/**
 * @brief Resizes the renderer window (not the output) in a given context.
 *
 * @param ctx Rendering context to resize.
 * @param window_width New window width.
 * @param window_height New window height.
 */
DNF_API void renderer_resize_window(
    renderer_context *ctx,
    int32_t window_width,
    int32_t window_height);

/**
 * @brief Shuts down the renderer of a given context.
 *
 * @param ctx Rendering context to stop.
 */
void renderer_shutdown(renderer_context *ctx);


/**
 * @brief Creates a rendering api to wrap raylib draw functions.
 *
 * @return Rendering API.
 */
DNF_API dnf_renderer_api renderer_get_api(void);

/**
 * @brief Begins rendering a frame of a given context.
 *
 * @param ctx Rendering context to render.
 */
DNF_API void renderer_begin_frame(const renderer_context *ctx);

/**
 * @brief Stops rendering a frame of a given context.
 *
 * @param ctx
 */
DNF_API void renderer_end_frame(const renderer_context *ctx);
