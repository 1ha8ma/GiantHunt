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
	const int MaxBlackBandAlpha = 255;	//���эő�Z��

	//���N���X
	Camera* camera;
	Player* player;
	ArmEnemy* enemy;
	ArmEnemyStage* stage;

	int flame;
	int blackBandAlpha;		//���т̓����x
};