#ifndef PADDLE_H_
#define PADDLE_H_

#if defined(LINUX) || defined(MINGW) || defined(__linux__)
#include <SDL2/SDL.h>
#else
// Windows and Mac use a different path
// If you have compilation errors, change this as needed.
#include <SDL.h>
#endif

#include "Common.h"
#include "Rectangle.hpp"
#include "TinyMath.hpp"

class Paddle : public Rectangle {
 public:
  Paddle(Vector2D position, Vector2D velocity)
      : Rectangle(position, PADDLE_WIDTH, PADDLE_HEIGHT), velocity(velocity) {
    rect.y = std::min(rect.y, WINDOW_HEIGHT - rect.h);
  }

  void Update(float dt) {
    position += velocity * dt;

    if (position.x < GAME_SCENE_LEFT) {
      // Restrict to top of the screen
      position.x = GAME_SCENE_LEFT;
    } else if (position.x > GAME_SCENE_RIGHT - PADDLE_WIDTH) {
      // Restrict to bottom of the screen
      position.x = GAME_SCENE_RIGHT - PADDLE_WIDTH;
    }
  }

  void Draw(SDL_Renderer* renderer) {
    rect.x = static_cast<int>(position.x);
    SDL_RenderFillRect(renderer, &rect);
  }

  Vector2D velocity;
};

#endif  // PADDLE_H_
