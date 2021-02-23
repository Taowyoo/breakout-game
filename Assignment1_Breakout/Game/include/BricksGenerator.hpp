/**
 * @file BricksGenerator.hpp
 * @author Yuxiang Cao (cao.yux@northeastern.edu)
 * @brief Header file for BricksGenerator
 * @version 1.0.0
 * @date 2021-02-22 22:47:39 -08:00
 *
 * @copyright Copyright (c) 2021
 *
 */
#if !defined(BRICKS_GENERATOR_HPP)
#define BRICKS_GENERATOR_HPP
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Brick.hpp"
#include "Common.h"
/**
 * @brief Struct to store brick arrangement data of one level
 *
 */
struct LevelData {
  /// Raw data stored in string for each row of bricks
  std::vector<std::string> data;
};
/**
 * @brief Helper class to load and generate each level bricks arrangement
 *
 */
class BricksGenerator {
 private:
  /// All level data store in an array
  std::vector<LevelData> allLevels;

 public:
  /**
   * @brief Load one level config data form a file
   *
   * @param path File path
   * @return true Success to load
   * @return false Error occurs
   */
  bool loadOneLevelData(const std::string& path) {
    std::ifstream ifs(path);
    if (!ifs.is_open()) {
      std::cerr << "Fail to load level config file: " << path << std::endl;
      return false;
    }
    LevelData levelData;
    while (!ifs.eof()) {
      std::string line;
      ifs >> line;
      //   std::cerr << "[log] " << line << std::endl;
      if (!line.empty()) levelData.data.push_back(line);
    }
    allLevels.push_back(levelData);
    return true;
  }
  /**
   * @brief Get the bricks info of specific level
   *
   * @param level Level number
   * @return std::vector<Brick> Bricks array
   */
  std::vector<Brick> getLevelBricks(int level) const {
    std::vector<Brick> bricks;
    bricks.reserve(BRICK_COLUMN * BRICK_ROW);
    int brickSumWidth =
        BRICK_COLUMN * BRICK_WIDTH + (BRICK_COLUMN - 1) * BRICK_INTERVAL;
    int brickStartX = (WINDOW_WIDTH - brickSumWidth) / 2;
    int brickStartY = BRICK_START_HEIGHT;
    LevelData const& curLevel = allLevels[level];
    for (int i = 0, x = brickStartX, y = brickStartY; i < BRICK_ROW; i++) {
      for (int j = 0; j < BRICK_COLUMN; j++) {
        auto ch = curLevel.data[i][j];
        if (ch != '0') {
          Brick b(Vector2D(x, y), true);
          b.setScore(ch - '0');
          bricks.push_back(b);
        }
        x += BRICK_WIDTH + BRICK_INTERVAL;
      }
      x = brickStartX;
      y += BRICK_HEIGHT + BRICK_INTERVAL;
    }
    return bricks;
  }
  /**
   * @brief Get the Max Level
   *
   * @return int Max Level number
   */
  int getMaxLevel() const { return allLevels.size(); }
};

#endif  // BRICKS_GENERATOR_HPP
