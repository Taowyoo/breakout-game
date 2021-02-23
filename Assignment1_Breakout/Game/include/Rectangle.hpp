/**
 * @file Rectangle.hpp
 * @author Yuxiang Cao (cao.yux@northeastern.edu)
 * @brief A rectangle class
 * @version 1.0.0
 * @date 2021-02-23 00:07:43 -08:00
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#if defined(LINUX) || defined(MINGW) || defined(__linux__)
#include <SDL2/SDL.h>
#else
// Windows and Mac use a different path
// If you have compilation errors, change this as needed.
#include <SDL.h>
#endif

#include "Common.h"
#include "TinyMath.hpp"
/**
 * @brief A simple rectange class to represnet a rectangle on screen
 *
 */
class Rectangle {
 public:
  /**
   * @brief Construct a new Rectangle object
   *
   */
  Rectangle() = default;
  /**
   * @brief Construct a new Rectangle object
   *
   * @param position Position of the Rectangle
   * @param w Width of the Rectangle
   * @param h Height of the Rectangle
   */
  Rectangle(Vector2D position, int w, int h) : position(position) {
    rect.x = static_cast<int>(position.x);
    rect.y = static_cast<int>(position.y);
    rect.w = w;
    rect.h = h;
  }
  /**
   * @brief Draw the rectangle on screen
   *
   * @param renderer The pointer to the global SDL_Renderer
   */
  void Draw(SDL_Renderer* renderer) { SDL_RenderFillRect(renderer, &rect); }

  /// The position of this rectangle
  Vector2D position;
  /**
   * @brief A rectangle struct with left top position , height, width
   *
   */
  SDL_Rect rect{};
};

#endif  // RECTANGLE_H_
