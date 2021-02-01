#include "Rectangle.h"

void Rectangle::init(int screenWidth, int screenHeight) {
  x = rand() % screenWidth;
  y = rand() % screenHeight;
  w = rand() % 100;
  h = rand() % 100;
  speed = rand() % 2 + 1;
}

// Arguments here are a little redundant--do we need them?
// (Perhaps if the screen resizes? Hmm!)
void Rectangle::update(int screenWidth, int screenHeight) {
  if (up) {
    y += speed;
    if (y > screenHeight) {
      up = !up;
    }
  }

  if (!up) {
    y -= speed;
    if (y < 0) {
      up = !up;
    }
  }
  if (left) {
    x += speed;
    if (x > screenWidth) {
      left = !left;
    }
  }

  if (!left) {
    x -= speed;
    if (x < 0) {
      left = !left;
    }
  }
}

// Okay, render our rectangles!
void Rectangle::render(SDL_Renderer *gRenderer) {
  SDL_Rect fillRect = {x, y, w, h};
  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
  SDL_RenderDrawRect(gRenderer, &fillRect);
}