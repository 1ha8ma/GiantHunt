#pragma once
#include"PlayerStateProcessBase.h"

class PlayerJump :public PlayerStateProcessBase
{
public:
	PlayerJump(int modelHandle,VECTOR prevmoveVec);
	~PlayerJump()override;

	//初期化
	void Initialize()override;
	//更新
	bool Update(VECTOR position,int inputstate, DINPUT_JOYSTATE stickstate,const Camera& camera, VECTOR objectCapsuleStart, VECTOR objectCapsuleEnd)override;

private:
	const float FirstJumpPower = 20.0f;	//最初のジャンプ力

	//移動処理
	void Move();

	VECTOR moveVecV;	//水平方向ベクトル
	float jumpPower;	//ジャンプ力
};