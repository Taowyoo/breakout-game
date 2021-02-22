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

class Wall : public Rectangle {
 public:
  Wall() = default;
  Wall(Vector2D position, int width)
      : Rectangle(position, width, WINDOW_HEIGHT) {
    position.y = 0;
    rect.y = static_cast<int>(position.y);
  }
};

#endif  // WALL_HPP
