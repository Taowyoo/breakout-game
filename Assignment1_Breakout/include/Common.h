#ifndef COMMON_H_
#define COMMON_H_

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

const int GAME_SCENE_WIDTH = 800;
const int GAME_SCENE_LEFT = (WINDOW_WIDTH - GAME_SCENE_WIDTH) / 2;
const int GAME_SCENE_RIGHT = (WINDOW_WIDTH + GAME_SCENE_WIDTH) / 2;
const int WALL_WIDTH = 10;
const float PADDLE_SPEED = 0.75f;
const int PADDLE_WIDTH = 100;
const int PADDLE_HEIGHT = 15;
const int PADDLE_DISTANCE_FROM_BOTTOM = 50;
const float BALL_SPEED = 0.4f;
const int BALL_WIDTH = 10;
const int BALL_HEIGHT = 10;

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

const int SCREEN_FPS_60 = 60;
const int SCREEN_TICKS_PER_FRAME_60 = 1000 / SCREEN_FPS_60;
// Fixed update speed
const int TICKS_PER_UPDATE = 10;

enum Buttons {
  PaddleLeft = 0,
  PaddleRight,
};

enum GameState { Initializing, Running, PauseNormal, PauseWin, PauseLose };

enum class CollisionType { None, Top, Middle, Bottom, Left, Right };

struct Contact {
  CollisionType type;
  float penetration;
};

#endif  // COMMON_H_
