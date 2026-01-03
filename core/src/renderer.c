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
#include "raylib.h"

// Global pixel array.
static Color pixels[WIDTH * HEIGHT];
// Main texture that we will draw to directly.
static Texture2D fb_texture;

void core_renderer_init(void)
{
    const Image fb_image = {
        .data = pixels,
        .width = WIDTH,
        .height = HEIGHT,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
    };
    fb_texture = LoadTextureFromImage(fb_image);
    SetTextureFilter(fb_texture, TEXTURE_FILTER_POINT);  // disable interpolation
}

void core_renderer_stop(void)
{
    UnloadTexture(fb_texture);
}

void core_renderer_draw_pixel(uint32_t x, uint32_t y, const Color color)
{
    pixels[y * WIDTH + x] = color;
}

void core_renderer_render(void)
{
    const float screen_width = (float)GetScreenWidth();
    const float screen_height = (float)GetScreenHeight();

    // get the smaller of ratios
    const float scale = (screen_width / (float)WIDTH) < (screen_height / (float)HEIGHT) ? (screen_width / (float)WIDTH) : (screen_height / (float)HEIGHT);

    const Vector2 position = {
        (screen_width - WIDTH * scale) / 2,
        (screen_height - HEIGHT * scale) / 2,
    };

    core_renderer_draw_pixel(50, 50, WHITE);

    UpdateTexture(fb_texture, pixels);
    BeginDrawing();
        ClearBackground(BLACK);
        DrawTextureEx(
            fb_texture,
            position,
            0.0f,
            scale,
            WHITE
            );
        DrawFPS(10, 10);
    EndDrawing();
}
