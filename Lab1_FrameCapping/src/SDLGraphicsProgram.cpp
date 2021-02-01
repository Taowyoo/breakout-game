#include "SDLGraphicsProgram.h"

#include "LTimer.h"
#include "Rectangle.h"

// Try toggling this number!
#define BLOCKS 600

// Fixed FPS variables
const Uint32 SCREEN_60FPS = 60;
const Uint32 SCREEN_30FPS = 30;
const Uint32 SCREEN_TICKS_PER_FRAME_60 = 1000 / SCREEN_60FPS;
const Uint32 SCREEN_TICKS_PER_FRAME_30 = 1000 / SCREEN_30FPS;
// Fixed update speed
const Uint32 TICKS_PER_UPDATE = 10;

// Create our list of rectangles!
Rectangle r[BLOCKS];

//Set text color as Green
SDL_Color textColor = { 0, 255, 0, 255 };

// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
SDLGraphicsProgram::SDLGraphicsProgram(int w, int h)
    : screenWidth(w), screenHeight(h) {
  // Initialize random number generation.
  srand(time(NULL));
  // Setup blocks
  for (int i = 0; i < BLOCKS; ++i) {
    r[i].init(screenWidth, screenHeight);
  }

  // Initialization flag
  bool success = true;
  // String to hold any errors that occur.
  std::stringstream errorStream;
  // The window we'll be rendering to
  gWindow = NULL;
  // Render flag

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError()
                << "\n";
    success = false;
  } else {
    // Create window
    gWindow = SDL_CreateWindow("Lab", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, screenWidth,
                               screenHeight, SDL_WINDOW_SHOWN);

    // Check if Window did not create.
    if (gWindow == NULL) {
      errorStream << "Window could not be created! SDL Error: "
                  << SDL_GetError() << "\n";
      success = false;
    } else {
      // Create a Renderer to draw on
      gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
      // Check if Renderer did not create.
      if (gRenderer == NULL) {
        errorStream << "Renderer could not be created! SDL Error: "
                    << SDL_GetError() << "\n";
        success = false;
      } else {
        // Initialize SDL_ttf
        if (TTF_Init() == -1) {
          errorStream << "SDL_ttf could not initialize! SDL_ttf Error: "
                      << TTF_GetError() << "\n";
          success = false;
        } else {
          gFont = TTF_OpenFont("lazy.ttf", 28);
          if (gFont == NULL) {
            errorStream << "Failed to load lazy font! SDL_ttf Error: "
                        << TTF_GetError() << "\n";
            success = false;
          }
        }
      }
    }
    
  }

  // If initialization did not work, then print out a list of errors in the
  // constructor.
  if (!success) {
    errorStream << "Failed to initialize!\n\n";
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", errorStream.str().c_str());
  } else {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "No SDL, or OpenGL, errors Detected\n\n");
  }
}

// Proper shutdown and destroy initialized objects
SDLGraphicsProgram::~SDLGraphicsProgram() {
  //Free loaded images
	gFPSTextTexture.free();
  // Destroy Renderer
  SDL_DestroyRenderer(gRenderer);
  // Destroy window
  SDL_DestroyWindow(gWindow);
  //Free global font
	TTF_CloseFont( gFont );
  // Point gWindow to NULL to ensure it points to nothing.
  gFont = NULL;
  gRenderer = NULL;
  gWindow = NULL;
  // Quit SDL subsystems
  TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

// Update OpenGL
void SDLGraphicsProgram::update() {
  // Nothing yet!
  SDL_SetRenderDrawColor(gRenderer, 0x22, 0x22, 0x22, 0xFF);
  SDL_RenderClear(gRenderer);
  // update all rectangles' state
  for (int i = 0; i < BLOCKS; i++) {
    r[i].update(screenWidth, screenHeight);
  }
  std::string text = "FPS: " + std::to_string(avgFPS) + ", Press SPACE to change FPS between 60 & 30";

  // Update FPS Text Texture
  if(!gFPSTextTexture.loadFromRenderedText(text, textColor, gRenderer, gFont))
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR , "Unable to render FPS texture!\n" );
  }
}

// Render
// The render function gets called once per loop
void SDLGraphicsProgram::render() {
  for (int i = 0; i < BLOCKS; i++) {
    r[i].render(getSDLRenderer());
  }
  //Render textures
  gFPSTextTexture.render(( screenWidth - gFPSTextTexture.getWidth() ) / 2, ( screenHeight - gFPSTextTexture.getHeight() ) / 2, gRenderer);
  //Update screen
  SDL_RenderPresent(gRenderer);
}

// Loops forever!
void SDLGraphicsProgram::loop() {
  // Main loop flag
  // If this is quit = 'true' then the program terminates.
  bool quit = false;
  // Event handler that handles various events in SDL
  // that are related to input and output
  SDL_Event e;

  // The frames per second timer
  LTimer fpsTimer;
  //The frames per second cap timer
  LTimer capTimer;
  Uint32 fixedTicks = SCREEN_TICKS_PER_FRAME_60;
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,"Please press SPACE key to change FPS between 60 & 30!");

  
  
  // Update timer
  LTimer updateTimer;
  Uint32 previous = 0;
  Uint32 lag = 0;
  updateTimer.start();
  // Start counting frames per second
  Uint32 countedFrames = 0;
  fpsTimer.start();
  // Start update timer
  // Enable text input
  SDL_StartTextInput();
  // While application is running
  while (!quit) {
    //Start cap timer
    capTimer.start();

    Uint32 current = updateTimer.getTicks();
    Uint32 elapsed = current - previous;
    previous = current;
    lag += elapsed;

    // Handle events on queue
    while (SDL_PollEvent(&e) != 0) {
      // User posts an event to quit
      // An example is hitting the "x" in the corner of the window.
      if (e.type == SDL_QUIT) {
        quit = true;
      }
      if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE){
        if(fixedTicks == SCREEN_TICKS_PER_FRAME_60){
          fixedTicks = SCREEN_TICKS_PER_FRAME_30;
          SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,"Changed Fixed FPS to %u",SCREEN_30FPS);
        }
        else{
          fixedTicks = SCREEN_TICKS_PER_FRAME_60;
          SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,"Changed Fixed FPS to %u",SCREEN_60FPS);
        }
      }
    }

    // get current passed time in millisecond
    auto mSecPassed = fpsTimer.getTicks();
    // Update average FPS every second
    if (mSecPassed >= 1000)
    {
      // Update average FPS
      avgFPS = countedFrames / ( mSecPassed/ 1000.f);
      fprintf(stderr, "\rFPS: %u\r",avgFPS);
      countedFrames = 0;
      // Reset timer
      fpsTimer.start();
    }

    // Update our scene
    while (lag >= TICKS_PER_UPDATE)
    {
      update();
      lag -= TICKS_PER_UPDATE;
    }

    // Render using OpenGL
    render();
    // Update screen of our specified window
    // SDL_GL_SwapWindow(getSDLWindow());
    ++countedFrames;

    //If frame finished early
    Uint32 frameTicks = capTimer.getTicks();
    if( frameTicks < fixedTicks )
    {
        //Wait remaining time
        SDL_Delay( fixedTicks - frameTicks );
    }
  }

  // Disable text input
  SDL_StopTextInput();
}

// Get Pointer to Window
SDL_Window* SDLGraphicsProgram::getSDLWindow() { return gWindow; }

// Get Pointer to Renderer
SDL_Renderer* SDLGraphicsProgram::getSDLRenderer() { return gRenderer; }
