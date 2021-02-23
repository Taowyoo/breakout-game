/**
 * @file Ball.hpp
 * @author Yuxiang Cao (cao.yux@northeastern.edu)
 * @brief Ball object class
 * @version 1.0.0
 * @date 2021-02-22 21:54:19 -08:00
 *
 * @copyright Copyright (c) 2021
 *
 */
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

/**
 * @brief Represent the ball object in the break out game.
 * Record velocity, position etc. info of the ball.
 *
 */
class Ball {
 public:
  /**
   * @brief Construct a default all 0 value Ball object
   *
   */
  Ball() = default;
  /**
   * @brief Construct a new Ball object
   *
   * @param position Initial position
   * @param velocity The velocity of the ball
   */
  Ball(Vector2D position, Vector2D velocity)
      : position(position), velocity(velocity) {
    rect.x = static_cast<int>(position.x);
    rect.y = static_cast<int>(position.y);
    rect.w = BALL_WIDTH;
    rect.h = BALL_HEIGHT;
  }

  /**
   * @brief Update the state of the ball
   *
   * @param dt Time in milliseconds passed from last update
   */
  void Update(float dt) { position += velocity * dt; }
  /**
   * @brief Draw ball on screen
   *
   * @param renderer Global renderer pointer
   */
  void Draw(SDL_Renderer* renderer) {
    rect.x = static_cast<int>(position.x);
    rect.y = static_cast<int>(position.y);

    SDL_RenderFillRect(renderer, &rect);
  }

  /**
   * @brief Update ball's state when collide with paddle
   *
   * @param contact Collision info
   */
  void CollideWithPaddle(Contact const& contact) {
    position += contact.penetration;
    velocity.y = -velocity.y;
    // Get a random  degree in range of [-2,2]
    float randomDegreeChange =
        static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 4 - 2;
    // Add  degree change to ball after collision
    velocity = velocity.getRotatedVector(randomDegreeChange);
  }
  /**
   * @brief Update ball's state when collide with wall
   *
   * @param contact Collision info
   */
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
  /**
   * @brief Update ball's state when collide with brick
   *
   * @param contact Collision info
   */
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
  /**
   * @brief 2D vector to store ball's position
   *
   */
  Vector2D position;
  /**
   * @brief 2D vector to store ball's velocity
   *
   */
  Vector2D velocity;
  /**
   * @brief A rectangle struct with left top position , height, width
   *
   */
  SDL_Rect rect{};
};

#endif  // BALL_H_
