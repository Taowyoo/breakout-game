/**
 * @file Brick.hpp
 * @author Yuxiang Cao (cao.yux@northeastern.edu)
 * @brief Brick object class
 * @version 1.0.0
 * @date 2021-02-22 22:44:19 -08:00
 *
 * @copyright Copyright (c) 2021
 *
 */
#if !defined(BRICK_HPP)
#define BRICK_HPP

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
 * @brief Brick object Class
 *
 * Store info of a brick: position,score whether active ...
 */
class Brick : public Rectangle {
  bool active;
  int score = BRICK_DEFAULT_SCORE;

 public:
  /**
   * @brief Construct a new Brick object
   *
   * @param position Position
   * @param active Whether active
   */
  Brick(Vector2D position, bool active = false)
      : Rectangle(position, BRICK_WIDTH, BRICK_HEIGHT), active(active) {}
  /**
   * @brief Whether active
   *
   * @return true Active
   * @return false Inactive
   */
  bool isActive() const { return active; }
  /**
   * @brief Set the active state
   *
   * @param state New state
   */
  void setActive(bool state) { active = state; }
  /**
   * @brief Get the score of this brick
   *
   * @return int Score value
   */
  int getScore() const { return score; }
  /**
   * @brief Set the brick's score
   *
   * @param score Score value
   */
  void setScore(int score) { this->score = score; }
  /**
   * @brief Draw brick on screen
   *
   * @param renderer Global SDL_Renderer pointer
   */
  void Draw(SDL_Renderer* renderer) {
    if (active) SDL_RenderFillRect(renderer, &rect);
  }
};
#endif  // BRICK_HPP
