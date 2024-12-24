#pragma once
#include"PlayerStateProcessBase.h"

class PlayerClimb :public PlayerStateProcessBase
{
public:
	PlayerClimb(int modelHandle,VECTOR lookDir);
	~PlayerClimb()override;

	//������
	void Initialize()override;
	//�X�V
	bool Update(int inputstate, DINPUT_JOYSTATE stickstate, const Camera& camera, VECTOR objectCapsuleStart, VECTOR objectCapsuleEnd)override;

private:
	//�ړ�����
	void Move(DINPUT_JOYSTATE stickstate, Camera camera);

	//�o���Ă���I�u�W�F�N�g�̃J�v�Z��
	VECTOR climbCapStart;
	VECTOR climbCapEnd;

	bool moveflg;		//�ړ���
};