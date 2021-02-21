#if !defined(PLAYER_HPP)
#define PLAYER_HPP
#include "Common.h"

class Player {
 private:
  int score = 0;
  int lives = PLAYER_DEFAULT_LIFE_NUM;

 public:
  Player() = default;
  Player(int s, int l) : score(s), lives(l) {}

  void setScore(int s) { score = s; }
  void setLives(int l) { lives = l; }
  void loseLife() {
    if (lives > 0) --lives;
  }
  int getScore() const { return score; }
  int getLives() const { return lives; }
};

#endif  // PLAYER_HPP
