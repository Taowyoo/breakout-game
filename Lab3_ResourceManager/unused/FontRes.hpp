#if !defined(FONT_RES_HPP)
#define FONT_RES_HPP

#include "BaseResource.hpp"
#if defined(LINUX) || defined(MINGW) || defined(__linux__)
#include <SDL2/SDL_ttf.h>
#else
// Windows and Mac use a different path
// If you have compilation errors, change this as needed.
#include <SDL2/SDL_ttf.h>
#endif
#include <iostream>
#include <memory>

class FontRes : public BaseResource {
 private:
  std::shared_ptr<TTF_Font> font;

 public:
  FontRes(const std::string& resourceFileName, void* args)
      : BaseResource(resourceFileName, args) {}
  ~FontRes(){};
  void LoadFromFile(const std::string& resourcePath, void* args) {
    font = std::shared_ptr<TTF_Font>(
        TTF_OpenFont(resourcePath.c_str(), *((int*)args)), TTF_CloseFont);
    if (font == nullptr) {
      std::cerr << "Font file could not be loaded! SDL_ttf Error: "
                << TTF_GetError() << "\n";
    }
  }
  std::shared_ptr<TTF_Font> getRes() const { return font; }
};
#endif  // FONT_RES_HPP
