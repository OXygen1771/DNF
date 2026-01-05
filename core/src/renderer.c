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


#include "renderer.h"

#include "logger.h"

#include <raylib.h>
#include <raymath.h>

#include <stdlib.h>


bool8_t renderer_init(
    renderer_context *ctx,
    const int32_t out_width,
    const int32_t out_height)
{
    // TODO: make the logic more robust and raise errors if something is wrong
    ctx->framebuffer.width = out_width;
    ctx->framebuffer.height = out_height;
    ctx->framebuffer.pixels = GenImageColor(out_width, out_height, BLACK).data;

    // initialize target Texture2D
    const Image target_image = {
        .data = ctx->framebuffer.pixels,
        .width = out_width,
        .height = out_height,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
    };
    ctx->target = LoadTextureFromImage(target_image);
    SetTextureFilter(ctx->target, TEXTURE_FILTER_POINT);  // no interpolation
    DNF_DEBUG("Initialized rendering context");

    DNF_INFO(
        "Initialized a new rendering context: "
        "target resolution %dx%d, ",
        out_width, out_height);

    return true;
}

void renderer_resize_window(
    renderer_context *ctx,
    const int32_t window_width,
    const int32_t window_height)
{
    // scale factor - get it from either of the ratios
    const float32_t scale = fminf(
        (float32_t)window_width / (float32_t)ctx->target.width,
        (float32_t)window_height / (float32_t)ctx->target.height);

    // we could just do ctx->screen_rect.width = window_width
    ctx->screen_rect.width = (float32_t)ctx->target.width * scale;
    ctx->screen_rect.height = (float32_t)ctx->target.height * scale;

    // update screen rectangle top-left corner position
    ctx->screen_rect.x = ((float32_t)window_width - ctx->screen_rect.width) / 2;
    ctx->screen_rect.y = ((float32_t)window_height - ctx->screen_rect.height) / 2;
}

void renderer_shutdown(renderer_context *ctx)
{
    if (ctx)
    {
        DNF_INFO(
            "Shutting down a rendering context: "
            "target %dx%d, screen %dx%d",
            ctx->target.width, ctx->target.height,
            ctx->screen_rect.width, ctx->screen_rect.height);
        UnloadTexture(ctx->target);
        DNF_INFO("Renderer shut down successfully");
    }
}


void renderer_begin_frame(const renderer_context *ctx)
{
    // update texture with our framebuffer
    UpdateTexture(ctx->target, ctx->framebuffer.pixels);

    BeginDrawing();
    ClearBackground(BLACK);

    // scale the render to the screen rect
    DrawTexturePro(
        // Texture to render
        ctx->target,
        // Source rectangle
        (Rectangle){
            0.0f,
            0.0f,
            (float32_t)ctx->framebuffer.width,
            (float32_t)ctx->framebuffer.height},
        // Destination rectangle (to scale to)
        ctx->screen_rect,
        // Origin of destination rectangle
        (Vector2){0.0f, 0.0f},
        // Rotation of destination rectangle
        0.0f,
        // Tint
        WHITE);
}

void renderer_end_frame(const renderer_context *ctx)
{
    // render the entire screen
    EndDrawing();
}
