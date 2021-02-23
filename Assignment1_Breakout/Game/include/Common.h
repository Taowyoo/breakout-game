/**
 * @file Common.h
 * @author Yuxiang Cao (cao.yux@northeastern.edu)
 * @brief Header file to declare all global variables
 * @version 1.0.0
 * @date 2021-02-22 22:52:41 -08:00
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef COMMON_H_
#define COMMON_H_

#include <string>

#include "TinyMath.hpp"

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

extern int GAME_SCENE_WIDTH;
extern int GAME_SCENE_LEFT;
extern int GAME_SCENE_RIGHT;
extern int WALL_WIDTH;
extern float PADDLE_SPEED;
extern int PADDLE_WIDTH;
extern int PADDLE_HEIGHT;
extern int PADDLE_DISTANCE_FROM_BOTTOM;

extern float BALL_START_DEGREE;
extern float BALL_SPEED;
extern int BALL_WIDTH;
extern int BALL_HEIGHT;

extern int BRICK_START_HEIGHT;
extern int BRICK_WIDTH;
extern int BRICK_HEIGHT;
extern int BRICK_INTERVAL;
extern int BRICK_ROW;
extern int BRICK_COLUMN;
extern int BRICK_DEFAULT_SCORE;
extern int PLAYER_DEFAULT_LIFE_NUM;

/// Default begin level
extern int DEFAULT_LEVEL;

extern int DEFAULT_FONT_SIZE;
extern int MENU_FONT_SIZE;

extern int SCREEN_FPS_60;
/// Milliseconds between each frame update when fps is 60
extern int SCREEN_TICKS_PER_FRAME_60;
/// Milliseconds between each update
extern int TICKS_PER_UPDATE;

/**
 * @brief Indicate paddle moving state
 *
 */
enum Buttons {
  PaddleLeft = 0,  ///< Paddle is moving left
  PaddleRight,     ///< Paddle is moving right
};

/**
 * @brief Game state Enum
 *
 */
enum GameState {
  Initializing,    ///< Game is under initialization
  Running,         ///< Game is running
  PauseNormal,     ///< Game paused normally
  PauseWin,        ///< Game paused because player just finish one level
  PauseClearGame,  ///< Game paused because player finished all levels
  PauseLoseGame,   ///< Game paused because player lose all lives
  PauseLoseLife    ///< Game paused because player lose one life
};

/**
 * @brief Collision direction
 *
 */
enum class CollisionType {
  None,    ///< No collision happened
  Top,     ///< Ball is now moving towards top
  Middle,  ///< Ball hit the middle of the paddle
  Bottom,  ///< Ball is now moving towards bottom
  Left,    ///< Ball is now moving towards left
  Right    ///< Ball is now moving towards right
};
/**
 * @brief Collision info struct
 *
 */
struct Contact {
  CollisionType type;    ///< Collision direction
  Vector2D penetration;  ///< How much the ball has penetrated in hitted object
};

#endif  // COMMON_H_
