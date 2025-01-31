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
	bool Update(UsePlayerData playerData, const Camera& camera, CollisionData objectCollision)override;

private:
	const float FirstJumpPower = 20.0f;	//�ŏ��̃W�����v��

	//�ړ�����
	void Move();

	VECTOR moveVecV;	//���������x�N�g��
	float jumpPower;	//�W�����v��
};