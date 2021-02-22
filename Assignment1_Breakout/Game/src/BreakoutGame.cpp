#include "BreakoutGame.hpp"

#include "LTimer.h"
#include "ResourceManager.hpp"
// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
BreakoutGame::BreakoutGame(int w, int h, nlohmann::json js)
    : screenWidth(w),
      screenHeight(h),
      gameState(Initializing),
      configs(js)
// Initialize game objects
{
  bool success = true;
  // String to hold any errors that occur.
  std::stringstream errorStream;
  // Init SDL systems
  if (!initSDLSystems()) {
    errorStream << "Fail to init SDL systems!" << std::endl;
    success = false;
  }

  if (!loadResources()) {
    errorStream << "Fail to load resources!" << std::endl;
    success = false;
  }
  if (!loadLevels()) {
    errorStream << "Fail to load level configs!" << std::endl;
    success = false;
  }
  if (!loadLanguages()) {
    errorStream << "Fail to load level language data!" << std::endl;
    success = false;
  }
  initGameObjects();
  if (!success) {
    errorStream << "Failed to initialize!\n";
    std::string errors = errorStream.str();
    std::cout << errors << "\n";
  } else {
    std::cout << "No SDL errors Detected in during init\n\n";
  }
}
bool BreakoutGame::loadResources() {
  ResourceManager& rm = ResourceManager::getInstance();
  rm.init("BreakoutGameResourceManager", "");
  bool success = false;
  success = rm.startManager();
  if (!success) {
    std::cerr << "Fail to start ResourceManager\n";
    return success;
  }

  for (auto& kv : configs["RESOURCE"].items()) {
    // process font
    success = rm.AddResource(kv.key(), kv.value().get<std::string>(), nullptr);
    if (!success) {
      std::cout << "Fail to Load: " << kv.key() << " : " << kv.value()
                << std::endl;
      return success;
    }
  }
  contentFont_ = std::shared_ptr<TTF_Font>(
      TTF_OpenFontRW(rm.LoadResource("FONT_IPIX_PATH").get(), 0,
                     DEFAULT_FONT_SIZE),
      TTF_CloseFont);

  menuFont_ = std::shared_ptr<TTF_Font>(
      TTF_OpenFontRW(rm.LoadResource("FONT_IPIX_PATH").get(), 0,
                     MENU_FONT_SIZE),
      TTF_CloseFont);
  // Initialize sound effects
  wallHitSound = std::shared_ptr<Mix_Chunk>(
      Mix_LoadWAV_RW(rm.LoadResource("WALL_HIT_SOUND").get(), 0),
      Mix_FreeChunk);

  paddleHitSound = std::shared_ptr<Mix_Chunk>(
      Mix_LoadWAV_RW(rm.LoadResource("PADDLE_HIT_SOUND").get(), 0),
      Mix_FreeChunk);

  winSound = std::shared_ptr<Mix_Chunk>(
      Mix_LoadWAV_RW(rm.LoadResource("WIN_SOUND").get(), 0), Mix_FreeChunk);

  loseSound = std::shared_ptr<Mix_Chunk>(
      Mix_LoadWAV_RW(rm.LoadResource("LOSE_SOUND").get(), 0), Mix_FreeChunk);

  loseLifeSound = std::shared_ptr<Mix_Chunk>(
      Mix_LoadWAV_RW(rm.LoadResource("LOSE_LIFE_SOUND").get(), 0),
      Mix_FreeChunk);

  brickHitSound = std::shared_ptr<Mix_Chunk>(
      Mix_LoadWAV_RW(rm.LoadResource("BRICK_HIT_SOUND").get(), 0),
      Mix_FreeChunk);
  backgroundMusic = std::shared_ptr<Mix_Chunk>(
      Mix_LoadWAV_RW(rm.LoadResource("BACKGROUND_SOUND").get(), 0),
      Mix_FreeChunk);
  return true;
}

