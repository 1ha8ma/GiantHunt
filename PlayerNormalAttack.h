#pragma once
#include"PlayerStateProcessBase.h"

class PlayerNormalAttack:public PlayerStateProcessBase
{
public:
	PlayerNormalAttack(int modelHandle,VECTOR prevtargetLookDirection);
	~PlayerNormalAttack()override;

	//������
	void Initialize()override;
	//�X�V
	bool Update(int inputstate, DINPUT_JOYSTATE stickstate, const Camera& camera)override;

private:
	bool stateChangeflg;	//�X�e�[�g�ύX�t���O
	bool animEndflg;		//�A�j���[�V�����I��
};