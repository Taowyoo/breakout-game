
#ifndef BALL_H_
#define BALL_H_

#include "Common.h"
#include "TinyMath.hpp"

#if defined(LINUX) || defined(MINGW) || defined(__linux__)
#include <SDL2/SDL.h>
#else
// Windows and Mac use a different path
// If you have compilation errors, change this as needed.
#include <SDL.h>
#endif

class Ball {
 public:
  Ball(Vector2D position, Vector2D velocity)
      : position(position), velocity(velocity) {
    rect.x = static_cast<int>(position.x);
    rect.y = static_cast<int>(position.y);
    rect.w = BALL_WIDTH;
    rect.h = BALL_HEIGHT;
  }

  void Update(float dt) { position += velocity * dt; }

  void Draw(SDL_Renderer* renderer) {
    rect.x = static_cast<int>(position.x);
    rect.y = static_cast<int>(position.y);

    SDL_RenderFillRect(renderer, &rect);
  }

  void CollideWithPaddle(Contact const& contact) {
    position.y += contact.penetration;
    velocity.y = -velocity.y;

    if (contact.type == CollisionType::Top) {
      velocity.x = -.75f * BALL_SPEED;
    } else if (contact.type == CollisionType::Bottom) {
      velocity.x = 0.75f * BALL_SPEED;
    }
  }

  void CollideWithWall(Contact const& contact) {
    if (contact.type == CollisionType::Top) {
      position.y += contact.penetration;
      velocity.y = -velocity.y;
    } else if (contact.type == CollisionType::Bottom) {
      position.y += contact.penetration;
      velocity.y = -velocity.y;
    } else if (contact.type == CollisionType::Left ||
               contact.type == CollisionType::Right) {
      position.x += contact.penetration;
      velocity.x = -velocity.x;
    }
  }

  Vector2D position;
  Vector2D velocity;
  SDL_Rect rect{};
};

#endif  // BALL_H_
