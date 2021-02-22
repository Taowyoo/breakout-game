#ifndef COMMON_H_
#define COMMON_H_

#include "TinyMath.hpp"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

const int GAME_SCENE_WIDTH = 640;
const int GAME_SCENE_LEFT = (WINDOW_WIDTH - GAME_SCENE_WIDTH) / 2;
const int GAME_SCENE_RIGHT = (WINDOW_WIDTH + GAME_SCENE_WIDTH) / 2;
const int WALL_WIDTH = 10;
const float PADDLE_SPEED = 0.75f;
const int PADDLE_WIDTH = 130;
const int PADDLE_HEIGHT = 10;
const int PADDLE_DISTANCE_FROM_BOTTOM = 50;

const float BALL_START_DEGREE = -115;
const float BALL_SPEED = 0.65f;
const int BALL_WIDTH = 6;
const int BALL_HEIGHT = 6;

const int BRICK_START_HEIGHT = 100;
const int BRICK_WIDTH = 50;
const int BRICK_HEIGHT = 25;
const int BRICK_INTERVAL = 2;
const int BRICK_ROW = 4;
const int BRICK_COLUMN = 12;
const int BRICK_DEFAULT_SCORE = 1;
const int PLAYER_DEFAULT_LIFE_NUM = 3;

const int DEFAULT_LEVEL = 1;

const int DEFAULT_FONT_SIZE = 28;
const int MENU_FONT_SIZE = 40;

const int SCREEN_FPS_60 = 60;
const int SCREEN_TICKS_PER_FRAME_60 = 1000 / SCREEN_FPS_60;
// Fixed update speed
const int TICKS_PER_UPDATE = 10;

const char FONT_PIXELGAME_PATH[] = "assets/fonts/PixelGameFont.ttf";
const char FONT_IPIX_PATH[] = "assets/fonts/IPixRegular.ttf";
const char FONT_WQY_PATH[] = "assets/fonts/WenQuanYiMicroHei.ttf";

enum Buttons {
  PaddleLeft = 0,
  PaddleRight,
};

enum GameState {
  Initializing,
  Running,
  PauseNormal,
  PauseWin,
  PauseLoseGame,
  PauseLoseLife
};

enum class CollisionType { None, Top, Middle, Bottom, Left, Right };

struct Contact {
  CollisionType type;
  Vector2D penetration;
};

#endif  // COMMON_H_
