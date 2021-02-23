/**
 * @file Wall.hpp
 * @author Yuxiang Cao (cao.yux@northeastern.edu)
 * @brief Wall object class header
 * @version 1.0.0
 * @date 2021-02-22 23:26:56 -08:00
 *
 * @copyright Copyright (c) 2021
 *
 */
#if !defined(WALL_HPP)
#define WALL_HPP

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
 * @brief Wall object Class
 *
 * Store position info and width of the wall
 */
class Wall : public Rectangle {
 public:
  /**
   * @brief Construct a new Wall object
   *
   */
  Wall() = default;
  /**
   * @brief Construct a new Wall object
   *
   * @param position Wall position
   * @param width Wall width
   */
  Wall(Vector2D position, int width)
      : Rectangle(position, width, WINDOW_HEIGHT) {
    position.y = 0;
    rect.y = static_cast<int>(position.y);
  }
};

#endif  // WALL_HPP
