#pragma once
#include"ArmEnemyMoveBase.h"

class ArmEnemyIdle :public ArmEnemyMoveBase
{
public:
	ArmEnemyIdle(int modelHandle,VECTOR prevRotate);
	~ArmEnemyIdle()override;

	bool Update(Camera* camera,VECTOR playerPosition)override;
	void Draw()override {};

private:
	const VECTOR BasicRotate = VGet(-0.4, 0.0f, 0.0f);	//基本の回転量

	//上下揺れの切り替え用
	bool shakingflg;
	int shakingflame;
};