#pragma once
#include"SceneBase.h"

class Input;

class TitleScene :public SceneBase
{
public:
	TitleScene();
	~TitleScene()override;

	void Initialize()override;
	SceneBase* Update()override;
	void Draw()override;

private:
	Input* input;

	int titleBackImage;	//�w�i�摜
	int canInputB;		//B�{�^�����͉\
};