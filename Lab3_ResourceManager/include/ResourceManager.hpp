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
#include <string>
#include <unordered_map>

namespace yx {

typedef std::string ResName;
typedef std::string ResFilePath;
typedef int ResRefCount;

template <typename T>
class ResourceManager {
 private:
  std::string name_;
  std::string cfgFilePath_;
  bool useConfig_ = false;
  SDL_Renderer* renderer_;
  std::unordered_map<ResName, ResFilePath> fileMap_;
  std::unordered_map<ResName, T*> resMap_;

  ResourceManager() : name_("Not Set"), cfgFilePath_("") {}
  ResourceManager(const ResourceManager& other) = delete;
  ResourceManager& operator=(const ResourceManager& other) = delete;

 public:
  static ResourceManager& getInstance() {
    // Lazy initialize.
    static ResourceManager* instance = new ResourceManager();
    return *instance;
  }

  size_t size() const { return resMap_.size(); }
  std::string name() const { return name_; }

  void init(const std::string& name, const std::string& cfgFilePath,
            SDL_Renderer* renderer) {
    name_ = name;
    cfgFilePath_ = cfgFilePath;
    renderer_ = renderer;
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

  bool startManager(bool preload = false) {
    if (useConfig_ && preload) {
      for (auto const& kv : fileMap_) {
        if (!AddResource(kv.first, kv.second)) {
          SDL_Log("Fail load resources from config file: '%s'!",
                  cfgFilePath_.c_str());
          return false;
        }
      }
    }
    return true;
  }

  bool stopManager() {
    name_ = "Not Set";
    useConfig_ = false;
    fileMap_.clear();
    RemoveAllResource();
  }

  bool AddResource(const ResName& resName) {
    // find in fileMap_
    auto it = fileMap_.find(resName);
    if (it == fileMap_.end()) {
      SDL_Log("Fail to add %s, resource does not exist in config file: '%s'!",
              resName.c_str(), cfgFilePath_.c_str());
      return false;
    }
    return AddResource(resName, it->second);
  }

  bool AddResource(const ResName& resName, T* newRes) {
    auto ret = resMap_.emplace(resName, newRes);
    if (!ret.second) {
      SDL_Log("Fail to add %s, duplicate resource name!", resName.c_str());
      return false;
    }
    return true;
  }

  bool AddResource(const ResName& resName, const ResFilePath& resPath) {
    auto it = resMap_.find(resName);
    if (it != resMap_.end()) {
      SDL_Log("Fail to add %s, duplicate resource name!", resName.c_str());
      return false;
    }
    fileMap_.emplace(resName, resPath);
    T* newRes = new T(resName);
    newRes->loadFromFile(resPath, renderer_);
    resMap_.emplace(resName, newRes);
    SDL_Log("Added %s from %s.", resName.c_str(), resPath.c_str());
    return true;
  }

  T* LoadResource(const ResName& resName) const {
    auto it = resMap_.find(resName);
    if (it == resMap_.end()) {
      SDL_Log("Fail to load %s, resource does not exist!", resName.c_str());
      return nullptr;
    }
    T* ret = (*it).second;
    return ret;
  }

  bool RemoveResource(const ResName& resName) {
    auto it = resMap_.find(resName);
    if (it != resMap_.end()) {
      delete (*it).second;
      resMap_.erase(it);
      return true;
    }
    SDL_Log("Resource to remove does not exist!");
    return false;
  }

  bool RemoveAllResource() {
    auto it = resMap_.begin();
    while (it != resMap_.end()) {
      delete (*it).second;
      it = resMap_.erase(it);
    }
    return true;
  }

  ~ResourceManager() { RemoveAllResource(); }
};

}  // namespace yx

#endif  // RESOURCE_MANAGER_HPP