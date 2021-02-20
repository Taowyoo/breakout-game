#ifndef PONGGAMME_H_
#define PONGGAMME_H_

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

#include "Ball.h"
#include "Common.h"
#include "Paddle.h"
#include "Text.h"

class PongGame {
  enum Winner {
    None = 0,
    PlayerOne,
    PlayerTwo,
  };

 private:
  // Screen dimension constants
  Uint32 screen_height_;
  Uint32 screen_width_;
  // Sound Effects
  Mix_Chunk* wallHitSound = nullptr;
  Mix_Chunk* paddleHitSound = nullptr;
  Mix_Chunk* winSound = nullptr;
  // The window we'll be rendering to
  SDL_Window* window_ = nullptr;
  // SDL Renderer
  SDL_Renderer* renderer_ = nullptr;
  // Font
  TTF_Font* font_ = nullptr;
  Contact CheckPaddleCollision(Ball const& ball, Paddle const& paddle);
  Contact CheckWallCollision(Ball const& ball);

  // State array of four direction bottons
  bool buttons[4] = {};

  // Two player's score
  int playerOneScore = 0;
  int playerTwoScore = 0;
  // Ponters of objects in game
  Text* playerOneScoreText = nullptr;
  Text* playerTwoScoreText = nullptr;
  Text* winText = nullptr;
  Ball* ball = nullptr;
  Paddle* paddleOne = nullptr;
  Paddle* paddleTwo = nullptr;
  // Game state
  bool pause_ = false;
  bool rebegin_ = false;
  Winner winner_ = Winner::None;
 public:
  PongGame(Uint32 w, Uint32 h);
  ~PongGame();
  // Per frame update
  void Update(float dt = 0);
  // Renders shapes to the screen
  void Render();
  // loop that runs forever
  void Loop();
};

#endif  // PONGGAMME_H_