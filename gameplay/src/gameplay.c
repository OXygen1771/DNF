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


#include "gameplay.h"
#include "input_system.h"

#include <math.h>


typedef struct Player
{
    float x;        //!< Player x position.
    float y;        //!< Player y position.
    float z;        //!< Player z position.
    int angle_h;  //!< Player horizontal angle of rotation in degrees.
    int angle_v;  //!< Player vertical angle of rotation in degrees.
} Player;

typedef struct AngleMath
{
    float cos[360];  //!< Cosine lookup table.
    float sin[360];  //!< Sine lookup table.
} AngleMath;

static const DNF_InputSystemHandler *input_handler;
static Player player;
static AngleMath angle_math;


void gameplay_init(const DNF_InputSystemHandler *input_system_handler)
{
    // set global input handler
    input_handler = input_system_handler;

    // set initial player coordinates
    player.x = player.y = player.z = 0;
    player.angle_h = player.angle_v = 0;

    for (int a = 0; a < 360; a++)
    {
        angle_math.cos[a] = cosf((float)a / 180.0f * PI);
        angle_math.sin[a] = sinf((float)a / 180.0f * PI);
    }
}

/**
 * @brief Move player by a specified delta.
 *
 * @param dx Change in x direction.
 * @param dy Change in y direction.
 * @param dz Change in z direction.
 */
void move_player(const float dx, const float dy, const float dz)
{
    const float dxa = (float)(dx * angle_math.cos[player.angle_h] * 10);
    const float dya = (float)(dy * angle_math.cos[player.angle_v] * 10);

    player.x += dxa;
    player.y += dya;
    player.z += dz;
}

/**
 * @brief Rotate player based on mouse movement delta.
 *
 * @param mouse_pos_delta Change in mouse position since last frame.
 */
void rotate_player(const Vector2 mouse_pos_delta)
{
    const Vector2 d_angle = {
        mouse_pos_delta.x / 2,
        mouse_pos_delta.y / 4
    };

    player.angle_h += (int)d_angle.x;
    player.angle_v += (int)d_angle.y;

    if (player.angle_h < 0)
        player.angle_h += 360;
    else if (player.angle_h > 359)
        player.angle_h -= 360;

    if (player.angle_v < 0)
        player.angle_v += 360;
    else if (player.angle_v > 359)
        player.angle_v -= 360;
}

void gameplay_update(float dt)
{
    const Vector2 mouse_pos_delta = input_handler->mouse_pos_delta;
    rotate_player(mouse_pos_delta);

    if (core_input_action_is_held(input_handler, DNF_GAME_ACTION_MOVE_FORWARD))
        move_player(4, 0, 0);
    if (core_input_action_is_held(input_handler, DNF_GAME_ACTION_MOVE_BACKWARD))
        move_player(-4, 0, 0);
    if (core_input_action_is_held(input_handler, DNF_GAME_ACTION_MOVE_LEFT))
        move_player(0, -4, 0);
    if (core_input_action_is_held(input_handler, DNF_GAME_ACTION_MOVE_RIGHT))
        move_player(0, 4, 0);
}
