#ifndef SDLGRAPHICSPROGRAM
#define SDLGRAPHICSPROGRAM

// ==================== Libraries ==================
// Depending on the operating system we use
// The paths to SDL are actually different.
// The #define statement should be passed in
// when compiling using the -D argument.
// This gives an example of how a programmer
// may support multiple platforms with different
// dependencies.
#if defined(LINUX) || defined(MINGW) || defined(__linux__)
  #include <SDL2/SDL.h>
  #include <SDL2/SDL_log.h>
#else
// Windows and Mac use a different path
// If you have compilation errors, change this as needed.
  #include <SDL.h>
  #include <SDL_log.h>
#endif

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <time.h> /* time */

#include "LTexture.h"

// This class sets up a full graphics program
class SDLGraphicsProgram {
public:
  // Constructor
  SDLGraphicsProgram(int w, int h);
  // Desctructor
  ~SDLGraphicsProgram();
  // Per frame update
  void update();
  // Renders shapes to the screen
  void render();
  // loop that runs forever
  void loop();
  // Get Pointer to Window
  SDL_Window *getSDLWindow();
  // Get Pointer to Renderer
  SDL_Renderer *getSDLRenderer();

private:
  // Screen dimension constants
  int screenHeight;
  int screenWidth;
  // The window we'll be rendering to
  SDL_Window *gWindow = NULL;
  // SDL Renderer
  SDL_Renderer *gRenderer = NULL;

  // Font
  TTF_Font* gFont = NULL;

  // Scene textures
  LTexture gFPSTextTexture;

  // Average Frames per seoncd
  Uint32 avgFPS = 0;
};

#endif
