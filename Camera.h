#pragma once

class Input;

class Camera
{
public:
	Camera();

	//初期化
	void Initialize();
	//更新
	void Update(VECTOR playerPosition,float lookAngle);

private:
	Input* input;

	VECTOR position;
	VECTOR lookPosition;
	float lookAngleXZ;
	float lookAngleY;
};