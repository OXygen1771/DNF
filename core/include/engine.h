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


#ifndef DNF_ENGINE_H
#define DNF_ENGINE_H

/**
 * @brief Initializes the game engine.
 *
 * Initializes engine systems, creates a game window, a renderer.
 *
 * @param  title   Game window title
 * @param  width   Game window width
 * @param height   Game window height
 */
void core_engine_init(const char *title, int width, int height);

/**
 * @brief Runs the core engine loop.
 *
 * @param update_callback Game update callback
 */
void core_engine_loop(void (*update_callback)(float dt));

/**
 * @brief Stops the engine loop.
 */
void core_engine_stop(void);

#endif //DNF_ENGINE_H
