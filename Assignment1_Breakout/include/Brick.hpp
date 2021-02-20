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

class Brick : public Rectangle {
 public:
  Brick(Vector2D position, bool active = false)
      : Rectangle(position, BRICK_WIDTH, BRICK_HEIGHT), active(active) {}

  bool isActive() const { return active; }
  void setActive(bool state) { active = state; }
  bool active;
};
#endif  // BRICK_HPP
