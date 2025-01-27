#pragma once
#include"ArmEnemyMoveBase.h"

class ArmEnemyHandUp :public ArmEnemyMoveBase
{
public:
	ArmEnemyHandUp(int modelHandle,VECTOR prevRotate);
	~ArmEnemyHandUp()override;

	bool Update(Camera* camera)override;
	void Draw()override { ; }

private:
};