#pragma once
#include"SceneBase.h"

class Input;

class GameOverScene :public SceneBase
{
public:
	GameOverScene();
	~GameOverScene()override;

	

	//シーンごとの初期化
	void Initialize() override;
	//シーンごとの更新
	SceneBase* Update() override;
	//シーンごとの描画
	void Draw() override;

private:

	//他クラス
	Input* input;

	int backImage;	//背景画像
	bool canInputB;	//Bボタン入力可能
};