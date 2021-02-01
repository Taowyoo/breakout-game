#pragma once

#include <cstdlib>

#if defined(LINUX) || defined(MINGW) || defined(__linux__)
#include <SDL2/SDL.h>
#else
// Windows and Mac use a different path
// If you have compilation errors, change this as needed.
#include <SDL.h>
#endif

/**
 * @brief Rectangle Object class, maintain info of each rectangle object
 *
 */
class Rectangle {
public:
  Rectangle() {
    // Empty constructor! We haev complete control!
  }

  // Okay, but do not forget to call this!
  void init(int screenWidth, int screenHeight);

  // Arguments here are a little redundant--do we need them?
  // (Perhaps if the screen resizes? Hmm!)
  void update(int screenWidth, int screenHeight);

  // Okay, render our rectangles!
  void render(SDL_Renderer *gRenderer);

private:
  int x{100};
  int y{100};
  int w{100};
  int h{100};
  int speed{1};
  bool up{true};
  bool left{true};
};