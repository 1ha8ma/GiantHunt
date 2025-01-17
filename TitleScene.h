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

	int titleBackImage;	//”wŒi‰æ‘œ
	int canInputB;		//Bƒ{ƒ^ƒ““ü—Í‰Â”\
};