#include "GameObject.hpp"

void GameObject::AddComponent(Component* new_component) {
  m_components.emplace_back(new_component);
}

bool GameObject::RemoveComponent(int idx) {
  if (idx < 0 || idx >= m_components.size()) {
    SDL_Log("Failed to remove component, invalid input idx: %d", idx);
    return false;
  }
  Component* to_remove = *(m_components.begin() + idx);
  if (to_remove)
    delete to_remove;
  else {
    SDL_Log("Failed to free the component when remove it from GameObject");
  }
  m_components.erase(m_components.begin() + idx);
  return true;
}
void GameObject::update() {
  for (auto& component : m_components) {
    component->update();
  }
}
GameObject::~GameObject() {
  for (Component* c_ptr : m_components) {
    if (c_ptr) delete c_ptr;
  }
}