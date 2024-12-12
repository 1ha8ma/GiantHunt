#pragma once
#include"PlayerStateProcessBase.h"

class Input;

class PlayerRun :public PlayerStateProcessBase
{
public:
	PlayerRun(int modelHandle);
	~PlayerRun()override;

	void Initialize()override {};
	PlayerStateProcessBase* Update(const Camera& camera)override;

	void Draw();

private:
	const float Speed = 20.0f;      //スピード

	void Move(Camera camera);

	Input* input;

	bool moveflg;
};