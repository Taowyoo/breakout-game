/**
 * @file Paddle.hpp
 * @author Yuxiang Cao (cao.yux@northeastern.edu)
 * @brief Paddle object Class
 * @version 1.0.0
 * @date 2021-02-23 00:01:56 -08:00
 *
 * @copyright Copyright (c) 2021
 *
 */
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
/**
 * @brief Paddle object class
 *
 * Keep track the info of the paddle in the game
 */
class Paddle : public Rectangle {
 public:
  /**
   * @brief Construct a new Paddle object
   *
   */
  Paddle() = default;
  /**
   * @brief Construct a new Paddle object
   *
   * @param position Start position
   * @param velocity Inital velocity
   */
  Paddle(Vector2D position, Vector2D velocity)
      : Rectangle(position, PADDLE_WIDTH, PADDLE_HEIGHT), velocity(velocity) {
    rect.y = std::min(rect.y, WINDOW_HEIGHT - rect.h);
  }
  /**
   * @brief Update paddle state
   *
   * @param dt Milliseconds from last updated
   */
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
  /**
   * @brief Draw the paddle on the screen
   *
   * @param renderer The global SDL_Renderer
   */
  void Draw(SDL_Renderer* renderer) {
    rect.x = static_cast<int>(position.x);
    SDL_RenderFillRect(renderer, &rect);
  }
  /// The current velocity of the paddle
  Vector2D velocity;
};

#endif  // PADDLE_H_
