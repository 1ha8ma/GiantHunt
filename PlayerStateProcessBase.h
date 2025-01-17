#pragma once

class PlayerStateProcessBase
{
public:
	PlayerStateProcessBase(int modelHandle);
	virtual ~PlayerStateProcessBase() {};

	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize() abstract;
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="inputstate">�{�^�����͏��</param>
	/// <param name="stickstate">�X�e�B�b�N���͏��</param>
	/// <param name="camera">�J����</param>
	/// <returns>�X�e�[�g����̃X�e�[�g�ύX�w��</returns>
	virtual bool Update(VECTOR position, float angle, int inputstate, DINPUT_JOYSTATE stickstate, const Camera& camera, CollisionData objectCollision) abstract;

	/// <summary>
	/// �`��(�m�F�p)
	/// </summary>
	virtual void Draw() {};

	//�����Ă���ꏊ
	enum class RunPlaceKind :int
	{
		air,		//��
		ground,		//�n�ʏ�
		capsule,	//�J�v�Z����
	};

	//Get,Set
	VECTOR GetmoveVec() { return moveVec; }
	VECTOR GettargetLookDirection() { return targetLookDirection; }
	void SetRunPlace(RunPlaceKind place) { runPlace = place; }
	//�o��p
	void SetCapsule(VECTOR capsuleStart, VECTOR capsuleEnd, float radius) { playerCapsuleStart = capsuleStart; playerCapsuleEnd = capsuleEnd; playerCapsuleRadius = radius; }

protected:
	//�A�j���[�V�����ԍ�
	enum PlayerAnimationNumber
	{
		Run,			//����
		Jump,			//�W�����v
		NormalAttack,	//�ʏ�U��
		Climb,			//�o��
		Squat,			//���Ⴊ��
	};

	//�t���[���ԍ�
	enum PlayerFrameNumber
	{
		RightArmFrameNumber = 45,	//�E�r�̃t���[���ԍ�
		RightHandFrameNumber = 50,	//�E��̃t���[���ԍ�(���w)
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
	RunPlaceKind runPlace;		//�����Ă���ꏊ�@false:�n�� true:�J�v�Z����

	//�o��p
	VECTOR playerCapsuleStart;
	VECTOR playerCapsuleEnd;
	float playerCapsuleRadius;
};