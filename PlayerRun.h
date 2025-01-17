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
	bool Update(VECTOR position, float angle, int inputstate, DINPUT_JOYSTATE stickstate, const Camera& camera, CollisionData objectCollision)override;

private:
	const float Speed = 20.0f;      //スピード

	//移動処理
	void Move(int inputstate, DINPUT_JOYSTATE stickstate,Camera camera, VECTOR objectCapsuleStart, VECTOR objectCapsuleEnd);

	bool moveflg;	//移動しているか
};