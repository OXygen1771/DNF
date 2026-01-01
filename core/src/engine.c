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


#include "engine.h"
#include "renderer.h"
#include "input_system.h"
#include "log.h"

#include "raylib.h"


//!< Global input system handler (initialized in the engine's init function)
static DNF_InputSystemHandler g_InputSystemHandler;

void core_engine_init(const char *title, const int width, const int height)
{
    dnf_log_system_init();
    dnf_info("Starting the DNF engine");

    dnf_info("Initializing window %s (%dx%d)", title, width, height);
    InitWindow(width, height, title);
    SetTargetFPS(60);  // TODO: add FPS setting?

    dnf_info("Initializing the rendering engine");
    core_renderer_init();
    dnf_info("Initializing the input system");
    core_input_system_init(&g_InputSystemHandler);
}

void core_engine_loop(void (*update_callback)(float dt, const DNF_InputSystemHandler *))
{
    dnf_info("Starting the DNF engine loop");
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        core_input_update(&g_InputSystemHandler);
        update_callback(dt, &g_InputSystemHandler);
        core_renderer_render();
    }
    dnf_info("DNF engine loop exited!");
}

void core_engine_stop(void)
{
    dnf_info("Stopping the DNF game engine");
    dnf_info("Stopping the rendering engine");
    core_renderer_stop();
    CloseWindow();
}
