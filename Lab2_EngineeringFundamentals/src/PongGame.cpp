#include "PongGame.h"

#include <chrono>
#include <sstream>
#include "LTimer.h"
// Fixed FPS variables
const Uint32 SCREEN_60FPS = 60;
const Uint32 SCREEN_30FPS = 30;
const Uint32 SCREEN_TICKS_PER_FRAME_60 = 1000 / SCREEN_60FPS;
const Uint32 SCREEN_TICKS_PER_FRAME_30 = 1000 / SCREEN_30FPS;
// Fixed update speed
const Uint32 TICKS_PER_UPDATE = 10;

PongGame::PongGame(Uint32 w, Uint32 h) : screen_width_(w), screen_height_(h) {
  // Initialization flag
  bool success = true;
  // String to hold any errors that occur.
  std::stringstream errorStream;
  // The window we'll be rendering to
  window_ = nullptr;
  // Render flag
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
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
    // Initialize sound effects
    wallHitSound = Mix_LoadWAV("media/WallHit.wav");
    if (wallHitSound == nullptr) {
      errorStream << "Sound file could not be loaded! SDL_Mix Error: "
                  << Mix_GetError() << "\n";
      success = false;
    }
    paddleHitSound = Mix_LoadWAV("media/PaddleHit.wav");
    if (paddleHitSound == nullptr) {
      errorStream << "Sound file could not be loaded! SDL_Mix Error: "
                  << Mix_GetError() << "\n";
      success = false;
    }
    winSound = Mix_LoadWAV("media/Win.wav");
    if (paddleHitSound == nullptr) {
      errorStream << "Sound file could not be loaded! SDL_Mix Error: "
                  << Mix_GetError() << "\n";
      success = false;
    }
    // Create window
    window_ = SDL_CreateWindow("PongGame", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, screen_width_,
                               screen_height_, SDL_WINDOW_SHOWN);

    // Check if Window did not create.
    if (window_ == nullptr) {
      errorStream << "Window could not be created! SDL Error: "
                  << SDL_GetError() << "\n";
      success = false;
    } else {
      // Create a Renderer to draw on
      renderer_ = SDL_CreateRenderer(
          window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      // Check if Renderer did not create.
      if (renderer_ == nullptr) {
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
        font_ = TTF_OpenFont("media/PixelGameFont.ttf", 28);
        if (font_ == nullptr) {
          errorStream << "Failed to load lazy font! SDL_ttf Error: "
                      << TTF_GetError() << "\n";
          success = false;
        }
      }
    }
    // If initialization did not work, then print out a list of errors in the
    // constructor.
  }

  // Create the player score text fields
  playerOneScoreText =
      new PlayerScore(Vec2(WINDOW_WIDTH / 4, 20), renderer_, font_);

  playerTwoScoreText =
      new PlayerScore(Vec2(3 * WINDOW_WIDTH / 4, 20), renderer_, font_);

  winText = new PlayerScore(Vec2(WINDOW_WIDTH / 3, WINDOW_HEIGHT / 2.0f),
                            renderer_, font_);
  winText->SetColor(0XFF, 0, 0, 0XFF);

  // Create the ball
  ball = new Ball(Vec2(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f),
                  Vec2(BALL_SPEED, 0.0f));

  // Create the paddles
  paddleOne = new Paddle(Vec2(50.0f, WINDOW_HEIGHT / 2.0f), Vec2(0.0f, 0.0f));

  paddleTwo = new Paddle(Vec2(WINDOW_WIDTH - 50.0f, WINDOW_HEIGHT / 2.0f),
                         Vec2(0.0f, 0.0f));

  if (!success) {
    errorStream << "Failed to initialize!\n\n";
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", errorStream.str().c_str());
  } else {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
                "No SDL, or OpenGL, errors Detected\n\n");
  }
}

PongGame::~PongGame() {
  // Free sound
  Mix_FreeChunk(wallHitSound);
  Mix_FreeChunk(paddleHitSound);

  // Destroy Renderer
  SDL_DestroyRenderer(renderer_);
  // Destroy window
  SDL_DestroyWindow(window_);
  // Free global font
  TTF_CloseFont(font_);
  // destruct all pointers
  if (playerOneScoreText) delete playerOneScoreText;
  if (playerTwoScoreText) delete playerTwoScoreText;
  if (ball) delete ball;
  if (paddleOne) delete paddleOne;
  if (paddleTwo) delete paddleTwo;
  // Point ponters to NULL to ensure it points to nothing.
  font_ = nullptr;
  renderer_ = nullptr;
  window_ = nullptr;
  wallHitSound = nullptr;
  paddleHitSound = nullptr;

  playerOneScoreText = nullptr;
  playerTwoScoreText = nullptr;
  ball = nullptr;
  paddleOne = nullptr;
  paddleTwo = nullptr;
  // Quit SDL subsystems
  TTF_Quit();
  IMG_Quit();
  Mix_Quit();
  SDL_Quit();
}

