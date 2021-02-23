/**
 * @file Text.hpp
 * @author Yuxiang Cao (cao.yux@northeastern.edu)
 * @brief Text object class
 * @version 1.0.0
 * @date 2021-02-22 23:53:09 -08:00
 *
 * @copyright Copyright (c) 2021
 *
 */
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
/**
 * @brief A text wrapper class
 *
 */
class Text {
 public:
  /**
   * @brief Construct a new Text object
   *
   */
  Text() = default;
  /**
   * @brief Construct a new Text object
   *
   * @param position The position of the text
   * @param renderer Pinter to the renderer which used to render text
   * @param font Pinter to the font object
   */
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
  /**
   * @brief Update the text content
   *
   * @param str New string
   */
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
  /**
   * @brief Draw the text on screen
   *
   */
  void Draw() { SDL_RenderCopy(renderer.get(), texture.get(), nullptr, &rect); }
  /**
   * @brief Set the Position of the text
   *
   * @param position New position
   */
  void SetPosition(const Vector2D& position) {
    SetPosition(position.x, position.y);
  }
  /**
   * @brief Set the Position of the text
   *
   * @param x X-coordinate
   * @param y Y-coordinate
   */
  void SetPosition(int x, int y) {
    rect.x = x;
    rect.y = y;
  }
  /**
   * @brief Set the Color of the text
   *
   * @param r Red value
   * @param g Green value
   * @param b Blue value
   * @param a Alpha value
   */
  void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
  }
  /**
   * @brief Set the Position of the text by given it's Center position
   *
   * @param x Center position X-coordinate
   * @param y Center position Y-coordinate
   */
  void SetCenterPosition(int x, int y) {
    rect.x = x - rect.w / 2;
    rect.y = y - rect.h / 2;
  }
  /**
   * @brief Get the Center Position
   *
   * @return Vector2D Center Position in a 2D vector
   */
  Vector2D getCenterPosition() const {
    return Vector2D(rect.x + rect.w / 2, rect.y + rect.h / 2);
  }
  /**
   * @brief Set the text maintain the its center position when its size changed
   *
   * @param state Whether maintain
   */
  void setKeepCentered(bool state) { keepCentered = state; }
  /**
   * @brief Get the Width of the text
   *
   * @return int Width value
   */
  int getWidth() const { return rect.w; }
  /**
   * @brief Get the Height of the text
   *
   * @return int Height value
   */
  int getHeight() const { return rect.h; }
  /// Shared pointer to global SDL_Renderer
  std::shared_ptr<SDL_Renderer> renderer;
  /// Shared pointer to TTF_Font
  std::shared_ptr<TTF_Font> font;
  /// Shared pointer to SDL_Surface
  std::shared_ptr<SDL_Surface> surface;
  /// Shared pointer to SDL_Texture
  std::shared_ptr<SDL_Texture> texture;
  /// A Rectange store the position and height, with of current text
  SDL_Rect rect;
  /// Text's color
  SDL_Color color;
  /// The last text string, used to avoid updating by same string
  std::string lastText;
  /// Whether keep the center position
  bool keepCentered = false;
};

#endif  // TEXT_H_
