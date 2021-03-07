#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else  // This works for Mac
#include <SDL.h>
#endif

class Component {
 public:
  virtual ~Component(){};
  virtual void update() = 0;

 private:
};

#endif
