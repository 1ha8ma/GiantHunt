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
	bool Update(UsePlayerData playerData, const Camera& camera, CollisionData objectCollision)override;

private:
	const float FirstJumpPower = 20.0f;	//最初のジャンプ力

	//移動処理
	void Move();

	VECTOR moveVecV;	//水平方向ベクトル
	float jumpPower;	//ジャンプ力
};