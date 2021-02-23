/**
 * @file main.cpp
 * @author Yuxiang Cao (cao.yux@northeastern.edu)
 * @brief Enter point of the game
 * @version 1.0.0
 * @date 2021-02-22 23:25:35 -08:00
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "BreakoutGame.hpp"
#include "ConfigUtil.hpp"
/**
 * @brief Main function of the game
 *
 * @param argc Number of argument
 * @param argv Argument string array
 * @return int Program exit state
 */
int main(int argc, char** argv) {
  // Create an instance of an object for a BreakoutGame
  auto json = ConfigUtil::loadConfig("../config/config.json");
  ConfigUtil::loadAllVariables(json);
  // nlohmann::json json;
  BreakoutGame myBreakoutGame(WINDOW_WIDTH, WINDOW_HEIGHT, json);
  // Run our program forever
  myBreakoutGame.loop();
  // When our program ends, it will exit scope, the
  // destructor will then be called and clean up the program.
  return 0;
}
