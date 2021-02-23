/**
 * @file LanguageManager.hpp
 * @author Yuxiang Cao (cao.yux@northeastern.edu)
 * @brief Helper class LanguageSelector
 * @version 1.0.0
 * @date 2021-02-22 23:15:42 -08:00
 *
 * @copyright Copyright (c) 2021
 *
 */
#if !defined(LANGUAGE_SELECTOR_HPP)
#define LANGUAGE_SELECTOR_HPP
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include "json.hpp"
/**
 * @brief Struct to store all key-value pair of game texts
 *
 */
struct Language {
  std::unordered_map<std::string, std::string> data;
};
/**
 * @brief Help class to read, load and manage multi language text data
 *
 */
class LanguageSelector {
 private:
  /// all language text data
  std::unordered_map<std::string, Language> languages;
  /// current language
  std::string currentLanguage;

 public:
  /**
   * @brief Read and load one language data file
   *
   * @param path File path
   * @param name Language name
   * @return true Success to read and load
   * @return false Error occurs
   */
  bool loadOneLanguageContent(const std::string& path,
                              const std::string& name) {
    nlohmann::json json;
    std::ifstream ifs(path);
    if (!ifs.is_open()) {
      std::cerr << "Fail to load language content file: " << path << std::endl;
      return false;
    }
    ifs >> json;
    Language lan;
    for (auto& kv : json.items()) {
      lan.data.emplace(kv.key(), kv.value().get<std::string>());
    }

    currentLanguage = name;
    languages.emplace(currentLanguage, lan);
    std::cout << "Loaded " << currentLanguage << " from " << path << std::endl;
    return true;
  }
  std::string const& getContent(const std::string& key) const {
    return languages.at(currentLanguage).data.at(key);
  }
  /**
   * @brief Set current language
   *
   * @param lan Language name
   */
  void useLanguage(std::string const& lan) { currentLanguage = lan; }
};

#endif  // LANGUAGE_SELECTOR_HPP
