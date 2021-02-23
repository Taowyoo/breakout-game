#if !defined(PLAYER_HPP)
#define PLAYER_HPP
#include "Common.h"

/**
 * @brief Player class, store info of the player
 *
 */
class Player {
 private:
  /// Curret score of the player
  int score = 0;
  /// Current rest lives of the player
  int lives = PLAYER_DEFAULT_LIFE_NUM;

 public:
  /**
   * @brief Construct a new Player object
   *
   */
  Player() = default;
  /**
   * @brief Construct a new Player object
   *
   * @param s Default score
   * @param l Default livies
   */
  Player(int s, int l) : score(s), lives(l) {}
  /**
   * @brief Add score
   *
   * @param s Number to add
   */
  void addScore(int s) { score += s; }
  /**
   * @brief Set the Score
   *
   * @param s Number to set
   */
  void setScore(int s) { score = s; }
  /**
   * @brief Set the Lives
   *
   * @param l Number to set
   */
  void setLives(int l) { lives = l; }
  /**
   * @brief lose one life
   *
   * decrease 1 on lives
   */
  void loseLife() {
    if (lives > 0) --lives;
  }
  /**
   * @brief Get the current player's score
   *
   * @return int Score number
   */
  int getScore() const { return score; }
  /**
   * @brief Get the current player's lives
   *
   * @return int Lives number
   */
  int getLives() const { return lives; }
};

#endif  // PLAYER_HPP
