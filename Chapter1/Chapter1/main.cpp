#include "Game.h"

//ToDo 3���Ń_���ɂ���B(����ۑ�)
//2�l�ŗV�ׂ�悤�ɂ���
//�}���`�{�[��
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