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

class Rectangle {
 public:
  Rectangle() = default;
  Rectangle(Vector2D position, int w, int h) : position(position) {
    rect.x = static_cast<int>(position.x);
    rect.y = static_cast<int>(position.y);
    rect.w = w;
    rect.h = h;
  }

  void Draw(SDL_Renderer* renderer) {
    // SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
  }
  // void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
  //   color.r = r;
  //   color.g = g;
  //   color.b = b;
  //   color.a = a;
  // }
  // void SetColor(const SDL_Color& c) {
  //   color.r = c.r;
  //   color.g = c.g;
  //   color.b = c.b;
  //   color.a = c.a;
  // }
  Vector2D position;
  SDL_Rect rect{};
  // SDL_Color color{};
};

#endif  // RECTANGLE_H_
