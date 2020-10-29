#include "Game.h"

Game::Game()
	:mWindow(nullptr)
	, mlsRunning(true)
{}

bool Game::Initialize() {
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);

	if (sdlResult != 0) {
		SDL_Log("SDLを初期化できません:%s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow(
		"Game Programming in C++(Chapter1)", //ウィンドウのタイトル
		100, //ウィンドウのx座標
		100, //ウィンドウのy座標
		1024, //ウィンドウの幅(width)
		768, //ウィンドウの高さ(height)
		0 //フラグ(設定しないときは0)
	);

	if (!mWindow) {
		SDL_Log("ウィンドウの作成に失敗しました:%s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(
		mWindow, //作成するレンダラーの描画対象となるウィンドウ
		-1, //デフォルトで-1ウィンドウが複数ある場合に用いる。
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	//失敗したらnullptrを返す
	if (!mRenderer) {
		SDL_Log("レンダラーの作成に失敗しました:%s", SDL_GetError());
		return false;
	}

	return true;
}

void Game::Shutdown() {
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

void Game::RunLoop() {

	while (mlsRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput() {
	SDL_Event event;

	//キューにイベントがあれば繰り替えす
	while (SDL_PollEvent(&event)) {

		switch (event.type) {
			//ここで各種のイベントを処理する。

			//ユーザーが「×」をクリックしたときにゲームループを止める。
		case SDL_QUIT:
			mlsRunning = false;
			break;
		}
	}

	//キーボードの状態の配列を取得する関数
	const Uint8* state = SDL_GetKeyboardState(NULL);

	//[ESC]キーが押された時もゲームループを終える
	if (state[SDL_SCANCODE_ESCAPE]) {
		mlsRunning = false;
	}
}

void Game::UpdateGame() {

}

void Game::GenerateOutput() {

}