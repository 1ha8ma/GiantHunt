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

	int titleBackImage;		//背景画像
	int canInputB;			//Bボタン入力可能
	int inputOrderAlpha;	//ボタン指示透明度
	bool inputOrderflg;
};