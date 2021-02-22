#if !defined(SOUDN_RES_HPP)
#define SOUDN_RES_HPP

#include "BaseResource.hpp"
#if defined(LINUX) || defined(MINGW) || defined(__linux__)
#include <SDL2/SDL_mixer.h>
#else
// Windows and Mac use a different path
// If you have compilation errors, change this as needed.
#include <SDL2/SDL_mixer.h>
#endif
#include <iostream>
#include <memory>

class SoundRes : public BaseResource {
 private:
  std::shared_ptr<Mix_Chunk> sound;

 public:
  SoundRes(const std::string& resourceFileName, void* args)
      : BaseResource(resourceFileName, args) {}
  ~SoundRes(){};
  void LoadFromFile(const std::string& resourcePath, void* args) {
    sound = std::shared_ptr<Mix_Chunk>(Mix_LoadWAV(resourcePath.c_str()),
                                       Mix_FreeChunk);
    if (sound == nullptr) {
      std::cerr << "Sound file could not be loaded! SDL_Mix Error: "
                << Mix_GetError() << "\n";
    }
  }
  std::shared_ptr<Mix_Chunk> getRes() const { return sound; }
};

#endif  // SOUDN_RES_HPP
