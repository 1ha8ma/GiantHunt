#pragma once
#include"PlayerStateProcessBase.h"

class PlayerRun :public PlayerStateProcessBase
{
public:
	PlayerRun(int modelHandle,VECTOR prevtargetLookDirection);
	~PlayerRun()override;

	//初期化
	void Initialize()override {};
	//更新
	bool Update(int inputstate, DINPUT_JOYSTATE stickstate,const Camera& camera)override;

private:
	const float Speed = 20.0f;      //スピード

	//移動処理
	void Move(int inputstate, DINPUT_JOYSTATE stickstate,Camera camera);

	bool moveflg;	//移動しているか
};