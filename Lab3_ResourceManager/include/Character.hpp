#ifndef CHARACTERS_HPP
#define CHARACTERS_HPP

// I recommend a map for filling in the resource manager
#include <iterator>
#include <map>
#include <memory>
#include <string>

#include "BaseTexture.hpp"

namespace yx {

// Just a cheap little class to demonstrate loading characters.
class Character {
 public:
  Character(const std::string& name = "Character");

  ~Character();

  void init(int x, int y, BaseTexture* texture);

  void update(int x, int y, int frame);

  void render(SDL_Renderer* ren);
  std::string getName() const;
  void setName(const std::string& newName);
 private:
  int xPos_{0}, yPos_{0};
  unsigned int currentFrame_{0};
  unsigned int LastFrame_{7};
  // An SDL Surface contains pixel data to draw an image
  BaseTexture* texture_ = nullptr;
  SDL_Rect src_;
  SDL_Rect dest_;
  std::string name_;
};

}  // namespace yx

#endif  // CHARACTERS_HPP
