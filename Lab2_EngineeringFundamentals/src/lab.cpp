#include "PongGame.h"

int main(int argc, char *argv[]) {

  PongGame myGame(1280u, 720u);
  // Run our program forever
  myGame.Loop();
  // When our program ends, it will exit scope, the
  // destructor will then be called and clean up the program.
  return 0;
}