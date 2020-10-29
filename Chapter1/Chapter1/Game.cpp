#include "Game.h"

bool Game::Initialize() {
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);

	if (sdlResult != 0) {
		SDL_Log("SDLを初期化できません:%s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow(
		"Game Programming in C++(第一章)", //ウィンドウのタイトル
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

	return true;
}

void Game::Shutdown() {
	SDL_DestroyWindow(mWindow);
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

}

void Game::UpdateGame() {

}

void Game::GenerateOutput() {

}