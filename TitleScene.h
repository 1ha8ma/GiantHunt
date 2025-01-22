#pragma once
#include"SceneBase.h"

class Input;
class BGM;
class SoundEffect;

class TitleScene :public SceneBase
{
public:
	TitleScene();
	~TitleScene()override;

	void Initialize()override;
	SceneBase* Update()override;
	void Draw()override;

private:
	//タイトル状態
	enum class State :int
	{
		Title,		//タイトル名と入力指示
		Select,		//シーンセレクト
	};

	//カーソルのさしている場所
	enum class Cursor :int
	{
		ArmEnemyStage,	//腕の敵ステージ
		CheckRanking,	//ランキング確認
	};
	
	//他クラス
	Input* input;
	BGM* bgm;
	SoundEffect* se;

	State state;				//タイトルの状態
	int cursor;					//カーソルのさしている場所
	int titleBackImage;			//背景画像
	int canInputB;				//Bボタン入力可能
	int inputOrderAlpha;		//ボタン指示透明度
	bool inputOrderflg;			//入力指示の透明度
	float trianglePosY;			//三角形カーソルのポジション
	bool canInputStick;			//スティック入力可能
};