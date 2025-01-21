#pragma once
#include"SceneBase.h"

class Input;
class BGM;

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
	BGM* bgm;

	int titleBackImage;		//�w�i�摜
	int canInputB;			//B�{�^�����͉\
	int inputOrderAlpha;	//�{�^���w�������x
	bool inputOrderflg;
};