// Update all elements' state
void PongGame::Update(float dt) {
  if (!pause_) {
    if (rebegin_) {
      playerTwoScoreText->SetScore(playerTwoScore);
      playerOneScoreText->SetScore(playerOneScore);
      rebegin_ = false;
    }
    if (buttons[Buttons::PaddleOneUp]) {
      paddleOne->velocity.y = -PADDLE_SPEED;
    } else if (buttons[Buttons::PaddleOneDown]) {
      paddleOne->velocity.y = PADDLE_SPEED;
    } else {
      paddleOne->velocity.y = 0.0f;
    }

    if (buttons[Buttons::PaddleTwoUp]) {
      paddleTwo->velocity.y = -PADDLE_SPEED;
    } else if (buttons[Buttons::PaddleTwoDown]) {
      paddleTwo->velocity.y = PADDLE_SPEED;
    } else {
      paddleTwo->velocity.y = 0.0f;
    }

    // Update the paddle positions
    paddleOne->Update(dt);
    paddleTwo->Update(dt);

    // Update the ball position
    ball->Update(dt);

    // Check collisions
    if (Contact contact = CheckPaddleCollision(*ball, *paddleOne);
        contact.type != CollisionType::None) {
      ball->CollideWithPaddle(contact);
      Mix_PlayChannel(-1, paddleHitSound, 0);

    } else if (contact = CheckPaddleCollision(*ball, *paddleTwo);
               contact.type != CollisionType::None) {
      ball->CollideWithPaddle(contact);
      Mix_PlayChannel(-1, paddleHitSound, 0);

    } else if (contact = CheckWallCollision(*ball);
               contact.type != CollisionType::None) {
      ball->CollideWithWall(contact);

      if (contact.type == CollisionType::Left) {
        ++playerTwoScore;
        playerTwoScoreText->SetScore(playerTwoScore);

      } else if (contact.type == CollisionType::Right) {
        ++playerOneScore;
        playerOneScoreText->SetScore(playerOneScore);

      } else {
        Mix_PlayChannel(-1, wallHitSound, 0);
      }
    }
    if (playerTwoScore > 2 || playerOneScore > 2) {
      Mix_PlayChannel(-1, winSound, 0);
      std::string win_str;
      if (playerTwoScore > 2) {
        winner_ = Winner::PlayerTwo;
        win_str = "PlayerTwo Win! Press 'space' to continue";
      } else {
        winner_ = Winner::PlayerOne;
        win_str = "PlayerOne Win! Press 'space' to continue";
      }
      winText->SetText(win_str);
      winText->rect.x = screen_width_/2-winText->rect.w/2;
      winText->rect.y = screen_height_/2-winText->rect.h/2;
      pause_ = true;
      playerTwoScore = 0;
      playerOneScore = 0;
    }
  }
}

// Render
// The render function gets called once per loop
void PongGame::Render() {
  // Clear the window to black
  SDL_SetRenderDrawColor(renderer_, 0x0, 0x0, 0x0, 0xFF);
  SDL_RenderClear(renderer_);
  // Set the draw color to be white
  SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);

  // Draw the net
  for (int y = 0; y < WINDOW_HEIGHT; ++y) {
    if (y % 5) {
      SDL_RenderDrawPoint(renderer_, WINDOW_WIDTH / 2, y);
    }
  }
  // Draw the ball
  ball->Draw(renderer_);

  // Draw the paddles
  paddleOne->Draw(renderer_);
  paddleTwo->Draw(renderer_);

  // Display the scores
  playerOneScoreText->Draw();
  playerTwoScoreText->Draw();
  if (pause_) {
    winText->Draw();
  }
  // Update screen
  SDL_RenderPresent(renderer_);
}