bool BreakoutGame::initSDLSystems() {
  // Initialize random number generation.
  srand(time(NULL));

  // Initialization flag
  bool success = true;
  // String to hold any errors that occur.
  std::stringstream errorStream;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError()
                << "\n";
    success = false;
  } else {
    // Create window
    gWindow = std::shared_ptr<SDL_Window>(
        SDL_CreateWindow("Breakout Game", 100, 100, screenWidth, screenHeight,
                         SDL_WINDOW_SHOWN),
        SDL_DestroyWindow);
    // Check if Window did not create.
    if (gWindow == nullptr) {
      errorStream << "Window could not be created! SDL Error: "
                  << SDL_GetError() << "\n";
      success = false;
    } else {
      gRenderer = std::shared_ptr<SDL_Renderer>(
          SDL_CreateRenderer(gWindow.get(), -1, SDL_RENDERER_ACCELERATED),
          SDL_DestroyRenderer);
      // Check if Renderer did not create.
      if (gRenderer == nullptr) {
        errorStream << "Renderer could not be created! SDL Error: "
                    << SDL_GetError() << "\n";
        success = false;
      }
    }
    // Open Audio
    int ret = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    if (ret < 0) {
      errorStream << "Audio could not be opened! SDL_mixer Error: "
                  << Mix_GetError() << "\n";
      success = false;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
      errorStream << "SDL_ttf could not initialize! SDL_ttf Error: "
                  << TTF_GetError() << "\n";
      success = false;
    }
  }
  return success;
}
void BreakoutGame::initBall() {
  ball = Ball(Vector2D((WINDOW_WIDTH - BALL_WIDTH) / 2,
                       WINDOW_HEIGHT - PADDLE_HEIGHT - BALL_HEIGHT -
                           PADDLE_DISTANCE_FROM_BOTTOM),
              Vector2D(BALL_SPEED, 0).getRotatedVector(BALL_START_DEGREE));
}
void BreakoutGame::initPaddle() {
  paddle = Paddle(
      Vector2D((WINDOW_WIDTH - PADDLE_WIDTH) / 2,
               WINDOW_HEIGHT - PADDLE_HEIGHT - PADDLE_DISTANCE_FROM_BOTTOM),
      Vector2D(PADDLE_SPEED, 0));
}
bool BreakoutGame::loadLevels() {
  std::cout << "Loading level config files..." << std::endl;
  for (auto& path : configs["LEVEL_FILES"]) {
    if (!bricksGenerator.loadOneLevelData(path)) {
      std::cerr << "Fail to load level config file: " << path << std::endl;
      return false;
    } else {
      std::cout << "Loaded " << path << std::endl;
    }
  }
  maxLevel = bricksGenerator.getMaxLevel();
  return true;
}

bool BreakoutGame::loadLanguages() {
  bool success;
  success = languageSelector.loadOneLanguageContent(
      configs["ZH_CN_LANGUAGE_FILE"].get<std::string>(), "zh_US");
  if (!success) return false;
  success = languageSelector.loadOneLanguageContent(
      configs["EN_US_LANGUAGE_FILE"].get<std::string>(), "en_US");
  return success;
}
void BreakoutGame::updateAllTexts() {
  switch (gameState) {
    case GameState::Initializing:
      notificationText.SetText(languageSelector.getContent("LANGUAGE_CHOOSE"));
      break;
    case GameState::PauseNormal:
      notificationText.SetText(languageSelector.getContent("PAUSE_NORMAL"));
      break;
    case GameState::PauseLoseGame:
      notificationText.SetText(languageSelector.getContent("PAUSE_LOSE_GAME"));
      break;
    case GameState::PauseLoseLife:
      notificationText.SetText(languageSelector.getContent("PAUSE_LOSE_LIFE"));
      break;
    case GameState::PauseWin:
      notificationText.SetText(languageSelector.getContent("PAUSE_WIN_GAME"));
      break;
    case GameState::PauseClearGame:
      notificationText.SetText(languageSelector.getContent("PAUSE_CLEAR_GAME"));
      break;
    default:
      break;
  }
  scoreText.SetText(languageSelector.getContent("SCORE"));
  livesText.SetText(languageSelector.getContent("LIVES"));
  levelText.SetText(languageSelector.getContent("LEVEL"));
}

