#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include "Component.hpp"

class TransformComponent : public Component {
 public:
  TransformComponent(int x, int y, int w, int h)
      : rect{x, y, w, h}, speed_x{0}, speed_y{0} {};
  virtual ~TransformComponent(){};
  virtual void update();
  void updatePos(int x, int y);
  void updateSize(int w, int h);
  void updateSpeed(int s_x, int s_y);
  const SDL_Rect& getSDLRect() const;

 protected:
  SDL_Rect rect;
  int speed_x;
  int speed_y;
};

#endif
