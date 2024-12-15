#pragma once
#include"PlayerStateProcessBase.h"

class PlayerJump :public PlayerStateProcessBase
{
public:
	PlayerJump(int modelHandle,VECTOR prevmoveVec);
	~PlayerJump()override;

	//������
	void Initialize()override;
	//�X�V
	bool Update(int inputstate, DINPUT_JOYSTATE stickstate,const Camera& camera)override;

private:
	const float FirstJumpPower = 20.0f;	//�ŏ��̃W�����v��
	const float Gravity = 0.5f;			//�d��
	const float Speed = 10.0f;

	//�ړ�����
	void Move();

	VECTOR moveVecV;	//���������x�N�g��
	float jumpPower;	//�W�����v��
};