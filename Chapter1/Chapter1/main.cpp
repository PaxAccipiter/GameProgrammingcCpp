#include "Game.h"

//SDL��main��_sdl_main�ɕς��Ă��܂��炵���B
int main(int argc, char** argv) {
	
	Game game;
	
	bool success = game.Initialize();

	if (success) {
		game.RunLoop();
	}

	game.Shutdown();

	return 0;
}