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
};