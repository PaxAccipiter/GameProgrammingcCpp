#pragma once
#include "SDL/SDL.h"

class Game {
public:
	Game();
	//�f�X�g���N�^�Ȃ����ǂ���Ȃ��́H�H
	~Game();

	void Initialize();
	void RunLoop();
	void Shutdown();

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

};