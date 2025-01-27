#pragma once
#include"ArmEnemyMoveBase.h"

class ArmEnemyIdle :public ArmEnemyMoveBase
{
public:
	ArmEnemyIdle(int modelHandle,VECTOR prevRotate);
	~ArmEnemyIdle()override;

	bool Update(Camera* camera)override;
	void Draw()override {};

private:
	const VECTOR BasicRotate = VGet(-0.4, 0.0f, 0.0f);	//Šî–{‚Ì‰ñ“]—Ê

	//ã‰º—h‚ê‚ÌØ‚è‘Ö‚¦—p
	bool shakingflg;
	int shakingflame;
};