#include "KeyControllerComponent.hpp"
#define MAX_PULL_EVENT_NUM 100
void KeyControllerComponent::update() {
  SDL_Event events[MAX_PULL_EVENT_NUM];
  int num = SDL_PeepEvents(events, MAX_PULL_EVENT_NUM, SDL_GETEVENT,
                           SDL_KEYDOWN, SDL_KEYUP);
  // User posts an event to quit
  // An example is hitting the "x" in the corner of the window.
  for (int i = 0; i < num; i++) {
    SDL_Event* event = &events[i];
    if (event->type == SDL_KEYDOWN) {
      if (event->key.keysym.sym == SDLK_a) {
        transform->updateSpeed(-accelerate, 0);
      } else if (event->key.keysym.sym == SDLK_d) {
        transform->updateSpeed(accelerate, 0);
      }
    } else if (event->type == SDL_KEYUP) {
      if (event->key.keysym.sym == SDLK_a || event->key.keysym.sym == SDLK_d) {
        transform->updateSpeed(0, 0);
      }
    }
  }
}