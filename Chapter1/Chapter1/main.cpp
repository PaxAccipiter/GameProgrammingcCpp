#include "Game.h"

//SDL‚Ímain‚ğ_sdl_main‚É•Ï‚¦‚Ä‚µ‚Ü‚¤‚ç‚µ‚¢B
int main(int argc, char** argv) {
	
	Game game;
	
	bool success = game.Initialize();

	if (success) {
		game.RunLoop();
	}

	game.Shutdown();

	return 0;
}