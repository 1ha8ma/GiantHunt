#pragma once
#include"ArmEnemyMoveBase.h"

class ArmEnemySwing :public ArmEnemyMoveBase
{
public:
	ArmEnemySwing(int modelHandle,float modelScale,VECTOR prevRotate);
	~ArmEnemySwing()override;

	bool Update(Camera* camera)override;
	void Draw()override {};

private:
	const VECTOR BasicRotate = VGet(0.0f, 0.0f, 0.0f);	//Šî–{‚Ì‰ñ“]—Ê

	bool moveEnd;
};