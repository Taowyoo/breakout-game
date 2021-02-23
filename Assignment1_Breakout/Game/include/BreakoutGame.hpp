/**
 * @file BreakoutGame.hpp
 * @author Yuxiang Cao (cao.yux@northeastern.edu)
 * @brief  BreakoutGame main Class Header
 * @version 1.0.0
 * @date 2021-02-22 21:55:07 -08:00
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef BREAKOUTGAME_HPP
#define BREAKOUTGAME_HPP

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
#include "BricksGenerator.hpp"
#include "Common.h"
#include "LanguageManager.hpp"
#include "Paddle.hpp"
#include "Player.hpp"
#include "Text.hpp"
#include "Wall.hpp"
#include "json.hpp"

/**
 * @brief Breakout Game main Class, where main logic located
 *
 */
class BreakoutGame {
 public:
  /**
   * @brief Construct a new Breakout Game object
   *
   * @param w Game program window width
   * @param h Game program window height
   * @param js Config json object
   */
  BreakoutGame(int w, int h, nlohmann::json js);
  /**
   * @brief Destroy the Breakout Game object
   *
   */
  ~BreakoutGame();
  /**
   * @brief Update game state
   *
   * @param dt Milliseconds passed from last update
   */
  void update(float dt);
  /**
   * @brief Render all things for next frame
   *
   */
  void render();
  /**
   * @brief Game main loop
   *
   */
  void loop();
  /**
   * @brief Get current pointer to SDL_Window object
   *
   * @return std::shared_ptr<SDL_Window> Shared pointer to SDL_Window
   */
  std::shared_ptr<SDL_Window> getSDLWindow();
  /**
   * @brief Get current pointer to SDL_Renderer object
   *
   * @return std::shared_ptr<SDL_Renderer> Shared pointer to SDL_Renderer
   */
  std::shared_ptr<SDL_Renderer> getSDLRenderer();

 private:
  /**
   * @brief Json object contains loaded config data
   *
   */
  nlohmann::json configs;
  /**
   * @brief Current game state
   *
   */
  GameState gameState;

  /**
   * @brief Button state array to represent whether left or right key(also 'a'
   * and 'd') is pressed
   *
   */
  bool buttons[2]{};
  /**
   * @brief Game window height
   *
   */
  int screenHeight;
  /**
   * @brief Game window width
   *
   */
  int screenWidth;
  /**
   * @brief Current game level
   *
   */
  int level = 1;
  /**
   * @brief Max level for this game
   *
   */
  int maxLevel;
  /**
   * @brief SDL window shared pointer
   *
   */
  std::shared_ptr<SDL_Window> gWindow;
  /// SDL renderer shared pointer
  std::shared_ptr<SDL_Renderer> gRenderer;
  /// Font of score,player life,level
  std::shared_ptr<TTF_Font> contentFont_;
  /// Font of all notification
  std::shared_ptr<TTF_Font> menuFont_;
  /// Sound of ball hit wall
  std::shared_ptr<Mix_Chunk> wallHitSound;
  /// Sound of ball hit paddle

  std::shared_ptr<Mix_Chunk> paddleHitSound;
  /// Sound of player win one level
  std::shared_ptr<Mix_Chunk> winSound;
  /// Sound of player lose all lives
  std::shared_ptr<Mix_Chunk> loseSound;
  /// Sound of ball hit brick
  std::shared_ptr<Mix_Chunk> brickHitSound;
  /// Sound of player lose one life
  std::shared_ptr<Mix_Chunk> loseLifeSound;
  /// Background music
  std::shared_ptr<Mix_Chunk> backgroundMusic;
  /// Score Text
  Text scoreText;
  /// Score number Text
  Text scoreNum;
  /// Lives Text
  Text livesText;
  /// Player life number Text
  Text livesNum;
  /// Level Text
  Text levelText;
  /// Level number Text
  Text levelNum;
  /// Notification Text
  Text notificationText;
  /// Player Object store player state
  Player player;
  /// Wall object on the left
  Wall wallLeft;
  /// Wall object on the right
  Wall wallRight;
  /// Ball object
  Ball ball;
  /// Paddle object
  Paddle paddle;
  /// Array of all bricks in current level
  std::vector<Brick> bricks;
  /// Helper class to load level config and generate bricks for each level
  BricksGenerator bricksGenerator;
  /// Helper class to load different language texts
  LanguageSelector languageSelector;
  // Current number of remain bricks
  int restBricks;
  /// Reset all current level bricks' state
  void resetBricks();
  /**
   * @brief Init SDL systems
   *
   * @return true Init SDL and extra systems successfully
   * @return false Error occurs
   */
  bool initSDLSystems();
  /// Init all game Objects
  void initGameObjects();
  /**
   * @brief Load all resource which need IO by using ResourceManger
   *
   * @return true Load all resources successfully
   * @return false Error occurs
   */
  bool loadResources();
  /// Init or reset ball state
  void initBall();
  /// Init or reset paddle state
  void initPaddle();
  /**
   * @brief Load level data from files
   *
   * @return true Read and load level data successfully
   * @return false Error occurs
   */
  bool loadLevels();
  /**
   * @brief Load multi-language text data from file
   *
   * @return true Read and load all data successfully
   * @return false Error occurs
   */
  bool loadLanguages();
  /// Update all texts object when language change
  void updateAllTexts();
  /**
   * @brief Check whether ball collide with paddle
   *
   * @param ball Ball object
   * @param paddle Paddle object
   * @return Contact Collision info
   */
  Contact CheckPaddleCollision(Ball const& ball, Paddle const& paddle);
  /**
   * @brief Check whether ball collide with wall
   *
   * @param ball Ball object
   * @return Contact Collision info
   */
  Contact CheckWallCollision(Ball const& ball);
  /**
   * @brief Check whether ball collide with one brick
   *
   * @param ball Ball object
   * @param brick Brick object
   * @param dt Milliseconds passed from last update
   * @return Contact Collision info
   */
  Contact CheckBrickCollision(Ball const& ball, Brick const& brick, float dt);
};

#endif
