#include<math.h>
#include"DxLib.h"
#include"Camera.h"
#include"Input.h"
#include"PlayerClimb.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="modelHandle">���f���n���h��</param>
PlayerClimb::PlayerClimb(int modelHandle,VECTOR lookDir) :PlayerStateProcessBase(modelHandle)
{
	//�A�j���[�V�����A�^�b�`
	nowPlayAnim = MV1AttachAnim(modelHandle, PlayerAnimationNumber::Climb);
	//�A�j���[�V�����̑��Đ����Ԃ����
	animTotalTime = MV1GetAnimTotalTime(modelHandle, nowPlayAnim);
	animTotalTime *= 2;

	//private�ϐ�������
	moveflg = false;

	targetLookDirection = lookDir;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerClimb::~PlayerClimb()
{
	DetachAnimation(nowPlayAnim);
}

/// <summary>
/// ������
/// </summary>
void PlayerClimb::Initialize()
{

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="inputstate">���͏��</param>
/// <param name="stickstate">�X�e�B�b�N���͏��</param>
/// <param name="camera">�J����</param>
/// <returns>�X�e�[�g�ύX�w��</returns>
bool PlayerClimb::Update(int inputstate, DINPUT_JOYSTATE stickstate, const Camera& camera, VECTOR objectCapsuleStart, VECTOR objectCapsuleEnd)
{
	bool stateChange = false;

	Move(stickstate, camera);
	PlayAnimation(0.5f, moveflg);

	//R1�𗣂��ƃX�e�[�g�ύX
	if ((Input::InputNumber::R1 & inputstate) != Input::InputNumber::R1)
	{
		stateChange = true;
	}

	return stateChange;
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="stickstate">�X�e�B�b�N���͏��</param>
/// <param name="camera">�J����</param>
void PlayerClimb::Move(DINPUT_JOYSTATE stickstate, Camera camera)
{
	moveVec = VGet(0.0f, 0.0f, 0.0f);
	moveflg = false;

	//���X�e�B�b�N�̊p�x�����
	float stickX = stickstate.X;
	float stickY = -stickstate.Y;
}