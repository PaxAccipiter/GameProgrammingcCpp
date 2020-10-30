#pragma once
#include "SDL/SDL.h"


struct Vector2 {
	float x;
	float y;
};

class Game {
public:
	Game();

	//�Q�[��������������
	bool Initialize();

	//�Q�[���I�[�o�[�܂ŃQ�[�����[�v�����s����
	void RunLoop();

	//�Q�[�����V���b�g�_�E������
	void Shutdown();

private:

	//���͏���
	void ProcessInput();

	//�t���[���A�b�v�f�[�g
	void UpdateGame();

	//�o�͐���
	void GenerateOutput();

	//�p�h���̈ʒu
	Vector2 mPaddlePos;
	
	//�{�[���̈ʒu
	Vector2 mBallPos;

	//SDL�����E�B���h�E
	SDL_Window* mWindow;

	//SDL����郌���_���[
	SDL_Renderer* mRenderer;

	//�Q�[���̑��s���x������
	bool mlsRunning;
};