// Loops forever!
void PongGame::Loop() {
  // Main loop flag
  // If this is quit = 'true' then the program terminates.
  bool quit = false;
  // Event handler that handles various events in SDL
  // that are related to input and output
  SDL_Event event;
    
  // Update timer
  LTimer updateTimer;
  Uint32 previous = 0;
  Uint32 lag = 0;
  updateTimer.start();

  // Timer to cap time
  LTimer capTimer;
  Uint32 fixedTicks = SCREEN_TICKS_PER_FRAME_60;

  // Enable text input
  SDL_StartTextInput();
  // While application is running
  while (!quit) {
    //Start cap timer
    capTimer.start();
    // 
    Uint32 current = updateTimer.getTicks();
    Uint32 elapsed = current - previous;
    previous = current;
    lag += elapsed;
    // Handle events on queue
    while (SDL_PollEvent(&event) != 0) {
      // User posts an event to quit
      // An example is hitting the "x" in the corner of the window.
      if (event.type == SDL_QUIT) {
        quit = true;
      } else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_ESCAPE) {
          quit = true;
        } else if (event.key.keysym.sym == SDLK_w) {
          buttons[Buttons::PaddleOneUp] = true;
        } else if (event.key.keysym.sym == SDLK_s) {
          buttons[Buttons::PaddleOneDown] = true;
        } else if (event.key.keysym.sym == SDLK_UP) {
          buttons[Buttons::PaddleTwoUp] = true;
        } else if (event.key.keysym.sym == SDLK_DOWN) {
          buttons[Buttons::PaddleTwoDown] = true;
        } else if (event.key.keysym.sym == SDLK_SPACE) {
          if (pause_) {
            pause_ = false;
            rebegin_ = true;
          }
        }
      } else if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_w) {
          buttons[Buttons::PaddleOneUp] = false;
        } else if (event.key.keysym.sym == SDLK_s) {
          buttons[Buttons::PaddleOneDown] = false;
        } else if (event.key.keysym.sym == SDLK_UP) {
          buttons[Buttons::PaddleTwoUp] = false;
        } else if (event.key.keysym.sym == SDLK_DOWN) {
          buttons[Buttons::PaddleTwoDown] = false;
        }
      }
    }
    // Update our scene
    while (lag >= TICKS_PER_UPDATE)
    {
      Update(TICKS_PER_UPDATE);
      lag -= TICKS_PER_UPDATE;
    }
    
    // Render
    Render();

    // Cap fps
    Uint32 frameTicks = capTimer.getTicks();
    // If frame finished early
    if( frameTicks < fixedTicks )
    {
        //Wait remaining time
        SDL_Delay( fixedTicks - frameTicks );
    }
  }

  // Disable text input
  SDL_StopTextInput();
}

Contact PongGame::CheckPaddleCollision(Ball const& ball, Paddle const& paddle) {
  float ballLeft = ball.position.x;
  float ballRight = ball.position.x + BALL_WIDTH;
  float ballTop = ball.position.y;
  float ballBottom = ball.position.y + BALL_HEIGHT;

  float paddleLeft = paddle.position.x;
  float paddleRight = paddle.position.x + PADDLE_WIDTH;
  float paddleTop = paddle.position.y;
  float paddleBottom = paddle.position.y + PADDLE_HEIGHT;

  Contact contact{};

  if (ballLeft >= paddleRight) {
    return contact;
  }

  if (ballRight <= paddleLeft) {
    return contact;
  }

  if (ballTop >= paddleBottom) {
    return contact;
  }

  if (ballBottom <= paddleTop) {
    return contact;
  }

  float paddleRangeUpper = paddleBottom - (2.0f * PADDLE_HEIGHT / 3.0f);
  float paddleRangeMiddle = paddleBottom - (PADDLE_HEIGHT / 3.0f);

  if (ball.velocity.x < 0) {
    // Left paddle
    contact.penetration = paddleRight - ballLeft;
  } else if (ball.velocity.x > 0) {
    // Right paddle
    contact.penetration = paddleLeft - ballRight;
  }

  if ((ballBottom > paddleTop) && (ballBottom < paddleRangeUpper)) {
    contact.type = CollisionType::Top;
  } else if ((ballBottom > paddleRangeUpper) &&
             (ballBottom < paddleRangeMiddle)) {
    contact.type = CollisionType::Middle;
  } else {
    contact.type = CollisionType::Bottom;
  }

  return contact;
}

Contact PongGame::CheckWallCollision(Ball const& ball) {
  float ballLeft = ball.position.x;
  float ballRight = ball.position.x + BALL_WIDTH;
  float ballTop = ball.position.y;
  float ballBottom = ball.position.y + BALL_HEIGHT;

  Contact contact{};

  if (ballLeft < 0.0f) {
    contact.type = CollisionType::Left;
  } else if (ballRight > WINDOW_WIDTH) {
    contact.type = CollisionType::Right;
  } else if (ballTop < 0.0f) {
    contact.type = CollisionType::Top;
    contact.penetration = -ballTop;
  } else if (ballBottom > WINDOW_HEIGHT) {
    contact.type = CollisionType::Bottom;
    contact.penetration = WINDOW_HEIGHT - ballBottom;
  }

  return contact;
}