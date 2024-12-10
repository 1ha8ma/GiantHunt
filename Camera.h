#pragma once

class Input;

class Camera
{
public:
	Camera();

	//������
	void Initialize();
	//�X�V
	void Update(VECTOR playerPosition,float lookAngle);

private:
	Input* input;

	VECTOR position;
	VECTOR lookPosition;
	float lookAngleXZ;
	float lookAngleY;
};