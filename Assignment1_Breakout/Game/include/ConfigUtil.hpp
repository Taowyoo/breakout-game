/**
 * @file ConfigUtil.hpp
 * @author Yuxiang Cao (cao.yux@northeastern.edu)
 * @brief Helper class to load config from file
 * @version 1.0.0
 * @date 2021-02-22 23:05:14 -08:00
 *
 * @copyright Copyright (c) 2021
 *
 */
#if !defined(CONFIG_UTIL_HPP)
#define CONFIG_UTIL_HPP
#include <fstream>
#include <string>
#include <unordered_map>

#include "Common.h"
#include "json.hpp"

/**
 * @brief Help class which use nlohmann::json library to process json format
 * config file
 *
 */
class ConfigUtil {
 public:
  /**
   * @brief Get json object from file
   *
   * @param path File path
   * @return nlohmann::json Deserialized json object
   */
  static nlohmann::json loadConfig(const std::string& path) {
    std::ifstream ifs(path);
    if (!ifs.is_open()) {
      printf("Fail to open config file: '%s'!\n", path.c_str());
    }
    nlohmann ::json j;
    ifs >> j;
    return j;
  }
  /**
   * @brief Update all global variable value from json format config
   *
   * @param js Input json object
   */
  static void loadAllVariables(nlohmann::json& js) {
    WINDOW_WIDTH = js["WINDOW_WIDTH"];
    WINDOW_HEIGHT = js["WINDOW_HEIGHT"];

    GAME_SCENE_WIDTH = js["GAME_SCENE_WIDTH"];
    GAME_SCENE_LEFT = (WINDOW_WIDTH - GAME_SCENE_WIDTH) / 2;
    GAME_SCENE_RIGHT = (WINDOW_WIDTH + GAME_SCENE_WIDTH) / 2;
    WALL_WIDTH = js["WALL_WIDTH"];
    PADDLE_SPEED = js["PADDLE_SPEED"];
    PADDLE_WIDTH = js["PADDLE_WIDTH"];
    PADDLE_HEIGHT = js["PADDLE_HEIGHT"];
    PADDLE_DISTANCE_FROM_BOTTOM = js["PADDLE_DISTANCE_FROM_BOTTOM"];

    BALL_START_DEGREE = js["BALL_START_DEGREE"];
    BALL_SPEED = js["BALL_SPEED"];
    BALL_WIDTH = js["BALL_WIDTH"];
    BALL_HEIGHT = js["BALL_HEIGHT"];

    BRICK_START_HEIGHT = js["BRICK_START_HEIGHT"];
    BRICK_WIDTH = js["BRICK_WIDTH"];
    BRICK_HEIGHT = js["BRICK_HEIGHT"];
    BRICK_INTERVAL = js["BRICK_INTERVAL"];
    BRICK_ROW = js["BRICK_ROW"];
    BRICK_COLUMN = js["BRICK_COLUMN"];
    BRICK_DEFAULT_SCORE = js["BRICK_DEFAULT_SCORE"];
    PLAYER_DEFAULT_LIFE_NUM = js["PLAYER_DEFAULT_LIFE_NUM"];

    DEFAULT_LEVEL = js["DEFAULT_LEVEL"];

    DEFAULT_FONT_SIZE = js["DEFAULT_FONT_SIZE"];
    MENU_FONT_SIZE = js["MENU_FONT_SIZE"];

    SCREEN_FPS_60 = js["SCREEN_FPS_60"];
    SCREEN_TICKS_PER_FRAME_60 = 1000 / SCREEN_FPS_60;

    TICKS_PER_UPDATE = js["TICKS_PER_UPDATE"];
  }
};

#endif  // CONFIG_UTIL_HPP
