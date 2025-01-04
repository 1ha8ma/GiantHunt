#pragma once
#include"PlayerStateProcessBase.h"

class PlayerRun :public PlayerStateProcessBase
{
public:
	PlayerRun(int modelHandle,VECTOR prevtargetLookDirection);
	~PlayerRun()override;

	//������
	void Initialize()override {};
	//�X�V
	bool Update(VECTOR position,int inputstate, DINPUT_JOYSTATE stickstate,const Camera& camera, VECTOR objectCapsuleStart, VECTOR objectCapsuleEnd)override;

private:
	const float Speed = 20.0f;      //�X�s�[�h

	//�ړ�����
	void Move(int inputstate, DINPUT_JOYSTATE stickstate,Camera camera, VECTOR objectCapsuleStart, VECTOR objectCapsuleEnd);

	bool moveflg;	//�ړ����Ă��邩
};