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
	const int JoyPadVibPower = 150;				//コントローラー振動強さ
	const int JoyPadVibflame = -1;				//コントローラー振動フレーム(停止指示が来るまで)

	SoundEffect* se;

	bool moveEnd;
};