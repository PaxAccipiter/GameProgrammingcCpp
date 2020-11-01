#include "Game.h"

const int thickness = 15;
const float paddle_H = 150.0f;

Game::Game()
	:mWindow(nullptr)
	,mRenderer(nullptr)
	,mTicksCount(0)
	,mPaddleDir1(0)
	,mPaddleDir2(0)
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

	mPaddlePos1.x = 10.0f;
	mPaddlePos1.y = 768.0f / 2.0f;
	mPaddlePos2.x = 1014.0f;
	mPaddlePos2.y = 768.0f / 2.0f;
	mBallPos.x = 1024.0f / 2.0f;
	mBallPos.y = 768.0f / 2.0f;

	mBallVel.x = 150.0f;
	mBallVel.y = 200.0f;

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

	//paddle�̕����̍X�V�BW��S�����������瓮���Ȃ��悤�ɂȂ��Ă���B
	mPaddleDir1 = 0;

	if (state[SDL_SCANCODE_W]) {
		mPaddleDir1 -= 1;
	}
	else if (state[SDL_SCANCODE_S]) {
		mPaddleDir1 += 1;
	}

	mPaddleDir2 = 0;
	if (state[SDL_SCANCODE_I]) {
		mPaddleDir2 -= 1;
	}
	else if (state[SDL_SCANCODE_K]) {
		mPaddleDir2 += 1;
	}

}

void Game::UpdateGame() {

	while(!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	//deltatime�͑O�̃t���[���Ƃ̎����̍���b�ɕϊ������l�BTicks��ms�P�ʂ�����s�P�ʂɒ������߂�1000�Ŋ����Ă���B
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	if (deltaTime < 0.05f)
	{
		deltaTime = 0.05f;
	}

	//�������X�V(���̃t���[���̂��߂�)
	mTicksCount = SDL_GetTicks();

	//ToDo: �Q�[�����[���h�̃I�u�W�F�N�g�̍X�V���s���B
	if (mPaddleDir1 != 0) {
		mPaddlePos1.y += mPaddleDir1 * 300.0f * deltaTime; //300.0fpixel/s�Ńp�h���͓����B

		//�p�h�����O�ɏo�Ȃ��悤�ɂ���B
		if (mPaddlePos1.y < (paddle_H / 2.0f + thickness)) {//�p�h���̒��S�ʒu���p�h���̍����ƕǂ����킹�����̂�����ɂ���ƃ_��
			mPaddlePos1.y = paddle_H / 2.0f + thickness;
		}
		else if (mPaddlePos1.y > 768.0f - (paddle_H / 2.0f + thickness)) {
			mPaddlePos1.y = 768.0f - (paddle_H / 2.0f + thickness);
		}
	}

	if (mPaddleDir2 != 0) {
		mPaddlePos2.y += mPaddleDir2 * 300.0f * deltaTime;

		if (mPaddlePos2.y > 768.0f - (paddle_H / 2.0f + thickness)) {
			mPaddlePos2.y = 768.0f - (paddle_H / 2.0f + thickness);
		}
		else if (mPaddlePos2.y < paddle_H / 2.0f + thickness) {
			mPaddlePos2.y = paddle_H / 2.0f + thickness;
		}
	}

	//Ball�̈ʒu�X�V
	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	//Ball�̏Փ˔���
	float diff1 = mPaddlePos1.y - mBallPos.y;
	float diff2 = mPaddlePos2.y - mBallPos.y;
	
	//�ǂƂ̏Փ�
	//���
	if (mBallPos.y < thickness * 1.5f && mBallVel.y < 0.0f) {
		mBallVel.y = -mBallVel.y;
	}
	//�E��
	//if (mBallPos.x > 1024.0f - (thickness * 1.5f) && mBallVel.x > 0.0f) {
	//	mBallVel.x = -mBallVel.x;
	//}
	//����
	if (mBallPos.y > 768.0f - (thickness * 1.5f) && mBallVel.y > 0.0f) {
		mBallVel.y = -mBallVel.y;
	}
	//�p�h����
	diff1 = diff1 < 0.0f ? -diff1 : diff1;
	if (diff1 < paddle_H / 2.0f && mPaddlePos1.x + thickness / 2.0f < mBallPos.x && mBallPos.x < mPaddlePos1.x + thickness && mBallVel.x < 0.0f) {
		mBallVel.x = -mBallVel.x;
	}
	//2p�p�h����
	diff2 = diff2 < 0.0f ? -diff2 : diff2;
	if (diff2 < paddle_H / 2.0f && mPaddlePos2.x - thickness < mBallPos.x && mBallPos.x < mPaddlePos2.x - thickness / 2.0f && mBallVel.x > 0.0f) {
		mBallVel.x = -mBallVel.x;
	}
	//�p�h���㉺

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
	//wall.x = 1024 - thickness;
	//wall.y = 0;
	//wall.w = thickness;
	//wall.h = 1024;
	//SDL_RenderFillRect(mRenderer, &wall);

	//Paddle
	SDL_Rect paddle1{
		static_cast<int>(mPaddlePos1.x - thickness / 2), //���ꌳ�̂́A�����ĂȂ����ǁA�������ق����ǂ������B
		static_cast<int>(mPaddlePos1.y - paddle_H / 2),
		thickness,
		paddle_H
	};
	SDL_RenderFillRect(mRenderer, &paddle1);

	SDL_Rect paddle2{
		static_cast<int>(mPaddlePos2.x - thickness / 2),
		static_cast<int>(mPaddlePos2.y - thickness / 2),
		thickness,
		paddle_H
	};
	SDL_RenderFillRect(mRenderer, &paddle2);

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

	if ((mBallPos.x < 0.0f) | (mBallPos.x > 1024.0f)) {
		mlsRunning = false;
	}
}