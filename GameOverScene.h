#pragma once
#include"SceneBase.h"

class Input;

class GameOverScene :public SceneBase
{
public:
	GameOverScene();
	~GameOverScene()override;

	

	//�V�[�����Ƃ̏�����
	void Initialize() override;
	//�V�[�����Ƃ̍X�V
	SceneBase* Update() override;
	//�V�[�����Ƃ̕`��
	void Draw() override;

private:

	//���N���X
	Input* input;

	int backImage;	//�w�i�摜
	bool canInputB;	//B�{�^�����͉\
};