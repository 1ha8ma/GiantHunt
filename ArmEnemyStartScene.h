#pragma once
#include"SceneBase.h"

class Camera;
class Player;
class ArmEnemy;
class ArmEnemyStage;

class ArmEnemyStartScene:public SceneBase
{
public:
	ArmEnemyStartScene();
	~ArmEnemyStartScene()override;

	void Initialize()override;
	SceneBase* Update()override;
	void Draw()override;

private:
	const int MaxBlackBandAlpha = 255;	//•‘ÑÅ‘å”Z‚³

	//‘¼ƒNƒ‰ƒX
	Camera* camera;
	Player* player;
	ArmEnemy* enemy;
	ArmEnemyStage* stage;

	int flame;
	int blackBandAlpha;		//•‘Ñ‚Ì“§–¾“x
};