void BreakoutGame::initGameObjects() {
  // Ball
  initBall();
  // Paddle
  initPaddle();
  // Walls
  wallLeft = Wall(Vector2D(GAME_SCENE_LEFT - WALL_WIDTH, 0), WALL_WIDTH);
  wallRight = Wall(Vector2D(GAME_SCENE_RIGHT, 0), WALL_WIDTH);
  // Texts
  int textSideInterval = 50;
  int textLineInterval = 10;
  int textLeftCenter = ((WINDOW_WIDTH - GAME_SCENE_WIDTH) / 2 - WALL_WIDTH) / 2;

  int textRightCenter = WINDOW_WIDTH - textLeftCenter;
  // Score
  scoreText = Text(Vector2D(), gRenderer, contentFont_);
  scoreNum = Text(Vector2D(), gRenderer, contentFont_);
  // Current rest life
  livesText = Text(Vector2D(), gRenderer, contentFont_);
  livesNum = Text(Vector2D(), gRenderer, contentFont_);
  // Current Level
  levelText = Text(Vector2D(), gRenderer, contentFont_);
  levelNum = Text(Vector2D(), gRenderer, contentFont_);
  // Init Texts' text
  scoreText.SetText(languageSelector.getContent("SCORE"));
  livesText.SetText(languageSelector.getContent("LIVES"));
  levelText.SetText(languageSelector.getContent("LEVEL"));
  scoreNum.SetText(std::to_string(player.getScore()));
  livesNum.SetText(std::to_string(player.getLives()));
  levelNum.SetText(std::to_string(level));
  // Set each Texts' center location
  // Left side texts
  int beginX = textSideInterval;
  levelText.SetCenterPosition(textLeftCenter,
                              beginX + levelText.getHeight() / 2);
  beginX += levelText.getHeight();
  beginX += textLineInterval;
  levelNum.SetCenterPosition(textLeftCenter, beginX + levelNum.getHeight() / 2);
  // Right side texts
  beginX = textSideInterval;
  scoreText.SetCenterPosition(textRightCenter,
                              beginX + scoreText.getHeight() / 2);
  beginX += scoreText.getHeight();
  beginX += textLineInterval;
  scoreNum.SetCenterPosition(textRightCenter,
                             beginX + scoreNum.getHeight() / 2);
  beginX += scoreNum.getHeight();
  beginX += textLineInterval;
  livesText.SetCenterPosition(textRightCenter,
                              beginX + livesText.getHeight() / 2);
  beginX += livesText.getHeight();
  beginX += textLineInterval;
  livesNum.SetCenterPosition(textRightCenter,
                             beginX + livesNum.getHeight() / 2);

  // Init text for Win, Lose, Pause or Menu notification
  notificationText = Text(Vector2D(), gRenderer, menuFont_);
  notificationText.SetCenterPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
  notificationText.SetColor(0xc0, 0x00, 0x00, 0xff);
  notificationText.setKeepCentered(true);

  bricks = bricksGenerator.getLevelBricks(level - 1);
  restBricks = bricks.size();
}

