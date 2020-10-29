#include "Game.h"

bool Game::Initialize() {
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);

	if (sdlResult != 0) {
		SDL_Log("SDL���������ł��܂���:%s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow(
		"Game Programming in C++(����)", //�E�B���h�E�̃^�C�g��
		100, //�E�B���h�E��x���W
		100, //�E�B���h�E��y���W
		1024, //�E�B���h�E�̕�(width)
		768, //�E�B���h�E�̍���(height)
		0 //�t���O(�ݒ肵�Ȃ��Ƃ���0)
	);

	if (!mWindow) {
		SDL_Log("�E�B���h�E�̍쐬�Ɏ��s���܂���:%s", SDL_GetError());
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