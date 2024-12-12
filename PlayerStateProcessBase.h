#pragma once

class PlayerStateProcessBase
{
public:
	PlayerStateProcessBase(int modelHandle);
	virtual ~PlayerStateProcessBase() {};

	//������
	virtual void Initialize() abstract;
	//�X�V
	virtual PlayerStateProcessBase* Update(const Camera& camera) abstract;

	//NOTE:�m�F�̂��߂����ʂɂ���Ȃ�
	virtual void Draw()abstract;

	//Get,Set
	VECTOR GetmoveVec() { return moveVec; }
	VECTOR GettargetLookDirection() { return targetLookDirection; }

protected:
	//�A�j���[�V�����ԍ�
	enum PlayerAnimationNumber
	{
		Run,
	};
	
	//�A�j���[�V�����Đ�
	void PlayAnimation(float playSpeed,bool stop);
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