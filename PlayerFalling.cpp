#include"DxLib.h"
#include"CollisionData.h"
#include"Camera.h"
#include"PlayerFalling.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="modelHandle">���f���n���h��</param>
/// <param name="prevtargetLookDirection">�O�����Ă�������</param>
PlayerFalling::PlayerFalling(int modelHandle, VECTOR prevtargetLookDirection) :PlayerStateProcessBase(modelHandle)
{
	//�A�j���[�V�����A�^�b�`
	nowPlayAnim = MV1AttachAnim(modelHandle, PlayerAnimationNumber::Falling);
	//�A�j���[�V�����̑��Đ����Ԃ����
	animTotalTime = MV1GetAnimTotalTime(modelHandle, nowPlayAnim);

	//�ϐ�������
	targetLookDirection = prevtargetLookDirection;
	moveVec = VGet(0, 0, 0);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerFalling::~PlayerFalling()
{
	DetachAnimation(nowPlayAnim);
}

/// <summary>
/// ������
/// </summary>
void PlayerFalling::Initialize()
{

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="playerData">�v���C���[�f�[�^</param>
/// <param name="camera">�J����</param>
/// <param name="objectCollision">�Փ˂����I�u�W�F�N�g</param>
/// <returns>�I��</returns>
bool PlayerFalling::Update(UsePlayerData playerData, const Camera& camera, CollisionData objectCollision)
{
	PlayAnimation(0.2f, false);
	return false;
}