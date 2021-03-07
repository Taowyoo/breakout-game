#ifndef KEYCONTROLLERCOMPONENT_HPP
#define KEYCONTROLLERCOMPONENT_HPP

#include "ControllerComponent.hpp"
class KeyControllerComponent : public ControllerComponent {
 public:
  KeyControllerComponent(TransformComponent* tf) : ControllerComponent{tf} {};
  virtual ~KeyControllerComponent(){};
  virtual void update();

 protected:
  int accelerate = 1;
};

#endif