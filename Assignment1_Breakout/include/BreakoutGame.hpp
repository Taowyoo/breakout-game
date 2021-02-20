#ifndef BREAKOUTGAME_HPP
#define BREAKOUTGAME_HPP

// ==================== Libraries ==================
// Depending on the operating system we use
// The paths to SDL are actually different.
// The #define statement should be passed in
// when compiling using the -D argument.
// This gives an example of how a programmer
// may support multiple platforms with different
// dependencies.
//
// Note that your path may be different depending on where you intalled things
//
//
#if defined(LINUX) || defined(MINGW) || defined(__linux__)
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#else
// Windows and Mac use a different path
// If you have compilation errors, change this as needed.
#include <SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#endif

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "Ball.hpp"
#include "Brick.hpp"
#include "Common.h"
#include "Paddle.hpp"
#include "Text.hpp"
#include "Wall.hpp"

// This class sets up a full graphics program
class BreakoutGame {
 public:
  // Constructor
  BreakoutGame(int w, int h);
  // Desctructor
  ~BreakoutGame();
  // Per frame update
  void update();
  // Renders shapes to the screen
  void render();
  // loop that runs forever
  void loop();
  // Get Pointer to Window
  SDL_Window* getSDLWindow();
  // Get Pointer to Renderer
  SDL_Renderer* getSDLRenderer();

 private:
  // Screen dimension constants
  int screenHeight;
  int screenWidth;
  // The window we'll be rendering to
  SDL_Window* gWindow;
  // SDL Renderer
  SDL_Renderer* gRenderer = NULL;
  // Text font
  TTF_Font* font_;
  Wall wallLeft;
  Wall wallRight;
  Ball ball;
  // TODO: Use smart pointer to store texts
  //   Text score;
  //   Text lives;
  //   Text level;
  Paddle paddle;
  std::vector<Brick> bricks;
};

#endif
