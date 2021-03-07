#ifndef GRAPHICSCOMPONENT_HPP
#define GRAPHICSCOMPONENT_HPP

#include "Component.hpp"
#include "TransformComponent.hpp"
#include <string>
class GraphicsComponent : public Component {
 public:
  GraphicsComponent(SDL_Renderer* g_renderer, TransformComponent* tf)
      : renderer{g_renderer}, transform{tf} {};
  virtual ~GraphicsComponent() {
    if (m_texture) SDL_DestroyTexture(m_texture);
  };
  virtual void update() = 0;
  virtual void Render();
  virtual void LoadImage(std::string filePath);

 protected:
  SDL_Renderer* renderer;
  TransformComponent* transform;
  SDL_Texture* m_texture = nullptr;
  SDL_Rect m_src = {};
};

#endif