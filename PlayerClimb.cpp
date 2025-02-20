#include<fstream>
#include<math.h>
#include"DxLib.h"
#include"nlohmann/json.hpp"
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

	//�t�@�C���ǂݍ���
	using Json = nlohmann::json;
	Json jsonData;
	std::ifstream ifs("Data/PlayerData.json");
	if (ifs)
	{
		ifs >> jsonData;
	}

	//�ϐ�������
	calculation = new Calculation();
	stopanimflg = false;
	targetLookDirection = lookDir;
	Speed = jsonData["ClimbMoveSpeed"];
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

	//MoveCapsule(playerData, camera, objectCollision);
	MoveMesh(playerData, camera,objectCollision);
	PlayAnimation(0.5f, stopanimflg);

	//R1�𗣂��ƃX�e�[�g�ύX
	if ((Input::InputNumber::R1 & playerData.inputState) != Input::InputNumber::R1)
	{
		stateChange = true;
	}

	return stateChange;
}

/// <summary>
/// ���b�V���Ƃ̓o�蓮��
/// </summary>
/// <param name="playerData">�v���C���[���</param>
/// <param name="camera">�J����</param>
/// <param name="objectData">�I�u�W�F�N�g���</param>
void PlayerClimb::MoveMesh(UsePlayerData playerData, Camera camera,CollisionData objectData)
{
	stopanimflg = true;										//�A�j���[�V������~�t���O������
	moveVec = VGet(0.0f, 0.0f, 0.0f);						//moveVec������
	bool hit = false;										//���b�V���ɓ�������
	float nearDistance = 0;										//��ԋ߂������|���S���ƃv���C���[�̋���
	int nearNumber = 0;											//��ԋ߂������|���S���̔ԍ�

	//���X�e�B�b�N�̊p�x�����
	float stickX = playerData.stickState.X;
	float stickY = -playerData.stickState.Y;//�R���g���[���[����͂�+�̒l�ɂȂ�悤��

	//���͂�������ΕԂ�
	if (stickX == 0 && stickY == 0)
	{
		return;
	}
	else
	{
		stopanimflg = false;
	}
	
	for (int i = 0; i < objectData.meshData.polygonList.PolygonNum; i++)
	{
		VECTOR vertex0 = objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[i].VIndex[0]].Position;
		VECTOR vertex1 = objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[i].VIndex[1]].Position;
		VECTOR vertex2 = objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[i].VIndex[2]].Position;

		//���������
		float distance = Segment_Triangle_MinLength(playerData.capsuleStart, playerData.capsuleEnd, vertex0, vertex1, vertex2);

		//���ڂ̎�
		if (i == 0)
		{
			nearDistance = distance;
		}

		//�����蔻��
		if (distance < playerData.capsuleRadius)
		{
			hit = true;
		}

		//��ԋ߂��������X�V
		if (nearDistance > distance)
		{
			nearDistance = distance;
			nearNumber = i;
		}

		if (hit)
		{
			VECTOR vec01 = VSub(vertex1, vertex0);	//0��1
			VECTOR vec02 = VSub(vertex2, vertex0);	//0��2
			VECTOR normVec = VCross(vec01, vec02);	//�@���x�N�g��
			normVec = VNorm(normVec);

			//�@���Ƃ͋t�̕���(�|���S���̕����Ɍ�����)
			moveVec = normVec;
			//�@���̕ӖʂƂ̊p�x
			float angley = calculation->AngleTwoVector(normVec, VGet(normVec.x, 0, normVec.z));

			//��
			if (stickY > 0)
			{
				//�����x�N�g��
				VECTOR vecDir = VSub(playerData.capsuleStart, playerData.centerPosition);
				vecDir = VNorm(vecDir);

				moveVec = VScale(vecDir, Speed);
			}
			//��
			if (stickY < 0)
			{
				//�����x�N�g��
				VECTOR vecDir = VSub(playerData.capsuleEnd, playerData.centerPosition);
				vecDir = VNorm(vecDir);

				moveVec = VScale(vecDir, Speed);
			}
			//�E
			if (stickX > 0)
			{
				//��]�������
				VECTOR shaft = VSub(playerData.capsuleStart, playerData.capsuleEnd);
				shaft = VNorm(shaft);
				//���ʂ���90�x���Ɉړ��x�N�g���̌�����ݒ�
				MATRIX rot = MGetRotAxis(shaft, DX_PI_F / 2);
				VECTOR vecDir = playerData.lookDirection;
				vecDir = VNorm(vecDir);
				vecDir = VTransform(vecDir, rot);
				
				moveVec = VScale(vecDir, Speed);
			}
			//��
			if (stickX < 0)
			{
				//��]�������
				VECTOR shaft = VSub(playerData.capsuleStart, playerData.capsuleEnd);
				shaft = VNorm(shaft);
				//���ʂ���-90�x���Ɉړ��x�N�g���̌�����ݒ�
				MATRIX rot = MGetRotAxis(shaft, -DX_PI_F / 2);
				VECTOR vecDir = playerData.lookDirection;
				vecDir = VNorm(vecDir);
				vecDir = VTransform(vecDir, rot);

				moveVec = VScale(vecDir, Speed);
			}

			//�O�̃x�N�g������V�����x�N�g���ɕϊ������Ƃ��̉�]�s��
			//rotateMatrix = MGetRotVec2(targetLookDirection, VScale(normVec, -1));
			//�@���̋t�̕����Ɍ�����
			targetLookDirection = VScale(normVec, -1);

			break;
		}
	}

	//�ǂ��ɂ��������Ă��Ȃ���Έ�ԋ߂������|���S���ɋ߂Â���
	if (!hit)
	{
		VECTOR vertex0 = objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[nearNumber].VIndex[0]].Position;
		VECTOR vertex1 = objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[nearNumber].VIndex[1]].Position;
		VECTOR vertex2 = objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[nearNumber].VIndex[2]].Position;
		VECTOR vec01 = VSub(vertex1, vertex0);	//0��1
		VECTOR vec02 = VSub(vertex2, vertex0);	//0��2
		VECTOR normVec = VCross(vec01, vec02);	//�@���x�N�g��
		normVec = VNorm(normVec);

		moveVec = VScale(normVec, -1);
		moveVec = VScale(moveVec, nearDistance);

		//�@���̋t�̕����Ɍ�����
		targetLookDirection = VScale(normVec, -1);
	}
}

/// <summary>
/// �J�v�Z���Ƃ̓o�蓮��(�g�p���Ȃ�)
/// </summary>
/// <param name="playerData">�v���C���[�f�[�^</param>
/// <param name="camera">�J�v�Z��</param>
/// <param name="objectCollision">�I�u�W�F�N�g���</param>
void PlayerClimb::MoveCapsule(UsePlayerData playerData, Camera camera, CollisionData objectCollision )
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