// Proper shutdown and destroy initialized objects
BreakoutGame::~BreakoutGame() {
  // Quit external SDL libraries
  TTF_Quit();
  Mix_Quit();
  // Stop ResourceManager
  ResourceManager::getInstance().stopManager();
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
    Mix_PlayChannel(-1, paddleHitSound.get(), 0);
  } else if (contact = CheckWallCollision(ball);
             contact.type != CollisionType::None) {
    // When ball hit the Bottom
    if (contact.type == CollisionType::Bottom) {
      // Player lose one life
      player.loseLife();
      livesNum.SetText(std::to_string(player.getLives()));
      if (player.getLives() > 0) {
        gameState = GameState::PauseLoseLife;
        notificationText.SetText(
            languageSelector.getContent("PAUSE_LOSE_LIFE"));
        Mix_PlayChannel(-1, loseLifeSound.get(), 0);
      } else {
        gameState = GameState::PauseLoseGame;
        notificationText.SetText(
            languageSelector.getContent("PAUSE_LOSE_GAME"));
        player.setScore(0);
        scoreNum.SetText(std::to_string(player.getScore()));
        Mix_PlayChannel(-1, loseSound.get(), 0);
      }
      // Reset paddle and ball
      initBall();
      initPaddle();
    } else {  // When ball hit top
      Mix_PlayChannel(-1, wallHitSound.get(), 0);
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
          Mix_PlayChannel(-1, brickHitSound.get(), 0);
        }
      }
    }
    scoreNum.SetText(std::to_string(player.getScore()));
    // Player win when all bricks are removed
    if (restBricks <= 0) {
      level++;
      if (level > maxLevel) {
        gameState = GameState::PauseClearGame;
        notificationText.SetText(
            languageSelector.getContent("PAUSE_CLEAR_GAME"));
        level = 1;
      } else {
        gameState = GameState::PauseWin;
        notificationText.SetText(languageSelector.getContent("PAUSE_WIN_GAME"));
      }
      Mix_PlayChannel(-1, winSound.get(), 0);
      // Reset paddle and ball
      initBall();
      initPaddle();
      // Generate new level bricks
      bricks = bricksGenerator.getLevelBricks(level - 1);
      restBricks = bricks.size();
    }
  }
  // Update Texts
  levelNum.SetText(std::to_string(level));
}

// Render
// The render function gets called once per loop
void BreakoutGame::render() {
  SDL_SetRenderDrawColor(gRenderer.get(), 0x22, 0x22, 0x22, 0xFF);
  SDL_RenderClear(gRenderer.get());
  // Render wall
  SDL_SetRenderDrawColor(gRenderer.get(), 0x82, 0x82, 0x82, 0xFF);
  wallLeft.Draw(gRenderer.get());
  wallRight.Draw(gRenderer.get());
  // Render ball
  SDL_SetRenderDrawColor(gRenderer.get(), 0xFF, 0x00, 0x00, 0xFF);
  ball.Draw(gRenderer.get());
  // Render paddle
  SDL_SetRenderDrawColor(gRenderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
  paddle.Draw(gRenderer.get());
  // Render bricks
  SDL_SetRenderDrawColor(gRenderer.get(), 28, 56, 183, 0xFF);
  for (Brick& brick : bricks) {
    brick.Draw(gRenderer.get());
  }
  // Render Texts
  scoreText.Draw();
  livesText.Draw();
  levelText.Draw();
  scoreNum.Draw();
  livesNum.Draw();
  levelNum.Draw();
  if (gameState != GameState::Running) {
    notificationText.Draw();
  }

  SDL_RenderPresent(gRenderer.get());
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
  gameState = GameState::Initializing;
  notificationText.SetText(languageSelector.getContent("LANGUAGE_CHOOSE"));
  Mix_PlayChannel(-1, backgroundMusic.get(), -1);
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
            notificationText.SetText(
                languageSelector.getContent("PAUSE_NORMAL"));
          } else {
            switch (gameState) {
              case GameState::PauseLoseGame:
                player.setLives(PLAYER_DEFAULT_LIFE_NUM);
                livesNum.SetText(std::to_string(player.getLives()));
                resetBricks();
                break;
              case GameState::PauseLoseLife:
                break;
              case GameState::PauseWin:
                player.setLives(player.getLives() + 1);
                break;
              default:
                break;
            }
            gameState = GameState::Running;
          }
        } else if (event.key.keysym.sym == SDLK_1) {
          languageSelector.useLanguage("en_US");
          updateAllTexts();
        } else if (event.key.keysym.sym == SDLK_2) {
          languageSelector.useLanguage("zh_US");
          updateAllTexts();
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
std::shared_ptr<SDL_Window> BreakoutGame::getSDLWindow() { return gWindow; }

// Get Pointer to Renderer
std::shared_ptr<SDL_Renderer> BreakoutGame::getSDLRenderer() {
  return gRenderer;
}

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
