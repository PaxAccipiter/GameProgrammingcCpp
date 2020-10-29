#pragma once
#include "SDL/SDL.h"

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

	//SDL�����E�B���h�E
	SDL_Window* mWindow;

	//�Q�[���̑��s���x������
	bool mlsRunning;
};

