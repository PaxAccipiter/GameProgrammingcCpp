#pragma once
#include "SDL/SDL.h"

class Game {
public:
	Game();
	//デストラクタないけどいらないの？？
	~Game();

	void Initialize();
	void RunLoop();
	void Shutdown();

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

};