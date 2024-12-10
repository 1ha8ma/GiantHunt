#pragma once
#include"SceneBase.h"

class Camera;
class ArmEnemyStage;
class Player;

class GameScene :public SceneBase
{
public:
	GameScene();
	~GameScene()override;

	void Initialize()override;
	SceneBase* Update()override;
	void Draw()override;

private:
	Camera* camera;
	ArmEnemyStage* armEnemyStage;
	Player* player;
};