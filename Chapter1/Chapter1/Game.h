#pragma once
#include "SDL/SDL.h"

class Game {
public:
	Game();

	//ゲームを初期化する
	bool Initialize();

	//ゲームオーバーまでゲームループを実行する
	void RunLoop();

	//ゲームをシャットダウンする
	void Shutdown();

private:

	//入力処理
	void ProcessInput();

	//フレームアップデート
	void UpdateGame();

	//出力生成
	void GenerateOutput();

	//SDLが作るウィンドウ
	SDL_Window* mWindow;

	//ゲームの続行を支持する
	bool mlsRunning;
};

