#pragma once
#include"SceneBase.h"

class Input;
class BGM;
class StageBase;
class EnemyBase;
class Camera;
class Player;

class GameClearScene :public SceneBase
{
public:
	GameClearScene(StageBase* stage, EnemyBase* enemy, Camera* camera, Player* player, bool rankIn,int time);
	~GameClearScene()override;

	void Initialize()override;
	SceneBase* Update()override;
	void Draw()override;

private:
	Input* input;
	BGM* bgm;
	StageBase* stage;
	EnemyBase* enemy;
	Camera* camera;
	Player* player;

	bool canInputB;			//B連続入力防止
	int blackBandAlpha;		//黒帯の透明度
	bool enemyMoveEnd;		//敵の動き終了
	bool rankIn;			//ランクイン
	int clearTextBackImage;	//テキスト背景
	int time;				//その回のタイム
};