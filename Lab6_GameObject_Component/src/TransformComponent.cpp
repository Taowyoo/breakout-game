#include "TransformComponent.hpp"
void TransformComponent::update() {
  rect.x += speed_x;
  rect.y += speed_y;
}
void TransformComponent::updatePos(int x, int y) {
  rect.x = x;
  rect.y = y;
}
void TransformComponent::updateSize(int w, int h) {
  rect.w = w;
  rect.h = h;
}
void TransformComponent::updateSpeed(int s_x, int s_y) {
  speed_x = s_x;
  speed_y = s_y;
}
const SDL_Rect& TransformComponent::getSDLRect() const { return rect; }