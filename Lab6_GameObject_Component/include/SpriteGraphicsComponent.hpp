#ifndef SPRITEGRAPHICSCOMPONENT_HPP
#define SPRITEGRAPHICSCOMPONENT_HPP

#include "GraphicsComponent.hpp"
class SpriteGraphicsComponent : public GraphicsComponent {
 public:
  SpriteGraphicsComponent(SDL_Renderer* g_renderer, TransformComponent* tf,
                          unsigned int startFrame, unsigned int maxFrame)
      : GraphicsComponent{g_renderer, tf},
        m_currentFrame{startFrame},
        m_maxFrame{maxFrame} {};
  virtual ~SpriteGraphicsComponent(){};
  virtual void update();

 protected:
  unsigned int m_currentFrame{0};
  unsigned int m_maxFrame{7};
};

#endif