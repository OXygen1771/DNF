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
#include "logger.h"

#include <raylib.h>


/**
 * @brief A structure that represents the current engine state.
 *
 * There should be only one of these.
 */
typedef struct dnf_engine_state
{
    bool8_t is_running;
    bool8_t is_paused;  //!< Window is out of focus and should not be processed.
} dnf_engine_state;

static dnf_engine_state engine_state;  // a "singleton" engine state
static bool dnf_engine_initialized = false;  // flag to prevent re-initialization


bool8_t engine_init(const dnf_engine_config* config)
{
    if (dnf_engine_initialized)
    {
        DNF_ERROR("Tried to initialize engine more than once!");
        return false;
    }

    // Initialize engine systems
    if (dnf_logger_init())
        DNF_INFO("Logger initialized");


    // Initialize window and create OpenGL context
    InitWindow(config->start_width, config->start_height, config->title);
    SetTargetFPS(60);  // TODO: add FPS settings

    DNF_INFO("Initializing renderer");
    core_renderer_init();
    DNF_INFO("Renderer initialized");
    // TODO: initialize input handling system

    // All subsystems are running
    engine_state.is_running = true;
    engine_state.is_paused = false;

    // Prevent re-initialization after initializing everything else
    dnf_engine_initialized = true;

    return true;
}

bool8_t engine_run(void)
{
    while (engine_state.is_running)
    {
        if (WindowShouldClose())
            engine_state.is_running = false;

        core_renderer_render();
    }

    // explicitly tell the window to close
    CloseWindow();

    // Shutdown all systems
    dnf_logger_shutdown();
    core_renderer_stop();

    return true;
}
