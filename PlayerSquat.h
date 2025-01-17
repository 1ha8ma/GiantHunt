#pragma once
#include"PlayerStateProcessBase.h"

class PlayerSquat :public PlayerStateProcessBase 
{
public:
	PlayerSquat(int modelHandle,VECTOR prevtargetLookDirection);
	~PlayerSquat()override;

	void Initialize()override {};
	bool Update(VECTOR position, float angle, int inputstate, DINPUT_JOYSTATE stickstate, const Camera& camera, CollisionData objectCollision) override;

private:
	bool changeState;		//èÛë‘ïœçX
};