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


#include "entrypoint.h"
#include "game.h"

#include <stdlib.h>


bool8_t game_create(game *out_game_instance)
{
    // configure the engine window
    out_game_instance->engine_config->start_width = 960;
    out_game_instance->engine_config->start_height = 540;
    out_game_instance->engine_config->title = "DNF 0.1.0 | TEST";

    // configure the game instance
    out_game_instance->init = dnf_game_init;
    out_game_instance->update = dnf_game_update;
    out_game_instance->render = dnf_game_render;
    out_game_instance->resize = dnf_game_resize;

    // configure the game state
    out_game_instance->game_state = malloc(sizeof(dnf_game_state));

    // TODO: do sturdier logic
    return true;
}

/**
 * @brief The game's main entry point (for the simplest .exe)
 *
 * @return Exit code.
 */
int main(void)
{
    dnf_engine_config engine_config;
    dnf_input_system_handler input_handler;
    renderer_context render_ctx;
    game game_instance;

    game_instance.engine_config = &engine_config;
    game_instance.input_handler = &input_handler;
    game_instance.renderer_context = &render_ctx;

    // Initialize game interface
    if (!game_create(&game_instance))
    {
        DNF_FATAL("Could not initialize game!");
        return -1;
    }

    // Initialize engine
    if (!engine_init(&game_instance))
    {
        DNF_FATAL("Could not initialize engine!");
        return 1;
    }

    // Run and shutdown
    if (!engine_run())
    {
        DNF_ERROR("Encountered an error while shutting down the engine.");
        return 2;
    }

    // exited ok!
    return 0;
}
