#include "Game.h"

//ToDo 3乙でダメにする。(自主課題)
//2人で遊べるようにする
//マルチボール
//SDLはmainを_sdl_mainに変えてしまうらしい。
int main(int argc, char** argv) {
	
	Game game;
	
	bool success = game.Initialize();

	if (success) {
		game.RunLoop();
	}

	game.Shutdown();

	return 0;
}