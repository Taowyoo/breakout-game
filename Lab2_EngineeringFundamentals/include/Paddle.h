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

class Paddle {
 public:
  Paddle(Vec2 position, Vec2 velocity)
      : position(position), velocity(velocity) {
    rect.x = static_cast<int>(position.x);
    rect.y = static_cast<int>(position.y);
    rect.w = PADDLE_WIDTH;
    rect.h = PADDLE_HEIGHT;
  }

  void Update(float dt) {
    position += velocity * dt;

    if (position.y < 0) {
      // Restrict to top of the screen
      position.y = 0;
    } else if (position.y > (WINDOW_HEIGHT - PADDLE_HEIGHT)) {
      // Restrict to bottom of the screen
      position.y = WINDOW_HEIGHT - PADDLE_HEIGHT;
    }
  }

  void Draw(SDL_Renderer* renderer) {
    rect.y = static_cast<int>(position.y);

    SDL_RenderFillRect(renderer, &rect);
  }

  Vec2 position;
  Vec2 velocity;
  SDL_Rect rect{};
};

#endif  // PADDLE_H_
