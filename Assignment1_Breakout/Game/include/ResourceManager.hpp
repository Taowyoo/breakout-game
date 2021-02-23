/**
 * @file ResourceManager.hpp
 * @author Yuxiang Cao (cao.yux@northeastern.edu)
 * @brief ResourceManager class header
 * @version 1.0.0
 * @date 2021-02-22 23:35:03 -08:00
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>
#else  // This works for Mac
#include <SDL.h>
#include <SDL_log.h>
#endif

#include <fstream>
#include <memory>
#include <string>
#include <unordered_map>

typedef std::string ResName;
typedef std::string ResFilePath;

/**
 * @brief Singleton ResourceManager manage resources which loaded from files
 *
 */
class ResourceManager {
 private:
  /// ResourceManager name
  std::string name_;
  /// The config file which can be automatically loaded
  std::string cfgFilePath_;
  /// Whether load config file
  bool useConfig_ = false;
  /// (Resource name , Resource file path) pair
  std::unordered_map<ResName, ResFilePath> fileMap_;
  /// (Resource name , Resource pointer) pair
  std::unordered_map<ResName, std::shared_ptr<SDL_RWops>> resMap_;
  /**
   * @brief Construct a new Resource Manager object
   *
   */
  ResourceManager() : name_("Not Set"), cfgFilePath_("") {}
  /// Abandon copy constructor
  ResourceManager(const ResourceManager& other) = delete;
  /// Abandon copy assign
  ResourceManager& operator=(const ResourceManager& other) = delete;

 public:
  /**
   * @brief Get the reference to the ResourceManager Instance
   *
   * @return ResourceManager& The reference to the ResourceManager Instance
   */
  static ResourceManager& getInstance() {
    // Lazy initialize.
    static ResourceManager* instance = new ResourceManager();
    return *instance;
  }
  /**
   * @brief Get number of resources
   *
   * @return size_t Number of resources
   */
  size_t size() const { return resMap_.size(); }
  /**
   * @brief Get the name of ResourceManager
   *
   * @return std::string Name string
   */
  std::string name() const { return name_; }
  /**
   * @brief Init the ResourceManager
   *
   * @param name The name of the ResourceManager
   * @param cfgFilePath Config file path, if empty then manage will not load
   * config file
   */
  void init(const std::string& name, const std::string& cfgFilePath) {
    name_ = name;
    cfgFilePath_ = cfgFilePath;
    // read asset config from config file
    if (!cfgFilePath.empty()) {
      std::ifstream paths(cfgFilePath);

      if (paths.is_open()) {
        ResName resName;
        ResFilePath resPath;

        while (!paths.eof()) {
          paths >> resName >> resPath;
          fileMap_.emplace(resName, resPath);
        }

        paths.close();
        useConfig_ = true;
        return;
      }
      SDL_Log("Fail to open %s!", cfgFilePath.c_str());
    }
    SDL_Log("Succeed to init ResourceManager!");
  }
  /**
   * @brief Start the manager, if preload enable, then load all resource
   * according to the config file
   *
   * @param preload Whether preload
   * @param args Extra args
   * @return true Success to start
   * @return false Fail to start
   */
  bool startManager(bool preload = false, void* args = nullptr) {
    if (useConfig_ && preload) {
      for (auto const& kv : fileMap_) {
        if (!AddResource(kv.first, kv.second, args)) {
          SDL_Log("Fail load resources from config file: '%s'!",
                  cfgFilePath_.c_str());
          return false;
        }
      }
    }
    return true;
  }
  /**
   * @brief Stop the manager
   *
   * @return true Success to start
   * @return false Fail to start
   */
  bool stopManager() {
    name_ = "Not Set";
    useConfig_ = false;
    fileMap_.clear();
    RemoveAllResource();
    return true;
  }
  /**
   * @brief Add a resource by find and load resource in resource-path map
   *
   * @param resName Resource name
   * @param args Extra args
   * @return true Success to add
   * @return false Fail to add
   */
  bool AddResource(const ResName& resName, void* args) {
    // find in fileMap_
    auto it = fileMap_.find(resName);
    if (it == fileMap_.end()) {
      SDL_Log("Fail to add %s, resource does not exist in config file: '%s'!",
              resName.c_str(), cfgFilePath_.c_str());
      return false;
    }
    return AddResource(resName, it->second, args);
  }
  /**
   * @brief Directly add a new resource
   *
   * @param resName Resource name
   * @param newRes Pointer to the resource object
   * @return true Success to add
   * @return false Fail to add
   */
  bool AddResource(const ResName& resName, std::shared_ptr<SDL_RWops> newRes) {
    auto ret = resMap_.emplace(resName, newRes);
    if (!ret.second) {
      SDL_Log("Fail to add %s, duplicate resource name!", resName.c_str());
      return false;
    }
    return true;
  }
  /**
   * @brief Add a resource from file
   *
   * @param resName Resource name
   * @param resPath Resource file path
   * @param args Extra args
   * @return true Success to add
   * @return false Fail to add
   */
  bool AddResource(const ResName& resName, const ResFilePath& resPath,
                   void* args) {
    auto it = resMap_.find(resName);
    if (it != resMap_.end()) {
      SDL_Log("Fail to add %s, duplicate resource name!", resName.c_str());
      return false;
    }
    fileMap_.emplace(resName, resPath);
    std::shared_ptr<SDL_RWops> newRes(SDL_RWFromFile(resPath.c_str(), "rb"),
                                      SDL_FreeRW);
    resMap_.emplace(resName, newRes);
    SDL_Log("Added %s from %s.", resName.c_str(), resPath.c_str());
    return true;
  }
  /**
   * @brief Offer a resource to others to use
   *
   * @param resName Resource name
   * @return std::shared_ptr<SDL_RWops> The pointer to the resource
   */
  std::shared_ptr<SDL_RWops> LoadResource(const ResName& resName) const {
    auto it = resMap_.find(resName);
    std::shared_ptr<SDL_RWops> ret;
    if (it == resMap_.end()) {
      SDL_Log("Fail to load %s, resource does not exist!", resName.c_str());
      return nullptr;
    }
    ret = (*it).second;
    return ret;
  }
  /**
   * @brief Remove one resource by name
   *
   * @param resName Resource name
   * @return true Success to remove
   * @return false Fail to remove
   */
  bool RemoveResource(const ResName& resName) {
    auto it = resMap_.find(resName);
    if (it != resMap_.end()) {
      resMap_.erase(it);
      return true;
    }
    SDL_Log("Resource to remove does not exist!");
    return false;
  }
  /**
   * @brief Remove all resources
   *
   * @return true Success to remove
   * @return false Fail to remove
   */
  bool RemoveAllResource() {
    auto it = resMap_.begin();
    while (it != resMap_.end()) {
      it = resMap_.erase(it);
    }
    return true;
  }
  /**
   * @brief Destroy the Resource Manager object
   *
   */
  ~ResourceManager() { RemoveAllResource(); }
};

#endif  // RESOURCE_MANAGER_HPP