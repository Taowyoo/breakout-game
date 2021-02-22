
#include "BreakoutGame.hpp"
#include "ConfigUtil.hpp"
int main(int argc, char** argv) {
  // Create an instance of an object for a BreakoutGame
  auto json = ConfigUtil::loadConfig("config/config.json");
  ConfigUtil::loadAllVariables(json);
  // nlohmann::json json;
  BreakoutGame myBreakoutGame(WINDOW_WIDTH, WINDOW_HEIGHT, json);
  // Run our program forever
  myBreakoutGame.loop();
  // When our program ends, it will exit scope, the
  // destructor will then be called and clean up the program.
  return 0;
}
