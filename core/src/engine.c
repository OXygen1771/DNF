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

#include "input_system.h"
#include "logger.h"
#include "renderer.h"

#include <raylib.h>


static game *dnf_game_instance;  // a "singleton" game instance pointer
static bool8_t dnf_engine_is_running = false;  // is the engine running
static bool8_t dnf_engine_initialized = false;  // flag to prevent re-initialization


bool8_t engine_init(game *game_instance)
{
    if (dnf_engine_initialized)
    {
        DNF_ERROR("Tried to initialize engine more than once!");
        return false;
    }

    // set global game instance pointer
    dnf_game_instance = game_instance;

    // Initialize engine systems
    if (dnf_logger_init())
        DNF_INFO("Logger initialized");


    // Initialize window and create OpenGL context
    InitWindow(
        game_instance->engine_config->start_width,
        game_instance->engine_config->start_height,
        game_instance->engine_config->title);
    SetTargetFPS(60);  // TODO: add FPS settings

    DNF_INFO("Initializing renderer");
    core_renderer_init();  // TODO: use game instance for initializing
    DNF_INFO("Renderer initialized");

    DNF_INFO("Initializing input system");
    if (input_handler_init(game_instance->input_handler))
        DNF_INFO("Input system initialized");


    // All subsystems are running
    dnf_engine_is_running = true;

    // Initialize game
    if (!dnf_game_instance->init(dnf_game_instance))
    {
        DNF_FATAL("Failed to initialize the game");
        return false;
    }
    dnf_game_instance->resize(dnf_game_instance, GetScreenWidth(), GetScreenHeight());

    // Prevent re-initialization after initializing everything else
    dnf_engine_initialized = true;

    return true;
}

bool8_t engine_run(void)
{
    while (dnf_engine_is_running)
    {
        if (WindowShouldClose())
            dnf_engine_is_running = false;

        float32_t dt = GetFrameTime();

        if (!dnf_game_instance->update(dnf_game_instance, dt))
        {
            DNF_FATAL("Game update failed! Exiting...");
            dnf_engine_is_running = false;
            break;
        }

        if (!dnf_game_instance->render(dnf_game_instance, dt))
        {
            DNF_ERROR("Frame rendering failed! Exiting...");
            dnf_engine_is_running = false;
            break;
        }
    }

    // explicitly tell the window to close
    CloseWindow();

    // Shutdown all systems
    dnf_logger_shutdown();
    core_renderer_stop();

    return true;
}
