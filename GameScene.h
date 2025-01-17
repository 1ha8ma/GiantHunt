#pragma once
#include"SceneBase.h"

class Camera;
class CollisionManager;
class ArmEnemy;
class ArmEnemyStage;
class Player;
class Wall;
class Wood;
class GameUI;

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
	CollisionManager* collisionManager;
	ArmEnemyStage* armEnemyStage;
	Player* player;
	Wall* wall;
	ArmEnemy* armEnemy;
	Wood* wood;
	GameUI* ui;

	bool gameOver;
	bool gameClear;
};