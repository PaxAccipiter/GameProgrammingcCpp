#pragma once
#include "SDL/SDL.h"


struct Vector2 {
	float x;
	float y;
};

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

	//パドルの位置
	Vector2 mPaddlePos1;

	//パドルの位置2
	Vector2 mPaddlePos2;
	
	//ボールの位置
	Vector2 mBallPos;

	//SDLが作るウィンドウ
	SDL_Window* mWindow;

	//SDLが作るレンダラー
	SDL_Renderer* mRenderer;

	//デルタタイム
	Uint32 mTicksCount;

	//パドルの移動方向
	int mPaddleDir1;
	
	//パドルの移動方向
	int mPaddleDir2;

	//ballの速度
	Vector2 mBallVel;

	//ゲームの続行を支持する
	bool mlsRunning;
};

