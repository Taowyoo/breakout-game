#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <vector>

#include "Component.hpp"

class GameObject {
 public:
  GameObject() = default;
  ~GameObject();
  void AddComponent(Component* new_component);
  bool RemoveComponent(int idx);
  void update();

 private:
  std::vector<Component*> m_components;
};

#endif
