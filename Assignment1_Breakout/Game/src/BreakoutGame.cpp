#include "BreakoutGame.hpp"

#include "LTimer.h"

// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
BreakoutGame::BreakoutGame(int w, int h)
    : screenWidth(w),
      screenHeight(h),
      level(DEFAULT_LEVEL),
      gameState(Initializing),
      // Initialize game objects
      // Wall
      wallLeft(Vector2D{GAME_SCENE_LEFT - WALL_WIDTH, 0}, WALL_WIDTH),
      wallRight(Vector2D{GAME_SCENE_RIGHT, 0}, WALL_WIDTH) {
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
    // Initialize sound effects
    wallHitSound = Mix_LoadWAV("assets/sounds/WallHit.wav");
    if (wallHitSound == nullptr) {
      errorStream << "Sound file could not be loaded! SDL_Mix Error: "
                  << Mix_GetError() << "\n";
      success = false;
    }
    paddleHitSound = Mix_LoadWAV("assets/sounds/PaddleHit.wav");
    if (paddleHitSound == nullptr) {
      errorStream << "Sound file could not be loaded! SDL_Mix Error: "
                  << Mix_GetError() << "\n";
      success = false;
    }
    winSound = Mix_LoadWAV("assets/sounds/Win.wav");
    if (winSound == nullptr) {
      errorStream << "Sound file could not be loaded! SDL_Mix Error: "
                  << Mix_GetError() << "\n";
      success = false;
    }
    loseSound = Mix_LoadWAV("assets/sounds/Lose.wav");
    if (loseSound == nullptr) {
      errorStream << "Sound file could not be loaded! SDL_Mix Error: "
                  << Mix_GetError() << "\n";
      success = false;
    }
    loseLifeSound = Mix_LoadWAV("assets/sounds/LoseLife.wav");
    if (loseLifeSound == nullptr) {
      errorStream << "Sound file could not be loaded! SDL_Mix Error: "
                  << Mix_GetError() << "\n";
      success = false;
    }
    brickHitSound = Mix_LoadWAV("assets/sounds/BrickHit.wav");
    if (brickHitSound == nullptr) {
      errorStream << "Sound file could not be loaded! SDL_Mix Error: "
                  << Mix_GetError() << "\n";
      success = false;
    }
    backgroundMusic = Mix_LoadMUS("assets/sounds/8_Bit_Surf.wav");
    if (backgroundMusic == nullptr) {
      errorStream << "Music file could not be loaded! SDL_Mix Error: "
                  << Mix_GetError() << "\n";
      success = false;
    }
    // Create window
    gWindow = SDL_CreateWindow("Breakout Game", 100, 100, screenWidth,
                               screenHeight, SDL_WINDOW_SHOWN);

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
      contentFont_ = TTF_OpenFont(FONT_IPIX_PATH, DEFAULT_FONT_SIZE);
      if (contentFont_ == nullptr) {
        errorStream << "Failed to load font! SDL_ttf Error: " << TTF_GetError()
                    << "\n";
        success = false;
      }
      menuFont_ = TTF_OpenFont(FONT_IPIX_PATH, MENU_FONT_SIZE);
      if (menuFont_ == nullptr) {
        errorStream << "Failed to load font! SDL_ttf Error: " << TTF_GetError()
                    << "\n";
        success = false;
      }
    }
  }

  // Texts
  int textSideInterval = 50;
  int textLineInterval = 10;
  int textLeftCenter = ((WINDOW_WIDTH - GAME_SCENE_WIDTH) / 2 - WALL_WIDTH) / 2;

  int textRightCenter = WINDOW_WIDTH - textLeftCenter;
  // Score
  scoreText = new Text(Vector2D(), gRenderer, contentFont_);
  scoreNum = new Text(Vector2D(), gRenderer, contentFont_);
  // Current rest life
  livesText = new Text(Vector2D(), gRenderer, contentFont_);
  livesNum = new Text(Vector2D(), gRenderer, contentFont_);
  // Current Level
  levelText = new Text(Vector2D(), gRenderer, contentFont_);
  levelNum = new Text(Vector2D(), gRenderer, contentFont_);
  // Init Texts' text
  scoreText->SetText("Score");
  livesText->SetText("Lives");
  levelText->SetText("Level");
  scoreNum->SetText(std::to_string(player.getScore()));
  livesNum->SetText(std::to_string(player.getLives()));
  levelNum->SetText(std::to_string(level));
  // Set each Texts' center location
  // Left side texts
  int beginX = textSideInterval;
  levelText->SetCenterPosition(textLeftCenter,
                               beginX + levelText->getHeight() / 2);
  beginX += levelText->getHeight();
  beginX += textLineInterval;
  levelNum->SetCenterPosition(textLeftCenter,
                              beginX + levelNum->getHeight() / 2);
  // Right side texts
  beginX = textSideInterval;
  scoreText->SetCenterPosition(textRightCenter,
                               beginX + scoreText->getHeight() / 2);
  beginX += scoreText->getHeight();
  beginX += textLineInterval;
  scoreNum->SetCenterPosition(textRightCenter,
                              beginX + scoreNum->getHeight() / 2);
  beginX += scoreNum->getHeight();
  beginX += textLineInterval;
  livesText->SetCenterPosition(textRightCenter,
                               beginX + livesText->getHeight() / 2);
  beginX += livesText->getHeight();
  beginX += textLineInterval;
  livesNum->SetCenterPosition(textRightCenter,
                              beginX + livesNum->getHeight() / 2);

  // Init text for Win, Lose, Pause or Menu notification
  notificationText = new Text(Vector2D(), gRenderer, menuFont_);
  notificationText->SetCenterPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
  notificationText->SetColor(0xc0, 0x00, 0x00, 0xff);
  notificationText->setKeepCentered(true);
  // Bricks
  // Create bricks
  bricks.reserve(BRICK_COLUMN * BRICK_ROW);
  int brickSumWidth =
      BRICK_COLUMN * BRICK_WIDTH + (BRICK_COLUMN - 1) * BRICK_INTERVAL;
  int brickStartX = (WINDOW_WIDTH - brickSumWidth) / 2;
  int brickStartY = BRICK_START_HEIGHT;
  for (int i = 0, x = brickStartX, y = brickStartY; i < BRICK_ROW; i++) {
    for (int j = 0; j < BRICK_COLUMN; j++) {
      bricks.push_back(Brick(Vector2D(x, y), true));
      x += BRICK_WIDTH + BRICK_INTERVAL;
    }
    x = brickStartX;
    y += BRICK_HEIGHT + BRICK_INTERVAL;
  }
  restBricks = bricks.size();
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
  // Deallocate Texts
  if (scoreText) delete scoreText;
  if (livesText) delete livesText;
  if (levelText) delete levelText;
  if (scoreNum) delete scoreNum;
  if (livesNum) delete livesNum;
  if (levelNum) delete levelNum;
  // Point gWindow to NULL to ensure it points to nothing.
  gRenderer = NULL;
  gWindow = NULL;
  // Quit external SDL libraries
  TTF_Quit();
  Mix_Quit();
  IMG_Quit();
  // Quit SDL subsystems
  SDL_Quit();
}

