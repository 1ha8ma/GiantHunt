#pragma once
#include"StageBase.h"

class CollisionManager;
struct CollisionData;
class Wood;
class Wall;
class BGM;

class ArmEnemyStage :public StageBase
{
public:
	ArmEnemyStage();
	~ArmEnemyStage()override;

	void Update()override;
	void Draw()override;
private:
	const float StageLeft = -2450.0f;
	const float StageRight = 7150.0f;
	const float StageFront = 4530.0f;
	const float StageBack = -4770.0f;

	CollisionManager* collisionManager;
	CollisionData collisionData;
	Wood* wood;
	Wall* wall;
	BGM* bgm;
};