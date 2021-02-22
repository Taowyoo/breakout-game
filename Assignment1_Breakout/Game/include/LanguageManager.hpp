#if !defined(LANGUAGE_SELECTOR_HPP)
#define LANGUAGE_SELECTOR_HPP
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include "json.hpp"
struct Language {
  std::unordered_map<std::string, std::string> data;
};

class LanguageSelector {
 private:
  std::unordered_map<std::string, Language> languages;
  std::string currentLanguage;

 public:
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
      std::cout << "[Lan] " << kv.key() << " , " << kv.value() << std::endl;
    }

    currentLanguage = name;
    languages.emplace(currentLanguage, lan);
    std::cout << "Loaded " << currentLanguage << " from " << path << std::endl;
    return true;
  }
  std::string const& getContent(const std::string& key) const {
    return languages.at(currentLanguage).data.at(key);
  }
  void useLanguage(std::string const& lan) { currentLanguage = lan; }
};

#endif  // LANGUAGE_SELECTOR_HPP