// Update OpenGL
void BreakoutGame::update(float dt) {
  // Update paddle
  if (buttons[Buttons::PaddleLeft]) {
    paddle.velocity.x = -PADDLE_SPEED;
  } else if (buttons[Buttons::PaddleRight]) {
    paddle.velocity.x = PADDLE_SPEED;
  } else {
    paddle.velocity.x = 0.0f;
  }
  paddle.Update(dt);
  // Update ball
  ball.Update(dt);
  // Check collisions and update related objects
  if (Contact contact = CheckPaddleCollision(ball, paddle);
      contact.type != CollisionType::None) {
    ball.CollideWithPaddle(contact);
    Mix_PlayChannel(-1, paddleHitSound, 0);
  } else if (contact = CheckWallCollision(ball);
             contact.type != CollisionType::None) {
    // When ball hit the Bottom
    if (contact.type == CollisionType::Bottom) {
      // Player lose one life
      player.loseLife();
      livesNum->SetText(std::to_string(player.getLives()));
      if (player.getLives() > 0) {
        gameState = GameState::PauseLoseLife;
        notificationText->SetText("Ops! Press SPACE to continue");
        Mix_PlayChannel(-1, loseLifeSound, 0);
      } else {
        gameState = GameState::PauseLoseGame;
        notificationText->SetText("You lose! Press SPACE to restart");
        player.setScore(0);
        scoreNum->SetText(std::to_string(player.getScore()));
        Mix_PlayChannel(-1, loseSound, 0);
      }
      // Reset paddle and ball
      paddle = Paddle();
      ball = Ball();
    } else {  // When ball hit top
      Mix_PlayChannel(-1, wallHitSound, 0);
    }
    ball.CollideWithWall(contact);
  } else {
    // Check ball collision with all bricks
    for (Brick& brick : bricks) {
      if (brick.isActive()) {
        contact = CheckBrickCollision(ball, brick, dt);
        if (contact.type != CollisionType::None) {
          brick.setActive(false);
          ball.CollideWithBrick(contact);
          player.addScore(brick.getScore());
          restBricks--;
          Mix_PlayChannel(-1, brickHitSound, 0);
        }
      }
    }
    scoreNum->SetText(std::to_string(player.getScore()));
    // Player win when all bricks are removed
    if (restBricks <= 0) {
      gameState = GameState::PauseWin;
      notificationText->SetText("You win! Press SPACE to play next level");
      // Reset paddle and ball
      paddle = Paddle();
      ball = Ball();
      level++;
      Mix_PlayChannel(-1, winSound, 0);
    }
  }
  // Update Texts
  levelNum->SetText(std::to_string(level));
}

