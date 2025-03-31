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
	const float CameraShakingPower = 3.0;		//カメラ揺れ強さ
	const int CameraShakingChangeDirflame = 10;	//カメラ上下揺れ変更フレーム
	const int CameraShakinPlayflame = 50;		//カメラ揺れ再生フレーム
	const int JoyPadVibPower = 300;				//コントローラー振動強さ
	const int JoyPadVibflame = 1200;				//コントローラー振動フレーム
};