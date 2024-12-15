#pragma once

class PlayerStateProcessBase
{
public:
	PlayerStateProcessBase(int modelHandle);
	virtual ~PlayerStateProcessBase() {};

	//������
	virtual void Initialize() abstract;
	//�X�V
	virtual bool Update(int inputstate, DINPUT_JOYSTATE stickstate,const Camera& camera) abstract;

	//Get,Set
	VECTOR GetmoveVec() { return moveVec; }
	VECTOR GettargetLookDirection() { return targetLookDirection; }

protected:
	//�A�j���[�V�����ԍ�
	enum PlayerAnimationNumber
	{
		Run,			//����
		Jump,			//�W�����v
		NormalAttack,	//�ʏ�U��
		Climb,			//�o��
	};
	
	//�A�j���[�V�����Đ�
	void PlayAnimation(float playSpeed,bool stop);
	//�A�j���[�V�����Đ�(1��̂�)
	bool PlayAnimationOnce(float playSpeed);
	//�A�j���[�V�����t�Đ�
	bool ReversePlaybackAnimation(float playSpeed, float backPoint);
	//�A�j���[�V�����̏I��
	void DetachAnimation(int attachIndex);

	//���f���E�A�j���[�V����
	int modelHandle;			//���f���n���h��
	int nowPlayAnim;			//�Đ����̃A�j���[�V����
	float animTotalTime;		//�A�j���[�V�����̑��Đ�����
	float nowAnimPlayTime;		//���݂̃A�j���[�V�����Đ�����

	//�ړ�
	VECTOR moveVec;				//�ړ��x�N�g��
	VECTOR targetLookDirection;	//�ڕW�p�x
};