// Render
// The render function gets called once per loop
void BreakoutGame::render() {
  SDL_SetRenderDrawColor(gRenderer, 0x22, 0x22, 0x22, 0xFF);
  SDL_RenderClear(gRenderer);
  // Render wall
  SDL_SetRenderDrawColor(gRenderer, 0x82, 0x82, 0x82, 0xFF);
  wallLeft.Draw(gRenderer);
  wallRight.Draw(gRenderer);
  // Render ball
  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
  ball.Draw(gRenderer);
  // Render paddle
  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
  paddle.Draw(gRenderer);
  // Render bricks
  SDL_SetRenderDrawColor(gRenderer, 28, 56, 183, 0xFF);
  for (Brick& brick : bricks) {
    brick.Draw(gRenderer);
  }
  // Render Texts
  scoreText->Draw();
  livesText->Draw();
  levelText->Draw();
  scoreNum->Draw();
  livesNum->Draw();
  levelNum->Draw();
  if (gameState != GameState::Running) {
    notificationText->Draw();
  }

  SDL_RenderPresent(gRenderer);
}

// Loops forever!
void BreakoutGame::loop() {
  // Main loop flag
  // If this is quit = 'true' then the program terminates.
  bool quit = false;
  // Event handler that handles various events in SDL
  // that are related to input and output
  SDL_Event event;
  // Enable text input
  SDL_StartTextInput();

  // Timer to cap time
  LTimer capTimer;
  Uint32 fixedTicks = SCREEN_TICKS_PER_FRAME_60;
  // Update timer
  LTimer updateTimer;
  Uint32 previous = 0;
  Uint32 lag = 0;
  updateTimer.start();

  // Start game
  gameState = GameState::PauseNormal;
  notificationText->SetText("Press SPACE to Start");
  Mix_PlayMusic(backgroundMusic, -1);
  while (!quit) {
    // Start cap timer
    capTimer.start();
    if (gameState == GameState::Running) {
      // Update variable for game update timer
      Uint32 current = updateTimer.getTicks();
      Uint32 elapsed = current - previous;
      previous = current;
      lag += elapsed;
    }
    // Handle events on queue
    while (SDL_PollEvent(&event) != 0) {
      // User posts an event to quit
      // An example is hitting the "x" in the corner of the window.
      if (event.type == SDL_QUIT) {
        quit = true;
      } else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_ESCAPE ||
            event.key.keysym.sym == SDLK_q) {
          quit = true;
        } else if (event.key.keysym.sym == SDLK_a) {
          buttons[Buttons::PaddleLeft] = true;
        } else if (event.key.keysym.sym == SDLK_d) {
          buttons[Buttons::PaddleRight] = true;
        } else if (event.key.keysym.sym == SDLK_LEFT) {
          buttons[Buttons::PaddleLeft] = true;
        } else if (event.key.keysym.sym == SDLK_RIGHT) {
          buttons[Buttons::PaddleRight] = true;
        } else if (event.key.keysym.sym == SDLK_SPACE) {
          if (gameState == GameState::Running) {
            gameState = GameState::PauseNormal;
            notificationText->SetText("Press SPACE to continue");
          } else {
            switch (gameState) {
              case GameState::PauseLoseGame:
                player.setLives(PLAYER_DEFAULT_LIFE_NUM);
                livesNum->SetText(std::to_string(player.getLives()));
                resetBricks();
                break;
              case GameState::PauseLoseLife:
                break;
              case GameState::PauseWin:
                resetBricks();
                break;
              default:
                break;
            }
            gameState = GameState::Running;
          }
        }
      } else if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_a) {
          buttons[Buttons::PaddleLeft] = false;
        } else if (event.key.keysym.sym == SDLK_d) {
          buttons[Buttons::PaddleRight] = false;
        } else if (event.key.keysym.sym == SDLK_LEFT) {
          buttons[Buttons::PaddleLeft] = false;
        } else if (event.key.keysym.sym == SDLK_RIGHT) {
          buttons[Buttons::PaddleRight] = false;
        }
      }
    }  // End while

    // Update our scene
    if (gameState == GameState::Running) {
      while (lag >= TICKS_PER_UPDATE) {
        update(TICKS_PER_UPDATE);
        lag -= TICKS_PER_UPDATE;
      }
    }

    // Game state check
    if (gameState != GameState::Running) {
      updateTimer.pause();
    }
    if (updateTimer.isPaused() && gameState == GameState::Running) {
      updateTimer.unpause();
    }

    // Render using OpenGL
    render();

    // Update screen of our specified window

    // Cap fps
    Uint32 frameTicks = capTimer.getTicks();
    // If frame finished early
    if (frameTicks < fixedTicks) {
      // Wait for extra time
      SDL_Delay(fixedTicks - frameTicks);
    }
  }  // End while

  // Disable text input
  SDL_StopTextInput();
}

