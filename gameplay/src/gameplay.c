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
#include "renderer.h"
#include "log.h"

#include <math.h>


typedef struct Player
{
    int32_t x;        //!< Player x position.
    int32_t y;        //!< Player y position.
    int32_t z;        //!< Player z position.
    int32_t angle_h;  //!< Player horizontal angle of rotation in degrees.
    int32_t angle_v;  //!< Player vertical angle of rotation in degrees.
} Player;

typedef struct AngleMath
{
    float32_t cos[360];  //!< Cosine lookup table.
    float32_t sin[360];  //!< Sine lookup table.
} AngleMath;

static const DNF_InputSystemHandler *input_handler;
static Player player;
static AngleMath angle_math;


void gameplay_init(const DNF_InputSystemHandler *input_system_handler)
{
    // set global input handler
    input_handler = input_system_handler;

    for (uint16_t a = 0; a < 360; a++)
    {
        angle_math.cos[a] = (float32_t)cos(a / 180.0 * PI);
        angle_math.sin[a] = (float32_t)sin(a / 180.0 * PI);
    }

    // set initial player coordinates
    player.x = 70; player.y = -110; player.z = 20;
    player.angle_h = 0; player.angle_v = 0;
}

/**
 * @brief Move player by a specified delta.
 *
 * @param dx Change in x direction.
 * @param dy Change in y direction.
 * @param dz Change in z direction.
 */
void move_player(const int32_t dx, const int32_t dy, const int32_t dz)
{
    const int32_t dxa = angle_math.cos[player.angle_h] * 10.0;
    const int32_t dya = angle_math.cos[player.angle_v] * 10.0;

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

    player.angle_h += (int32_t)d_angle.x;
    player.angle_v += (int32_t)d_angle.y;

    if (player.angle_h < 0)
        player.angle_h += 360;
    else if (player.angle_h > 359)
        player.angle_h -= 360;

    if (player.angle_v < 0)
        player.angle_v += 360;
    else if (player.angle_v > 359)
        player.angle_v -= 360;
}

void draw_game()
{
    int32_t wx[4], wy[4], wz[4];
    const float32_t cos = angle_math.cos[player.angle_h], sin = angle_math.sin[player.angle_h];

    // wall bottom points offset
    const int32_t x1 = 40 - player.x, y1 = 10 - player.y, z1 = 0 - player.z;
    const int32_t x2 = 40 - player.x, y2 = 310 - player.y, z2 = 0 - player.z;

    // world positions
    wx[0] = x1 * cos - y1 * sin; wy[0] = x1 * sin + y1 * cos; wz[0] = z1 + (player.angle_v * wy[0]) / 32.0;
    wx[1] = x2 * cos - y2 * sin; wy[1] = x2 * sin + y2 * cos; wz[1] = z2 + (player.angle_v * wy[1]) / 32.0;

    // screen positions
    wx[0] = wx[0] * 200 / wy[0] + WIDTH2; wy[0] = wz[0] * 200 / wy[0] + HEIGHT2;
    wx[1] = wx[1] * 200 / wy[1] + WIDTH2; wy[1] = wz[1] * 200 / wy[1] + HEIGHT2;

    // draw positions
    // if (wx[0] > 0 && wx[0] < WIDTH && wy[0] > 0 && wy[0] < HEIGHT)
    //     for (int i = wx[0] - 4, j = wy[0] - 4; i <= wx[0] + 4; i++, j++)
    //         core_renderer_draw_pixel(i, j, WHITE);

    for (int32_t i = 100; i < 250; i++)
        for (int32_t j = 100; j < 250; j++)
            core_renderer_draw_pixel(i, j, WHITE);
}

void gameplay_update(float32_t dt)
{
    const Vector2 mouse_pos_delta = input_handler->mouse_pos_delta;
    // rotate_player(mouse_pos_delta);

    if (core_input_action_is_held(input_handler, DNF_GAME_ACTION_MOVE_FORWARD))
        move_player(4, 0, 0);
    if (core_input_action_is_held(input_handler, DNF_GAME_ACTION_MOVE_BACKWARD))
        move_player(-4, 0, 0);
    if (core_input_action_is_held(input_handler, DNF_GAME_ACTION_MOVE_LEFT))
        move_player(0, -4, 0);
    if (core_input_action_is_held(input_handler, DNF_GAME_ACTION_MOVE_RIGHT))
        move_player(0, 4, 0);

    draw_game();
}
