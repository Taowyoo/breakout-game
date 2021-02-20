#ifndef COMMON_H_
#define COMMON_H_

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

const int GAME_SCENE_WIDTH = 800;
const int GAME_SCENE_LEFT = (WINDOW_WIDTH - GAME_SCENE_WIDTH) / 2;
const int GAME_SCENE_RIGHT = (WINDOW_WIDTH + GAME_SCENE_WIDTH) / 2;
const int WALL_WIDTH = 10;
const float PADDLE_SPEED = 1.0f;
const int PADDLE_WIDTH = 100;
const int PADDLE_HEIGHT = 10;

const float BALL_SPEED = 1.0f;
const int BALL_WIDTH = 10;
const int BALL_HEIGHT = 10;

const int BRICK_WIDTH = 100;
const int BRICK_HEIGHT = 20;

enum Buttons {
  PaddleOneUp = 0,
  PaddleOneDown,
  PaddleTwoUp,
  PaddleTwoDown,
};

enum class CollisionType { None, Top, Middle, Bottom, Left, Right };

struct Contact {
  CollisionType type;
  float penetration;
};

#endif  // COMMON_H_
