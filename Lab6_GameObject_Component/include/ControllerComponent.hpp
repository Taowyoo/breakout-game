#ifndef CONTROLLERCOMPONENT_HPP
#define CONTROLLERCOMPONENT_HPP

#include "Component.hpp"
#include "TransformComponent.hpp"
class ControllerComponent : public Component {
 public:
  ControllerComponent(TransformComponent* tf) : transform{tf} {};
  virtual ~ControllerComponent(){};
  virtual void update() = 0;

 protected:
  TransformComponent* transform;
};

#endif
