#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

// I recommend a map for filling in the resource manager
#include <iterator>
#include <map>
#include <memory>
#include <string>

// Try toggling this number!
#define CHARACTERS 50

// Just a cheap little class to demonstrate loading characters.
class Character {
 public:
  Character();

  ~Character();

  void init(int x, int y, SDL_Texture* texture);

  void update(int x, int y, int frame);

  void render(SDL_Renderer* ren);

 private:
  int xPos_{0}, yPos_{0};
  unsigned int currentFrame_{0};
  unsigned int LastFrame_{7};
  // An SDL Surface contains pixel data to draw an image
  SDL_Texture* texture_ = nullptr;
  SDL_Rect src_;
  SDL_Rect dest_;
};

#endif
