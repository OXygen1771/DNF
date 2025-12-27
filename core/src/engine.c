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


#include "engine.h"
#include "renderer.h"
#include "raylib.h"


/**
 * @brief Global running indicator
 */
static bool g_running = false;

void core_engine_init(const char *title, const int width, const int height)
{
    InitWindow(width, height, title);
    SetTargetFPS(60);  // TODO: add FPS setting?

    core_renderer_init();

    g_running = true;
}

void core_engine_loop(void (*update)(float dt))
{
    while (g_running && !WindowShouldClose())
    {
        float dt = GetFrameTime();

        update(dt);

        BeginDrawing();
        core_renderer_clear(BLACK);
        EndDrawing();
    }
}