// Get Pointer to Window
SDL_Window* BreakoutGame::getSDLWindow() { return gWindow; }

// Get Pointer to Renderer
SDL_Renderer* BreakoutGame::getSDLRenderer() { return gRenderer; }

void BreakoutGame::resetBricks() {
  for (Brick& b : bricks) {
    b.setActive(true);
  }
  restBricks = bricks.size();
}

Contact BreakoutGame::CheckPaddleCollision(Ball const& ball,
                                           Paddle const& paddle) {
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
  };

  contact.penetration.y = paddleTop - ballBottom;
  contact.type = CollisionType::Middle;
  return contact;
}

Contact BreakoutGame::CheckWallCollision(Ball const& ball) {
  float ballLeft = ball.position.x;
  float ballRight = ball.position.x + BALL_WIDTH;
  float ballTop = ball.position.y;
  float ballBottom = ball.position.y + BALL_HEIGHT;

  Contact contact{};

  if (ballLeft < GAME_SCENE_LEFT) {
    contact.type = CollisionType::Left;
  } else if (ballRight > GAME_SCENE_RIGHT) {
    contact.type = CollisionType::Right;
  } else if (ballTop < 0.0f) {
    contact.type = CollisionType::Top;
    contact.penetration.y = -ballTop;
  } else if (ballBottom > WINDOW_HEIGHT) {
    contact.type = CollisionType::Bottom;
    contact.penetration.y = WINDOW_HEIGHT - ballBottom;
  }

  return contact;
}

Contact BreakoutGame::CheckBrickCollision(Ball const& ball, Brick const& brick,
                                          float dt) {
  float ballLeft = ball.position.x;
  float ballRight = ball.position.x + BALL_WIDTH;
  float ballTop = ball.position.y;
  float ballBottom = ball.position.y + BALL_HEIGHT;

  // Loop over all bricks to check collision
  Contact contact{};
  float brickLeft, brickRight, brickTop, brickBottom;

  brickLeft = brick.position.x;
  brickRight = brick.position.x + BRICK_WIDTH;
  brickTop = brick.position.y;
  brickBottom = brick.position.y + BRICK_HEIGHT;
  if (ballLeft >= brickRight) {
    return contact;
  }
  if (ballRight <= brickLeft) {
    return contact;
  }
  if (ballTop >= brickBottom) {
    return contact;
  }
  if (ballBottom <= brickTop) {
    return contact;
  }
  // float ballCenterX = ball.position.x + BALL_HEIGHT / 2.0;
  // float ballCenterY = ball.position.y + BALL_WIDTH / 2.0;
  // Direction d = VectorDirectionSDL(ball.velocity);
  // switch (d) {
  //   case Direction::UP:
  //     contact.type = CollisionType::Bottom;
  //     contact.penetration.y = brickTop - ballBottom;
  //     break;
  //   case Direction::DOWN:
  //     contact.type = CollisionType::Top;
  //     contact.penetration.y = brickBottom - ballTop;
  //     break;
  //   case Direction::LEFT:
  //     contact.type = CollisionType::Right;
  //     contact.penetration.x = brickLeft - ballRight;
  //     break;
  //   case Direction::RIGHT:
  //     contact.type = CollisionType::Left;
  //     contact.penetration.x = brickRight - ballLeft;
  //     break;
  //   default:
  //     break;
  // }
  if (ballRight >= brickLeft && ballRight <= brickLeft + ball.velocity.x * dt) {
    contact.type = CollisionType::Right;
    contact.penetration.x = brickLeft - ballRight;
  } else if (ballLeft <= brickRight &&
             ballLeft >= brickRight + ball.velocity.x * dt) {
    contact.type = CollisionType::Left;
    contact.penetration.x = brickRight - ballLeft;
  } else if (ballBottom >= brickTop &&
             ballBottom <= brickTop + ball.velocity.y * dt) {
    contact.type = CollisionType::Bottom;
    contact.penetration.y = brickTop - ballBottom;
  } else if (ballTop <= brickBottom &&
             ballTop >= brickBottom + ball.velocity.y * dt) {
    contact.type = CollisionType::Top;
    contact.penetration.y = brickBottom - ballTop;
  }

  return contact;
}
