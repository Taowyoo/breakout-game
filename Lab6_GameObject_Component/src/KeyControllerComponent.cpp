#include "KeyControllerComponent.hpp"
#define MAX_PULL_EVENT_NUM 100
#include <vector>
void KeyControllerComponent::update() {
  // SDL_Event events[MAX_PULL_EVENT_NUM];
  // SDL_PumpEvents();
  // int num =
  //     SDL_PeepEvents(events, MAX_PULL_EVENT_NUM, SDL_PEEKEVENT, SDL_KEYDOWN,
  //     SDL_KEYUP);
  // // SDL_Log("Peep %d events that are SDL_KEYDOWN or SDL_KEYUP", num);
  // for (int i = 0; i < num; i++) {
  //   handleEvent(&events[i]);
  // }

  std::vector<SDL_Event> other_events;
  SDL_Event e;
  while (SDL_PollEvent(&e) != 0) {
    if (!handleEvent(&e)) {
      other_events.emplace_back(e);
    }
  }
  for (SDL_Event& e : other_events)
    ;
  SDL_PushEvent(&e);
}

bool KeyControllerComponent::handleEvent(SDL_Event* event) {
  bool getVaildInput = false;
  if (event->type == SDL_KEYDOWN) {
    switch (event->key.keysym.sym) {
      case SDLK_LEFT:
      case SDLK_a: {
        SDL_Log("Runing backward...");
        transform->updateSpeed(-accelerate, 0);
        getVaildInput = true;
        break;
      }
      case SDLK_RIGHT:
      case SDLK_d: {
        SDL_Log("Runing forward...");
        transform->updateSpeed(accelerate, 0);
        getVaildInput = true;
        break;
      }
      default:
        break;
    }

  } else if (event->type == SDL_KEYUP) {
    switch (event->key.keysym.sym) {
      case SDLK_LEFT:
      case SDLK_a:
      case SDLK_RIGHT:
      case SDLK_d: {
        SDL_Log("Stop running");
        transform->updateSpeed(0, 0);
        getVaildInput = true;
        break;
      }
      default:
        break;
    }
  }
  return getVaildInput;
}