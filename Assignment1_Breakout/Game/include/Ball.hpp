
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
  Ball()
      : Ball(Vector2D{(WINDOW_WIDTH - BALL_WIDTH) / 2,
                      WINDOW_HEIGHT - PADDLE_HEIGHT - BALL_HEIGHT -
                          PADDLE_DISTANCE_FROM_BOTTOM},
             Vector2D{BALL_SPEED, 0}.getRotatedVector(BALL_START_DEGREE)) {}
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
    position += contact.penetration;
    velocity.y = -velocity.y;

    // if (contact.type == CollisionType::Left) {
    //   velocity.x = -.75f * BALL_SPEED;
    // } else if (contact.type == CollisionType::Right) {
    //   velocity.x = 0.75f * BALL_SPEED;
    // }

    // Get a random  degree in range of [-2,2]
    float randomDegreeChange =
        static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 4 - 2;
    // Add  degree change to ball after collision
    velocity = velocity.getRotatedVector(randomDegreeChange);
  }

  void CollideWithWall(Contact const& contact) {
    if (contact.type == CollisionType::Top) {
      position += contact.penetration;
      velocity.y = -velocity.y;
    } else if (contact.type == CollisionType::Bottom) {
      position += contact.penetration;
      velocity.y = -velocity.y;
    } else if (contact.type == CollisionType::Left ||
               contact.type == CollisionType::Right) {
      position += contact.penetration;
      velocity.x = -velocity.x;
    }
  }
  void CollideWithBrick(Contact const& contact) {
    if (contact.type == CollisionType::Top ||
        contact.type == CollisionType::Bottom) {
      position += contact.penetration;
      velocity.y = -velocity.y;
    } else if (contact.type == CollisionType::Left ||
               contact.type == CollisionType::Right) {
      position += contact.penetration;
      velocity.x = -velocity.x;
    }
  }

  Vector2D position;
  Vector2D velocity;
  SDL_Rect rect{};
};

#endif  // BALL_H_
