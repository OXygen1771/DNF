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

/**
 * @brief A structure that describes the engine configuration.
 */
typedef struct dnf_engine_config
{
    int32_t start_width;   //!< Initial window width.
    int32_t start_height;  //!< Initial window height.
    char *title;           //!< Window title.
} dnf_engine_config;

/**
 * @brief A structure that represents our game interface and info.
 */
typedef struct game
{
    /**
     * @brief Function pointer to game's initialization function.
     *
     * @param game_instance Game instance info.
     * @return True if game initialized successfully.
     */
    bool8_t (*init)(struct game *game_instance);

    /**
     * @brief Function pointer to game's update function.
     *
     * @param game_instance Game instance info.
     * @param dt Time since last frame in seconds.
     * @return True if game updated successfully.
     */
    bool8_t (*update)(struct game *game_instance, float32_t dt);

    /**
     * @brief Function pointer to game's rendering function.
     *
     * @param game_instance Game instance info.
     * @param dt Time since last frame in seconds.
     * @return True if frame rendered successfully.
     */
    bool8_t (*render)(struct game *game_instance, float32_t dt);

    /**
     * @brief Function pointer to resize the game window.
     *
     * @param game_instance Game instance info.
     * @param width New window width.
     * @param height New window height.
     */
    void (*resize)(struct game *game_instance, uint32_t width, uint32_t height);

    // Game state.
    void *game_state;
} game;

/**
 * @brief Creates a window and initializes the engine loop.
 *
 * @param config Pointer to initial engine config.
 * @param game_instance Pointer to game instance.
 * @return True if started successfully, false otherwise.
 */
DNF_API bool8_t engine_init(const dnf_engine_config *config, game *game_instance);

/**
 * @brief Runs the engine loop.
 *
 * @return True if exited out of the loop successfully, false otherwise.
 */
DNF_API bool8_t engine_run(void);
