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
	calculation = new Calculation();
	stopanimflg = false;

	targetLookDirection = lookDir;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerClimb::~PlayerClimb()
{
	//delete calculation;
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
/// <param name="objectCapsuleStart">�Փ˂��Ă���J�v�Z���n�_</param>
/// <param name="objectCapsuleEnd">�J�v�Z���I�_</param>
/// <returns>��Ԃ�ύX���邩</returns>
bool PlayerClimb::Update(VECTOR position,int inputstate, DINPUT_JOYSTATE stickstate, const Camera& camera, VECTOR objectCapsuleStart, VECTOR objectCapsuleEnd)
{
	bool stateChange = false;//��ԕύX�t���O

	Move(position,stickstate, camera,objectCapsuleStart,objectCapsuleEnd);
	PlayAnimation(0.5f, stopanimflg);

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
void PlayerClimb::Move(VECTOR position, DINPUT_JOYSTATE stickstate, Camera camera, VECTOR objectCapsuleStart, VECTOR objectCapsuleEnd)
{
	moveVec = VGet(0.0f, 0.0f, 0.0f);
	VECTOR afterPos = VGet(0.0f, 0.0f, 0.0f);				//�v�Z��|�W�V����
	VECTOR positionFromShaftstart = VGet(0.0f, 0.0f, 0.0f);	//���̎n�_����̃|�W�V�����܂ł̃x�N�g��	
	stopanimflg = true;

	//���X�e�B�b�N�̊p�x�����
	float stickX = stickstate.X;
	float stickY = -stickstate.Y;

	//�ΏۃJ�v�Z���̎������
	VECTOR shaft = VSub(objectCapsuleStart, objectCapsuleEnd);

	//��
	if (stickY > 0)
	{
		stopanimflg = false;
		//���̐��������ɉ�]
		positionFromShaftstart = VSub(position, objectCapsuleStart);
		afterPos = calculation->RodriguesRotationFormula(shaft, -RotateSpeed, positionFromShaftstart);
		//�v�Z�O�ƌv�Z��̍�
		moveVec = VSub(afterPos, positionFromShaftstart);
	}
	//��
	if (stickY < 0)
	{
		stopanimflg = false;
		//���̐��������ɉ�]
		positionFromShaftstart = VSub(position, objectCapsuleStart);
		afterPos = calculation->RodriguesRotationFormula(shaft, RotateSpeed, positionFromShaftstart);
		//�v�Z�O�ƌv�Z��̍�
		moveVec = VSub(afterPos, positionFromShaftstart);
	}
	//��
	if (stickX < 0)
	{
		//���̕����Ɉړ�
		stopanimflg = false;

		VECTOR shaftVec = VNorm(shaft);
		VECTOR speedVec = VScale(shaftVec, Speed);
		moveVec = VAdd(moveVec, speedVec);
		
	}
	//�E
	if (stickX > 0)
	{
		//���̕����Ɉړ�
		stopanimflg = false;

		VECTOR shaftVec = VNorm(shaft);
		VECTOR speedVec = VScale(shaftVec, -Speed);
		moveVec = VAdd(moveVec, speedVec);
	}
}