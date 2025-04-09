#pragma once
#include"PlayerStateProcessBase.h"

class PlayerJump :public PlayerStateProcessBase
{
public:
	PlayerJump(int modelHandle,VECTOR prevmoveVec,VECTOR prevLookDir);
	~PlayerJump()override;

	//������
	void Initialize()override;
	//�X�V
	bool Update(UsePlayerData playerData, const Camera& camera, CollisionData objectCollision)override;

private:

	//�ړ�����
	void Move(UsePlayerData playerData, Camera camera);

	VECTOR moveVecV;				//���������x�N�g��
	float FirstJumpPower;			//�ŏ��̃W�����v��
	float MoveSpeedHorizon;			//���s�ړ����x
	float jumpPower;				//�W�����v��
};