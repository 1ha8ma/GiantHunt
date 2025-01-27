#pragma once
#include"SceneBase.h"

class Camera;
class Player;
class Enemy2;
class ArmEnemyStage;

class Enemy2StartScene :public SceneBase
{
public:
	Enemy2StartScene();
	~Enemy2StartScene()override;

	void Initialize()override;
	SceneBase* Update()override;
	void Draw()override;

private:
	const int MaxBlackBandAlpha = 255;	//黒帯最大濃さ

	//他クラス
	Camera* camera;
	Player* player;
	Enemy2* enemy;
	ArmEnemyStage* stage;

	int flame;					//開始からのフレーム数
	int blackBandAlpha;			//黒帯の透明度
	VECTOR cameraPosition;		//カメラポジション
	VECTOR cameraLookPosition;	//カメラ注視点
};