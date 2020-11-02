#pragma once
#include "Game.h"
#include "Math.h"
#include <vector>

class Actor {
public:
	//Actor�̏�ԊǗ�
	enum State {
		EActive,
		EPaused,
		EDead
	};

	//�R���X�g���N�^�ƃf�X�g���N�^�[
	Actor(class Game* game);
	virtual ~Actor();

	//game����Ăяo�����X�V�֐�(�I�[�o�[���C�h�s��)
	void Update(float deltaTime);
	//Actor�̎��S�R���|�[�l���g���X�V(�I�[�o�[���C�h�s��)
	void UpdateComponents(float deltaTime);
	//Actor�Ǝ��̍X�V����(�I�[�o�[���C�h�\)
	virtual void UpdateActor(float deltaTime);

	//�Q�b�^�[�A�Z�b�^�[(�����o�̒l�̎擾�Ɛݒ�)

	//�R���|�[�l���g�̒ǉ��ƍ폜
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

private:
	//�A�N�^�[�̏��
	State mState;
	
	//���W�ϊ�
	Vector2 mPosition; //�A�N�^�[�̒��S�ʒu
	float mScale; //�A�N�^�[�̃X�P�[��(1.0f��100%)
	float mRotation; //��]�̊p�x(���W�A��)

	//�A�N�^�[�����R���|�[�l���g
	std::vector<class Component*> mComponents;
	class Game* mGame;
};