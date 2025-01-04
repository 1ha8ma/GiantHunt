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
	bool Update(VECTOR position,int inputstate, DINPUT_JOYSTATE stickstate, const Camera& camera, VECTOR objectCapsuleStart, VECTOR objectCapsuleEnd)override;

private:
	const float RotateSpeed = 0.01;	//��]���x
	const float Speed = 5;			//�ړ����x

	//�ړ�����
	void Move(VECTOR position,DINPUT_JOYSTATE stickstate, Camera camera, VECTOR objectCapsuleStart, VECTOR objectCapsuleEnd);

	Calculation* calculation;

	//�o���Ă���I�u�W�F�N�g�̃J�v�Z��
	VECTOR climbCapStart;
	VECTOR climbCapEnd;

	bool stopanimflg;		//�A�j���[�V������~�t���O
};