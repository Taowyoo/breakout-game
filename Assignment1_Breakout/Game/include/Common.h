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

extern int DEFAULT_LEVEL;

extern int DEFAULT_FONT_SIZE;
extern int MENU_FONT_SIZE;

extern int SCREEN_FPS_60;
extern int SCREEN_TICKS_PER_FRAME_60;
// Fixed update speed
extern int TICKS_PER_UPDATE;

enum Buttons {
  PaddleLeft = 0,
  PaddleRight,
};

enum GameState {
  Initializing,
  Running,
  PauseNormal,
  PauseWin,
  PauseClearGame,
  PauseLoseGame,
  PauseLoseLife
};

enum class CollisionType { None, Top, Middle, Bottom, Left, Right };

struct Contact {
  CollisionType type;
  Vector2D penetration;
};

#endif  // COMMON_H_
