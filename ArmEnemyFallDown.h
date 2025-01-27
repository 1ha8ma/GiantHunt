#pragma once
#include"ArmEnemyMoveBase.h"

class ArmEnemyFallDown :public ArmEnemyMoveBase
{
public:
	ArmEnemyFallDown(int modelHandle);
	~ArmEnemyFallDown()override;

	bool UpdateFallDown(Camera* camera)override;
	void Draw()override;

private:
};