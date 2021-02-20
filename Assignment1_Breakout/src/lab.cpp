
#include "BreakoutGame.hpp"

int main(int argc, char** argv){
	// Create an instance of an object for a BreakoutGame
	BreakoutGame myBreakoutGame(1280,720);
	// Run our program forever
	myBreakoutGame.loop();
	// When our program ends, it will exit scope, the
	// destructor will then be called and clean up the program.
	return 0;
}
