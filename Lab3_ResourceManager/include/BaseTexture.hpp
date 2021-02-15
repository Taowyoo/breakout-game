#ifndef BASE_TEXTURE_HPP
#define BASE_TEXTURE_HPP
#if defined(LINUX) || defined(MINGW) || defined(__linux__)
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#else
// Windows and Mac use a different path
// If you have compilation errors, change this as needed.
#include <SDL.h>
#include <SDL_image.h>
#endif

#include <string>

namespace yx {

class BaseTexture {
 private:
  /* data */
  // The actual hardware texture
  SDL_Texture *texture_;
  std::string name_;
  // Image dimensions
  int width_;
  int height_;

 public:
  BaseTexture(const std::string &name = "Not Set");
  ~BaseTexture();

  // Loads image at specified path
  bool loadFromFile(std::string path, SDL_Renderer *renderer);

  // Deallocates texture
  void free();

  // Set color modulation
  void setColor(Uint8 red, Uint8 green, Uint8 blue);

  // Set blending
  void setBlendMode(SDL_BlendMode blending);

  // Set alpha modulation
  void setAlpha(Uint8 alpha);

  // Renders texture at given point
  void render(int x, int y, SDL_Renderer *renderer, SDL_Rect *src = nullptr,
              SDL_Rect *dst = nullptr, double angle = 0.0,
              SDL_Point *center = nullptr,
              SDL_RendererFlip flip = SDL_FLIP_NONE);

  // Sets image dimensions
  void setWidth(int w);
  void setHeight(int h);
  // Gets image dimensions
  int getWidth() const;
  int getHeight() const;
};

}  // namespace yx

#endif  // BASE_TEXTURE_HPP