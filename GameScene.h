#pragma once
#include"SceneBase.h"

class Camera;
class CollisionManager;
class EnemyBase;
class StageBase;
class Player;
class GameUI;

class GameScene :public SceneBase
{
public:
	GameScene(StageBase* stage, EnemyBase* enemy);
	~GameScene()override;

	void Initialize()override;
	SceneBase* Update()override;
	void Draw()override;

private:
	Camera* camera;
	CollisionManager* collisionManager;
	StageBase* stage;
	Player* player;
	EnemyBase* enemy;
	GameUI* ui;

	bool gameOver;
	bool gameClear;
};