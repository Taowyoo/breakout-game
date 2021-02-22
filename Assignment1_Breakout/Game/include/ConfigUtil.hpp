#if !defined(CONFIG_UTIL_HPP)
#define CONFIG_UTIL_HPP
#include <fstream>
#include <string>
#include <unordered_map>

#include "json.hpp"
class ConfigUtil {
 public:
  static nlohmann::json loadConfig(const std::string& path) {
    std::ifstream ifs(path);
    if (!ifs.is_open()) {
      printf("Fail to open config file: '%s'!\n", path.c_str());
    }
    nlohmann ::json j;
    ifs >> j;
    return j;
  }
};

#endif  // CONFIG_UTIL_HPP
