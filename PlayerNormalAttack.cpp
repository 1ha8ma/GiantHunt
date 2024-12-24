#include"DxLib.h"
#include"Camera.h"
#include"PlayerNormalAttack.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="modelHandle">�ʏ�U��</param>
PlayerNormalAttack::PlayerNormalAttack(int modelHandle, VECTOR prevtargetLookDirection) :PlayerStateProcessBase(modelHandle)
{
	//�A�j���[�V�����A�^�b�`
	nowPlayAnim = MV1AttachAnim(modelHandle, PlayerAnimationNumber::NormalAttack);
	//�A�j���[�V�����̑��Đ����Ԃ����
	animTotalTime = MV1GetAnimTotalTime(modelHandle, nowPlayAnim);

	//�ړ��x�N�g��������
	moveVec = VGet(0.0f, 0.0f, 0.0f);
	//�ڕW�̕�����O�̕����ɂ���
	targetLookDirection = prevtargetLookDirection;

	//private�ϐ�������
	stateChangeflg = false;
	animEndflg = false;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerNormalAttack::~PlayerNormalAttack()
{
	DetachAnimation(nowPlayAnim);
}

/// <summary>
/// ������
/// </summary>
void PlayerNormalAttack::Initialize()
{

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="inputstate">���͏��</param>
/// <param name="stickstate">�X�e�B�b�N���͏��</param>
/// <param name="camera">�J����</param>
bool PlayerNormalAttack::Update(int inputstate, DINPUT_JOYSTATE stickstate, const Camera& camera, VECTOR objectCapsuleStart, VECTOR objectCapsuleEnd)
{
	if (!animEndflg)//�Đ�
	{
		animEndflg = PlayAnimationOnce(0.7f);
	}
	else//�t�Đ�
	{
		stateChangeflg = ReversePlaybackAnimation(0.4f, 0.6);
	}

	//�ړ��͂��Ȃ�
	moveVec = VGet(0.0f, 0.0f, 0.0f);

	return stateChangeflg;
}