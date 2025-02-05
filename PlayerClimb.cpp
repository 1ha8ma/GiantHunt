#include<math.h>
#include"DxLib.h"
#include"CollisionData.h"
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

	//�ϐ�������
	calculation = new Calculation();
	stopanimflg = false;
	targetLookDirection = lookDir;
	rotateY = 0.0f;
	rotateH = 0.0f;
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
/// <param name="objectCapsuleStart">�Փ˂��Ă���J�v�Z���n�_</param>
/// <param name="objectCapsuleEnd">�J�v�Z���I�_</param>
/// <returns>��Ԃ�ύX���邩</returns>
bool PlayerClimb::Update(UsePlayerData playerData, const Camera& camera,CollisionData objectCollision)
{
	bool stateChange = false;//��ԕύX�t���O

	Move(playerData, camera, objectCollision);
	PlayAnimation(0.5f, stopanimflg);

	//R1�𗣂��ƃX�e�[�g�ύX
	if ((Input::InputNumber::R1 & playerData.inputState) != Input::InputNumber::R1)
	{
		stateChange = true;
	}

	return stateChange;
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="playerData">�v���C���[�f�[�^</param>
/// <param name="camera"></param>
/// <param name="objectCollision"></param>
void PlayerClimb::Move(UsePlayerData playerData, Camera camera, CollisionData objectCollision )
{
	stopanimflg = true;										//�A�j���[�V������~�t���O������
	moveVec = VGet(0.0f, 0.0f, 0.0f);						//moveVec������
	VECTOR afterPos = VGet(0.0f, 0.0f, 0.0f);				//�v�Z��|�W�V����
	VECTOR positionFromShaftstart = VGet(0.0f, 0.0f, 0.0f);	//���̎n�_����̃|�W�V�����܂ł̃x�N�g��
	
	//���X�e�B�b�N�̊p�x�����
	float stickX = playerData.stickState.X;
	float stickY = -playerData.stickState.Y;

	//�ΏۃJ�v�Z���̎������
	VECTOR shaft = VSub(objectCollision.startPosition, objectCollision.endPosition);

	//�o���Ă���ꏊ���J�v�Z���̓��̕�������[�̋��̕���������
	int capsuleRidePlace;	//0:�� 1:�J�v�Z���n�_ 2:�J�v�Z���I�_

	//�J�v�Z���̗��[�̂ǂ���ɋ߂���
	float sphere1 = calculation->LengthTwoPoint3D(playerData.position, objectCollision.startPosition);
	float sphere2 = calculation->LengthTwoPoint3D(playerData.position, objectCollision.endPosition);

	//�n�_�ɋ߂��ꍇ
	if (sphere1 < sphere2)
	{
		VECTOR OA = VSub(objectCollision.endPosition, objectCollision.startPosition);		//�n�_���I�_
		VECTOR OB = VSub(playerData.position, objectCollision.startPosition);				//�n�_���v���C���[�|�W�V����
		VECTOR tipPoint = VNorm(OA);														//�I�_���n�_�x�N�g���̐��K�� * ���a = �J�v�Z���̐�[�|�W�V����
		tipPoint = VScale(tipPoint, -1);
		tipPoint = VScale(tipPoint, objectCollision.radius);
		VECTOR OH = calculation->OrthogonalProjectionVector(OA, OB);
		float distanceForH = calculation->LengthTwoPoint3D(OH, tipPoint);					//�J�v�Z���̐�[�Ɛ����̋���
		if (distanceForH < objectCollision.radius)
		{
			capsuleRidePlace = 1;
		}
		else
		{
			capsuleRidePlace = 0;
		}
	}
	else //�I�_�ɋ߂��ꍇ
	{
		VECTOR OA = VSub(objectCollision.startPosition, objectCollision.endPosition);
		VECTOR OB = VSub(playerData.position, objectCollision.endPosition);
		VECTOR tipPoint = VNorm(OA);
		tipPoint = VScale(tipPoint, -1);
		tipPoint = VScale(tipPoint, objectCollision.radius);
		VECTOR OH = calculation->OrthogonalProjectionVector(OA, OB);
		float distanceForH = calculation->LengthTwoPoint3D(OH, tipPoint);	//�J�v�Z���̐�[�Ɛ����̋���
		if (distanceForH < objectCollision.radius)
		{
			capsuleRidePlace = 2;
		}
		else
		{
			capsuleRidePlace = 0;
		}
	}

	//���ɂ���ꍇ�̋��ƃv���C���[�̊p�x�v�Z
	if (capsuleRidePlace == 1)
	{
		CalculationAngle(playerData.position, objectCollision.startPosition);
	}
	if (capsuleRidePlace == 2)
	{
		CalculationAngle(playerData.position, objectCollision.endPosition);
	}

	//��
	if (stickY > 0)
	{
		if (capsuleRidePlace == 0)
		{
			stopanimflg = false;
			//���̐��������ɉ�]
			positionFromShaftstart = VSub(playerData.position, objectCollision.startPosition);
			afterPos = calculation->RodriguesRotationFormula(shaft, -RotateSpeed, positionFromShaftstart);
			//�v�Z�O�ƌv�Z��̍�
			moveVec = VSub(afterPos, positionFromShaftstart);
		}
		if (capsuleRidePlace == 1)
		{
			stopanimflg = false;

			rotateY += RotateSpeed;
			
			afterPos.x = objectCollision.startPosition.x + objectCollision.radius * cos(rotateY) * cos(rotateH);
			afterPos.y = objectCollision.startPosition.y + objectCollision.radius * sin(rotateY);
			afterPos.z = objectCollision.startPosition.z + objectCollision.radius * cos(rotateY) * sin(rotateH);

			//�v�Z�O�ƌv�Z��̍�
			moveVec = VSub(afterPos, playerData.position);
		}
		if (capsuleRidePlace == 2)
		{
			stopanimflg = false;

			rotateY += RotateSpeed;

			afterPos.x = objectCollision.endPosition.x + objectCollision.radius * cos(rotateY) * cos(rotateH);
			afterPos.y = objectCollision.endPosition.y + objectCollision.radius * sin(rotateY);
			afterPos.z = objectCollision.endPosition.z + objectCollision.radius * cos(rotateY) * sin(rotateH);

			//�v�Z�O�ƌv�Z��̍�
			moveVec = VSub(afterPos, playerData.position);
		}
	}
	//��
	if (stickY < 0)
	{
		if (capsuleRidePlace == 0)
		{
			stopanimflg = false;
			//���̐��������ɉ�]
			positionFromShaftstart = VSub(playerData.position, objectCollision.startPosition);
			afterPos = calculation->RodriguesRotationFormula(shaft, RotateSpeed, positionFromShaftstart);
			//�v�Z�O�ƌv�Z��̍�
			moveVec = VSub(afterPos, positionFromShaftstart);
		}
		if (capsuleRidePlace == 1)
		{
			stopanimflg = false;

			rotateY -= RotateSpeed;

			afterPos.x = objectCollision.startPosition.x + objectCollision.radius * cos(rotateY) * cos(rotateH);
			afterPos.y = objectCollision.startPosition.y + objectCollision.radius * sin(rotateY);
			afterPos.z = objectCollision.startPosition.z + objectCollision.radius * cos(rotateY) * sin(rotateH);

			//�v�Z�O�ƌv�Z��̍�
			moveVec = VSub(afterPos, playerData.position);
		}
		if (capsuleRidePlace == 2)
		{
			stopanimflg = false;

			rotateY -= RotateSpeed;

			afterPos.x = objectCollision.endPosition.x + objectCollision.radius * cos(rotateY) * cos(rotateH);
			afterPos.y = objectCollision.endPosition.y + objectCollision.radius * sin(rotateY);
			afterPos.z = objectCollision.endPosition.z + objectCollision.radius * cos(rotateY) * sin(rotateH);

			//�v�Z�O�ƌv�Z��̍�
			moveVec = VSub(afterPos, playerData.position);
		}
	}
	//��
	if (stickX < 0)
	{
		if (capsuleRidePlace == 0)
		{
			//���̕����Ɉړ�
			stopanimflg = false;

			VECTOR shaftVec = VNorm(shaft);
			VECTOR speedVec = VScale(shaftVec, Speed);
			moveVec = VAdd(moveVec, speedVec);
		}
		if (capsuleRidePlace == 1)
		{
			stopanimflg = false;

			rotateH -= RotateSpeed;

			afterPos.x = objectCollision.startPosition.x + objectCollision.radius * cos(rotateY) * cos(rotateH);
			afterPos.y = objectCollision.startPosition.y + objectCollision.radius * sin(rotateY);
			afterPos.z = objectCollision.startPosition.z + objectCollision.radius * cos(rotateY) * sin(rotateH);

			//�v�Z�O�ƌv�Z��̍�
			moveVec = VSub(afterPos, playerData.position);
		}
		if (capsuleRidePlace == 2)
		{
			stopanimflg = false;

			rotateH -= RotateSpeed;

			afterPos.x = objectCollision.endPosition.x + objectCollision.radius * cos(rotateY) * cos(rotateH);
			afterPos.y = objectCollision.endPosition.y + objectCollision.radius * sin(rotateY);
			afterPos.z = objectCollision.endPosition.z + objectCollision.radius * cos(rotateY) * sin(rotateH);

			//�v�Z�O�ƌv�Z��̍�
			moveVec = VSub(afterPos, playerData.position);
		}
	}
	//�E
	if (stickX > 0)
	{
		if (capsuleRidePlace == 0)
		{
			//���̕����Ɉړ�
			stopanimflg = false;

			VECTOR shaftVec = VNorm(shaft);
			VECTOR speedVec = VScale(shaftVec, -Speed);
			moveVec = VAdd(moveVec, speedVec);
		}
		if (capsuleRidePlace == 1)
		{
			stopanimflg = false;

			rotateH += RotateSpeed;

			afterPos.x = objectCollision.startPosition.x + objectCollision.radius * cos(rotateY) * cos(rotateH);
			afterPos.y = objectCollision.startPosition.y + objectCollision.radius * sin(rotateY);
			afterPos.z = objectCollision.startPosition.z + objectCollision.radius * cos(rotateY) * sin(rotateH);

			//�v�Z�O�ƌv�Z��̍�
			moveVec = VSub(afterPos, playerData.position);
		}
		if (capsuleRidePlace == 2)
		{
			stopanimflg = false;

			rotateH += RotateSpeed;

			afterPos.x = objectCollision.endPosition.x + objectCollision.radius * cos(rotateY) * cos(rotateH);
			afterPos.y = objectCollision.endPosition.y + objectCollision.radius * sin(rotateY);
			afterPos.z = objectCollision.endPosition.z + objectCollision.radius * cos(rotateY) * sin(rotateH);

			//�v�Z�O�ƌv�Z��̍�
			moveVec = VSub(afterPos, playerData.position);
		}
	}

	//�I�u�W�F�N�g��moveVec�����Z
	moveVec = VAdd(moveVec, objectCollision.moveVec);
}

/// <summary>
/// �p�x�v�Z
/// </summary>
/// <param name="playerPosition">�v���C���[�|�W�V����</param>
/// <param name="objectPosition">����Ώۂ̃|�W�V����</param>
void PlayerClimb::CalculationAngle(VECTOR playerPosition, VECTOR objectPosition)
{
	//����
	float dx = playerPosition.x - objectPosition.x;
	float dy = playerPosition.y - objectPosition.y;
	float dz = playerPosition.z - objectPosition.z;

	//���a
	float r = sqrt(dx * dx + dy * dy + dz * dz);

	//�p�x�v�Z
	rotateY = asinf(dy / r);
	rotateH = atan2f(dz, dx);
}