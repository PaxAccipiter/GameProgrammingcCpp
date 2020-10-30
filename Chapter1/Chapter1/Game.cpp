#include "Game.h"

const int thickness = 15;
const float paddle_H = 100.0f;

Game::Game()
	:mWindow(nullptr)
	,mRenderer(nullptr)
	,mlsRunning(true)
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

	mPaddlePos.x = 10.0f;
	mPaddlePos.y = 768.0f / 2.0f;
	mBallPos.x = 1024.0f / 2.0f;
	mBallPos.y = 768.0f / 2.0f;


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
	SDL_SetRenderDrawColor(
		mRenderer,
		0, //R
		0, //G
		255, //B
		255 //A : �����x
		);

	//�ݒ肵���F�Ńo�b�N�o�b�t�@��h��Ԃ��B
	SDL_RenderClear(mRenderer);

	//�s�������F�̒����`�������B
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

	SDL_Rect wall{
		0, //�����`�̍������x(x,y�̓E�B���h�E�̍��������E��x�������A����y��������ƍl����B)
		0, //�����`�̍������y
		1024, //�����`�̕�
		thickness //�����`�̍���
	};

	SDL_RenderFillRect(mRenderer, &wall);

	//���̕ǒǉ�
	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);

	//�E�̕ǒǉ�
	wall.x = 1024 - thickness;
	wall.y = 0;
	wall.w = thickness;
	wall.h = 1024;
	SDL_RenderFillRect(mRenderer, &wall);

	//Paddle
	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x - thickness / 2), //���ꌳ�̂́A�����ĂȂ����ǁA�������ق����ǂ������B
		static_cast<int>(mPaddlePos.y - paddle_H / 2),
		thickness,
		paddle_H
	};
	SDL_RenderFillRect(mRenderer, &paddle);

	//Ball
	SDL_Rect ball{
		static_cast<int>(mBallPos.x - thickness / 2),
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);
	//�t�����g�o�b�t�@�ƃo�b�N�o�b�t�@�̓���ւ�����ŕ`�悷�邱�ƂɂȂ�B
	SDL_RenderPresent(mRenderer);

}