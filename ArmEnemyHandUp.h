#pragma once
#include"ArmEnemyMoveBase.h"

class ArmEnemyHandUp :public ArmEnemyMoveBase
{
public:
	ArmEnemyHandUp(int modelHandle,VECTOR prevRotate);
	~ArmEnemyHandUp()override;

	bool Update(Camera* camera,VECTOR playerPosition)override;
	void Draw()override { ; }

private:
};