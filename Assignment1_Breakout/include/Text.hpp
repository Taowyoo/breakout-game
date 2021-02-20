
#ifndef TEXT_H_
#define TEXT_H_

#if defined(LINUX) || defined(MINGW) || defined(__linux__)
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#else
// Windows and Mac use a different path
// If you have compilation errors, change this as needed.
#include <SDL.h>
#include <SDL_ttf.h>
#endif

#include <string>

#include "TinyMath.hpp"

class Text {
 public:
  Text(Vector2D position, SDL_Renderer* renderer, TTF_Font* font)
      : renderer(renderer), font(font), color{0xFF, 0xFF, 0xFF, 0xFF} {
    surface = TTF_RenderText_Solid(font, "", {0xFF, 0xFF, 0xFF, 0xFF});
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    int width, height;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    rect.x = static_cast<int>(position.x);
    rect.y = static_cast<int>(position.y);
    rect.w = width;
    rect.h = height;
  }

  ~Text() {
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
  }

  void SetText(const std::string& str) {
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    surface = TTF_RenderText_Solid(font, str.c_str(), color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    int width, height;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    rect.w = width;
    rect.h = height;
  }

  void Draw() { SDL_RenderCopy(renderer, texture, nullptr, &rect); }

  void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
  }

  SDL_Renderer* renderer;
  TTF_Font* font;
  SDL_Surface* surface{};
  SDL_Texture* texture{};
  SDL_Rect rect{};
  SDL_Color color{};
};

#endif  // TEXT_H_
