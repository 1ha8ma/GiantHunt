#include<math.h>
#include"DxLib.h"
#include"Input.h"
#include"Camera.h"
#include"PlayerRun.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerRun::PlayerRun(int modelHandle):PlayerStateProcessBase(modelHandle)
{
	//�A�j���[�V�����A�^�b�`
	nowPlayAnim = MV1AttachAnim(modelHandle, PlayerAnimationNumber::Run);
	//�A�j���[�V�����̑��Đ����Ԃ����
	animTotalTime = MV1GetAnimTotalTime(modelHandle, nowPlayAnim);

	input = new Input();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerRun::~PlayerRun()
{
	DetachAnimation(nowPlayAnim);
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="cameralookAngleXZ">�J�����̕��ʊp�x</param>
/// <returns>���̃X�e�[�g</returns>
PlayerStateProcessBase* PlayerRun::Update(const Camera& camera)
{
	Move(camera);
	PlayAnimation(0.4f,!moveflg);

	return this;
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="cameralookAngleXZ"></param>
void PlayerRun::Move(Camera camera)
{
	moveVec = VGet(0, 0, 0);
	moveflg = false;

	//���X�e�B�b�N�̊p�x�����
	float inputX = input->GetStickInput().X;
	float inputY = -input->GetStickInput().Y;

	//���͂������
	if (!inputX == 0 || !inputY == 0)
	{
		float ang = atan2(inputY, inputX);

		moveVec.x = cos(ang + -camera.GetangleH());
		moveVec.z = sin(ang + -camera.GetangleH());

		moveflg = true;
		targetLookDirection = moveVec;
	}

	//�ړ���
	if (VSize(moveVec) > 0)
	{
		moveVec = VNorm(moveVec);
	}
	moveVec = VScale(moveVec, Speed);
}

void PlayerRun::Draw()
{
	input->Draw();
}