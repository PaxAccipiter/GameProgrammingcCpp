#include "Game.h"

Game::Game()
	:mWindow(nullptr)
	, mlsRunning(true)
{}

bool Game::Initialize() {
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);

	if (sdlResult != 0) {
		SDL_Log("SDL���������ł��܂���:%s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow(
		"Game Programming in C++(Chapter1)", //�E�B���h�E�̃^�C�g��
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

	mRenderer = SDL_CreateRenderer(
		mWindow, //�쐬���郌���_���[�̕`��ΏۂƂȂ�E�B���h�E
		-1, //�f�t�H���g��-1�E�B���h�E����������ꍇ�ɗp����B
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	//���s������nullptr��Ԃ�
	if (!mRenderer) {
		SDL_Log("�����_���[�̍쐬�Ɏ��s���܂���:%s", SDL_GetError());
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

	//�L���[�ɃC�x���g������ΌJ��ւ���
	while (SDL_PollEvent(&event)) {

		switch (event.type) {
			//�����Ŋe��̃C�x���g����������B

			//���[�U�[���u�~�v���N���b�N�����Ƃ��ɃQ�[�����[�v���~�߂�B
		case SDL_QUIT:
			mlsRunning = false;
			break;
		}
	}

	//�L�[�{�[�h�̏�Ԃ̔z����擾����֐�
	const Uint8* state = SDL_GetKeyboardState(NULL);

	//[ESC]�L�[�������ꂽ�����Q�[�����[�v���I����
	if (state[SDL_SCANCODE_ESCAPE]) {
		mlsRunning = false;
	}
}

void Game::UpdateGame() {

}

void Game::GenerateOutput() {

}