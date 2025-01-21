#pragma once
#include"PlayerStateProcessBase.h"

class PlayerFallDown :public PlayerStateProcessBase
{
public:
	PlayerFallDown(int modelHandle);
	~PlayerFallDown()override;

	void Initialize()override {};
	void UpdateGameOver()override;

private:
	bool animationEnd;
};