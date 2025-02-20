#pragma once
#include"PlayerStateProcessBase.h"

class PlayerFalling :public PlayerStateProcessBase
{
public:
	PlayerFalling(int modelHandle, VECTOR prevtargetLookDirection);
	~PlayerFalling()override;

	void Initialize()override;

	bool Update(UsePlayerData playerData, const Camera& camera, CollisionData objectCollision)override;

private:
	void Move(UsePlayerData playerData,Camera camera);

	float MoveSpeed;			//落ちている時の水平移動速度
};