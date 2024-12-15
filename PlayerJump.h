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
	bool Update(int inputstate, DINPUT_JOYSTATE stickstate,const Camera& camera)override;

private:
	const float FirstJumpPower = 20.0f;	//最初のジャンプ力
	const float Gravity = 0.5f;			//重力
	const float Speed = 10.0f;

	//移動処理
	void Move();

	VECTOR moveVecV;	//水平方向ベクトル
	float jumpPower;	//ジャンプ力
};