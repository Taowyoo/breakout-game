#include "BreakoutGame.hpp"

// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
BreakoutGame::BreakoutGame(int w, int h)
    : screenWidth(w),
      screenHeight(h),
      // Initialize game objects
      // Wall
      wallLeft(Vector2D{GAME_SCENE_LEFT - WALL_WIDTH, 0}, WALL_WIDTH),
      wallRight(Vector2D{GAME_SCENE_RIGHT, 0}, WALL_WIDTH),
      // Ball
      ball(Vector2D{(WINDOW_WIDTH - BALL_WIDTH) / 2,
                    WINDOW_HEIGHT - PADDLE_HEIGHT - BALL_HEIGHT},
           Vector2D{0, -BALL_SPEED}),
      // Paddles
      paddle(Vector2D{(WINDOW_WIDTH - PADDLE_WIDTH) / 2,
                      WINDOW_HEIGHT - PADDLE_HEIGHT},
             Vector2D{PADDLE_SPEED, 0}) {
  // Initialize random number generation.
  srand(time(NULL));

  // Initialization flag
  bool success = true;
  // String to hold any errors that occur.
  std::stringstream errorStream;
  // The window we'll be rendering to
  gWindow = NULL;
  // Render flag

  // Initialize SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError()
                << "\n";
    success = false;
  } else {
    // Open Audio
    int ret = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    if (ret < 0) {
      errorStream << "Audio could not be opened! SDL_Mix Error: "
                  << Mix_GetError() << "\n";
      success = false;
    }
    // // Initialize sound effects
    // wallHitSound = Mix_LoadWAV("media/WallHit.wav");
    // if (wallHitSound == nullptr) {
    //   errorStream << "Sound file could not be loaded! SDL_Mix Error: "
    //               << Mix_GetError() << "\n";
    //   success = false;
    // }
    // paddleHitSound = Mix_LoadWAV("media/PaddleHit.wav");
    // if (paddleHitSound == nullptr) {
    //   errorStream << "Sound file could not be loaded! SDL_Mix Error: "
    //               << Mix_GetError() << "\n";
    //   success = false;
    // }
    // winSound = Mix_LoadWAV("media/Win.wav");
    // if (paddleHitSound == nullptr) {
    //   errorStream << "Sound file could not be loaded! SDL_Mix Error: "
    //               << Mix_GetError() << "\n";
    //   success = false;
    // }

    // Create window
    gWindow = SDL_CreateWindow("Lab", 100, 100, screenWidth, screenHeight,
                               SDL_WINDOW_SHOWN);

    // Check if Window did not create.
    if (gWindow == NULL) {
      errorStream << "Window could not be created! SDL Error: "
                  << SDL_GetError() << "\n";
      success = false;
    }

    // Create a Renderer to draw on
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    // Check if Renderer did not create.
    if (gRenderer == NULL) {
      errorStream << "Renderer could not be created! SDL Error: "
                  << SDL_GetError() << "\n";
      success = false;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
      errorStream << "SDL_ttf could not initialize! SDL_ttf Error: "
                  << TTF_GetError() << "\n";
      success = false;
    } else {
      font_ = TTF_OpenFont("fonts/IPixRegular.ttf", 28);
      if (font_ == nullptr) {
        errorStream << "Failed to load lazy font! SDL_ttf Error: "
                    << TTF_GetError() << "\n";
        success = false;
      }
    }
  }

  // Texts
  // TODO: Use smart pointer
  // // Score
  // score = Text(Vector2D{}, gRenderer, font_);
  // // Current rest life
  // lives = Text(Vector2D{}, gRenderer, font_);
  // // Current Level
  // level = Text(Vector2D{}, gRenderer, font_);

  // Bricks
  // TODO: Init bricks array

  // If initialization did not work, then print out a list of errors in the
  // constructor.
  if (!success) {
    errorStream << "Failed to initialize!\n";
    std::string errors = errorStream.str();
    std::cout << errors << "\n";
  } else {
    std::cout << "No SDL errors Detected in during init\n\n";
  }
}

// Proper shutdown and destroy initialized objects
BreakoutGame::~BreakoutGame() {
  // Destroy Renderer
  SDL_DestroyRenderer(gRenderer);
  // Destroy window
  SDL_DestroyWindow(gWindow);
  // Point gWindow to NULL to ensure it points to nothing.
  gRenderer = NULL;
  gWindow = NULL;
  // Quit SDL subsystems
  SDL_Quit();
}

// Update OpenGL
void BreakoutGame::update() {}

// Render
// The render function gets called once per loop
void BreakoutGame::render() {
  SDL_SetRenderDrawColor(gRenderer, 0x22, 0x22, 0x22, 0xFF);
  SDL_RenderClear(gRenderer);
  SDL_SetRenderDrawColor(gRenderer, 0x82, 0x82, 0x82, 0xFF);
  wallLeft.Draw(gRenderer);
  wallRight.Draw(gRenderer);
  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
  ball.Draw(gRenderer);
  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
  paddle.Draw(gRenderer);
  SDL_RenderPresent(gRenderer);
}

// Loops forever!
void BreakoutGame::loop() {
  // Main loop flag
  // If this is quit = 'true' then the program terminates.
  bool quit = false;
  // Event handler that handles various events in SDL
  // that are related to input and output
  SDL_Event e;
  // Enable text input
  SDL_StartTextInput();

  // While application is running
  while (!quit) {
    // Handle events on queue
    while (SDL_PollEvent(&e) != 0) {
      // User posts an event to quit
      // An example is hitting the "x" in the corner of the window.
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }

    // If you have time, implement your frame capping code here
    // Otherwise, this is a cheap hack for this lab.
    SDL_Delay(250);

    // Update our scene
    update();
    // Render using OpenGL
    render();
    // Update screen of our specified window
  }

  // Disable text input
  SDL_StopTextInput();
}

// Get Pointer to Window
SDL_Window* BreakoutGame::getSDLWindow() { return gWindow; }

// Get Pointer to Renderer
SDL_Renderer* BreakoutGame::getSDLRenderer() { return gRenderer; }
