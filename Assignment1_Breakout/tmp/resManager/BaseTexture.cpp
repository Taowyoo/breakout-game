#include "BaseTexture.hpp"

namespace yx {

BaseTexture::BaseTexture(const std::string& name)
    : name_(name), texture_(nullptr), width_(0), height_(0) {}

BaseTexture::~BaseTexture() { free(); }

bool BaseTexture::loadFromFile(std::string path, SDL_Renderer* renderer) {
  // Get rid of preexisting texture
  free();

  // The final texture
  SDL_Texture* newTexture = nullptr;

  // Load image at specified path
  SDL_Surface* loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == nullptr) {
    SDL_Log("Unable to load image %s! SDL_image Error: %s", path.c_str(),
            IMG_GetError());
  } else {
    SDL_Log("Loaded %s", path.c_str());
    // Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (newTexture == nullptr) {
      SDL_Log("Unable to create texture from %s! SDL Error: %s", path.c_str(),
              SDL_GetError());
    } else {
      // Get image dimensions
      width_ = loadedSurface->w;
      height_ = loadedSurface->h;
    }

    // Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);
  }

  // Return success
  texture_ = newTexture;
  return texture_ != nullptr;
}

void BaseTexture::free() {
  // Free texture if it exists
  if (texture_ != nullptr) {
    SDL_DestroyTexture(texture_);
    texture_ = nullptr;
    width_ = 0;
    height_ = 0;
  }
}

void BaseTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
  // Modulate texture rgb
  SDL_SetTextureColorMod(texture_, red, green, blue);
}

void BaseTexture::setBlendMode(SDL_BlendMode blending) {
  // Set blending function
  SDL_SetTextureBlendMode(texture_, blending);
}

void BaseTexture::setAlpha(Uint8 alpha) {
  // Modulate texture alpha
  SDL_SetTextureAlphaMod(texture_, alpha);
}

void BaseTexture::render(int x, int y, SDL_Renderer* renderer, SDL_Rect* src,
                         SDL_Rect* dst, double angle, SDL_Point* center,
                         SDL_RendererFlip flip) {
  // Set rendering space and render to screen
  SDL_Rect dest = {x, y, width_, height_};
  if (dst == nullptr) {
    dst = &dest;
  }
  SDL_RenderCopyEx(renderer, texture_, src, dst, angle, center, flip);
}

void BaseTexture::setWidth(int w) { width_ = w; }
void BaseTexture::setHeight(int h) { height_ = h; }
int BaseTexture::getWidth() const { return width_; }
int BaseTexture::getHeight() const { return height_; }

}  // namespace yx
