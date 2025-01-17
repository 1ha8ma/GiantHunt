#include<math.h>
#include"DxLib.h"
#include"CollisionData.h"
#include"Camera.h"
#include"PlayerJump.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="modelHandle">���f���n���h��</param>
PlayerJump::PlayerJump(int modelHandle,VECTOR prevmoveVec) :PlayerStateProcessBase(modelHandle)
{
	//�A�j���[�V�����A�^�b�`
	nowPlayAnim = MV1AttachAnim(modelHandle, PlayerAnimationNumber::Jump);
	//�A�j���[�V�����̑��Đ����Ԃ����
	animTotalTime = MV1GetAnimTotalTime(modelHandle, nowPlayAnim);

	//���������̃x�N�g����O�܂ł̈ړ��x�N�g���̌����ɂ���
	moveVecV = prevmoveVec;
	moveVecV.y = 0.0f;

	jumpPower = FirstJumpPower;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerJump::~PlayerJump()
{
	DetachAnimation(nowPlayAnim);
}

/// <summary>
/// ������
/// </summary>
void PlayerJump::Initialize()
{

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="position">�|�W�V����</param>
/// <param name="angle">����</param>
/// <param name="inputstate">���͏��</param>
/// <param name="stickstate">�X�e�B�b�N���͏��</param>
/// <param name="camera">�J����</param>
/// <param name="objectCollision">�Փ˃I�u�W�F�N�g���</param>
/// <returns>�X�e�[�g�ύX</returns>
bool PlayerJump::Update(VECTOR position, float angle, int inputstate, DINPUT_JOYSTATE stickstate, const Camera& camera, CollisionData objectCollision)
{
	Move();
	//�A�j���[�V�����Đ�
	PlayAnimationOnce(1.3f);

	return false;
}

/// <summary>
/// �ړ�����
/// </summary>
void PlayerJump::Move()
{
	//������
	moveVec = VGet(0.0f, 0.0f, 0.0f);

	//����������ǉ�
	moveVec = VAdd(moveVec, moveVecV);

	//�������Z
	moveVec.y += jumpPower;

	targetLookDirection = moveVec;
}