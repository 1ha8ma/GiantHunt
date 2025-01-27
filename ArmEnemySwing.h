#pragma once
#include"ArmEnemyMoveBase.h"

class SoundEffect;

class ArmEnemySwing :public ArmEnemyMoveBase
{
public:
	ArmEnemySwing(int modelHandle,VECTOR prevRotate);
	~ArmEnemySwing()override;

	bool Update(Camera* camera)override;
	void Draw()override {};

private:

	SoundEffect* se;

	bool moveEnd;
};