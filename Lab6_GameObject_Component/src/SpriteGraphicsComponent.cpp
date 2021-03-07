#include "SpriteGraphicsComponent.hpp"

void SpriteGraphicsComponent::update() {
  m_currentFrame++;
  if (m_currentFrame > m_maxFrame) {
    m_currentFrame = 0;
  }
  m_src.x = m_currentFrame * 75;
  m_src.y = 0;
  m_src.w = 75;
  m_src.h = 87;
  Render();
}