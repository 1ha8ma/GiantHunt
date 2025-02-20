#include<fstream>
#include<math.h>
#include"DxLib.h"
#include"nlohmann/json.hpp"
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

	//�t�@�C���ǂݍ���
	using Json = nlohmann::json;
	Json jsonData;
	std::ifstream ifs("Data/PlayerData.json");
	if (ifs)
	{
		ifs >> jsonData;
	}

	//�ϐ�������
	moveVecV = prevmoveVec;
	moveVecV.y = 0.0f;
	targetLookDirection = prevmoveVec;
	FirstJumpPower = jsonData["JumpPower"];
	MoveSpeedHorizon = jsonData["FallingHorizonMoveSpeed"];
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
/// <param name="playerData">�v���C���[�f�[�^</param>
/// <param name="camera">�J����</param>
/// <param name="objectCollision">�Փ˂����I�u�W�F�N�g</param>
/// <returns>�I��</returns>
bool PlayerJump::Update(UsePlayerData playerData, const Camera& camera, CollisionData objectCollision)
{
	Move(playerData, camera);
	//�A�j���[�V�����Đ�
	PlayAnimationOnce(1.3f);

	return false;
}

/// <summary>
/// �ړ�����
/// </summary>
void PlayerJump::Move(UsePlayerData playerData, Camera camera)
{
	//������
	moveVec = VGet(0.0f, 0.0f, 0.0f);

	//���X�e�B�b�N�̊p�x�����
	float stickX = playerData.stickState.X;
	float stickY = -playerData.stickState.Y;

	//���͂������
	if ((stickX != 0.0f || stickY != 0.0f))
	{
		float stickAngle = atan2(stickY, stickX);

		moveVec.x = cos(stickAngle + -camera.GetangleH());
		moveVec.z = sin(stickAngle + -camera.GetangleH());

		moveVec = VScale(moveVec, MoveSpeedHorizon);
	}

	//����������ǉ�
	moveVec = VAdd(moveVec, moveVecV);

	//�������Z
	moveVec.y += jumpPower;
}