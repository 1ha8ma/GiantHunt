#pragma once
#include"ArmEnemyMoveBase.h"

class SoundEffect;

class ArmEnemySwing :public ArmEnemyMoveBase
{
public:
	ArmEnemySwing(int modelHandle,VECTOR prevRotate);
	~ArmEnemySwing()override;

	bool Update(Camera* camera,VECTOR playerPosition)override;
	void Draw()override {};

private:
	const int JoyPadVibPower = 150;				//�R���g���[���[�U������
	const int JoyPadVibflame = -1;				//�R���g���[���[�U���t���[��(��~�w��������܂�)

	SoundEffect* se;

	bool moveEnd;
};