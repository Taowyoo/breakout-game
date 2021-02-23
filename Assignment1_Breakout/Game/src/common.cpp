/**
 * @file common.cpp
 * @author Yuxiang Cao (cao.yux@northeastern.edu)
 * @brief Definition of all global variables
 * @version 1.0.0
 * @date 2021-02-22 23:03:50 -08:00
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "Common.h"
int WINDOW_WIDTH;
int WINDOW_HEIGHT;

int GAME_SCENE_WIDTH;
int GAME_SCENE_LEFT;
int GAME_SCENE_RIGHT;
int WALL_WIDTH;
float PADDLE_SPEED;
int PADDLE_WIDTH;
int PADDLE_HEIGHT;
int PADDLE_DISTANCE_FROM_BOTTOM;

float BALL_START_DEGREE;
float BALL_SPEED;
int BALL_WIDTH;
int BALL_HEIGHT;

int BRICK_START_HEIGHT;
int BRICK_WIDTH;
int BRICK_HEIGHT;
int BRICK_INTERVAL;
int BRICK_ROW;
int BRICK_COLUMN;
int BRICK_DEFAULT_SCORE;
int PLAYER_DEFAULT_LIFE_NUM;

/// Default begin level
int DEFAULT_LEVEL;

int DEFAULT_FONT_SIZE;
int MENU_FONT_SIZE;

int SCREEN_FPS_60;
/// Milliseconds between each frame update when fps is 60
int SCREEN_TICKS_PER_FRAME_60;
/// Milliseconds between each update
int TICKS_PER_UPDATE;
