#pragma once
#include"PlayerStateProcessBase.h"
#include"Calculation.h"

class PlayerClimb :public PlayerStateProcessBase
{
public:
	PlayerClimb(int modelHandle,VECTOR lookDir);
	~PlayerClimb()override;

	//������
	void Initialize()override;
	//�X�V
	bool Update(UsePlayerData playerData, const Camera& camera,CollisionData objectCollision)override;

private:
	const float RotateSpeed = 0.01f;	//��]���x

	//���ړ�����
	void MoveCapsule(UsePlayerData playerData, Camera camera, CollisionData objectCollision);
	//
	void MoveMesh(UsePlayerData playerData, Camera camera,CollisionData objectData);

	//�p�x�v�Z
	void CalculationAngle(VECTOR playerPosition, VECTOR objectPosition);

	//���N���X
	Calculation* calculation;

	//�ϐ�
	float Speed;			//�ړ����x
	bool stopanimflg;		//�A�j���[�V������~�t���O
	float rotateY;			//���ɒ����Ă��鎞
	float rotateH;			
};