
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
  Text() = default;
  Text(Vector2D position, std::shared_ptr<SDL_Renderer> renderer,
       std::shared_ptr<TTF_Font> font)
      : renderer(renderer),
        font(font),
        color{0xFF, 0xFF, 0xFF, 0xFF},
        lastText("") {
    surface = std::shared_ptr<SDL_Surface>(
        TTF_RenderText_Solid(font.get(), lastText.c_str(),
                             {0xFF, 0xFF, 0xFF, 0xFF}),
        SDL_FreeSurface);
    texture = std::shared_ptr<SDL_Texture>(
        SDL_CreateTextureFromSurface(renderer.get(), surface.get()),
        SDL_DestroyTexture);

    int width, height;
    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);

    rect.x = static_cast<int>(position.x);
    rect.y = static_cast<int>(position.y);
    rect.w = width;
    rect.h = height;
  }
  void SetText(const std::string& str) {
    if (str != lastText) {
      surface = std::shared_ptr<SDL_Surface>(
          TTF_RenderUTF8_Solid(font.get(), str.c_str(), color),
          SDL_FreeSurface);
      texture = std::shared_ptr<SDL_Texture>(
          SDL_CreateTextureFromSurface(renderer.get(), surface.get()),
          SDL_DestroyTexture);

      lastText = str;
      int width, height;
      SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
      if (keepCentered) {
        Vector2D oldCenterPos = getCenterPosition();
        rect.w = width;
        rect.h = height;
        SetCenterPosition(oldCenterPos.x, oldCenterPos.y);
      } else {
        rect.w = width;
        rect.h = height;
      }
    }
  }
  void Draw() { SDL_RenderCopy(renderer.get(), texture.get(), nullptr, &rect); }
  void SetPosition(const Vector2D& position) {
    SetPosition(position.x, position.y);
  }
  void SetPosition(int x, int y) {
    rect.x = x;
    rect.y = y;
  }
  void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
  }

  void SetCenterPosition(int x, int y) {
    rect.x = x - rect.w / 2;
    rect.y = y - rect.h / 2;
  }
  Vector2D getCenterPosition() const {
    return Vector2D(rect.x + rect.w / 2, rect.y + rect.h / 2);
  }
  void setKeepCentered(bool state) { keepCentered = state; }
  int getWidth() const { return rect.w; }
  int getHeight() const { return rect.h; }
  std::shared_ptr<SDL_Renderer> renderer;
  std::shared_ptr<TTF_Font> font;
  std::shared_ptr<SDL_Surface> surface;
  std::shared_ptr<SDL_Texture> texture;
  SDL_Rect rect;
  SDL_Color color;
  std::string lastText;
  bool keepCentered = false;
};

#endif  // TEXT_H_
