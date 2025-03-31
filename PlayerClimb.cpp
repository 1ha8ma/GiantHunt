#include<fstream>
#include<math.h>
#include"DxLib.h"
#include"nlohmann/json.hpp"
#include"CollisionData.h"
#include"Camera.h"
#include"Calculation.h"
#include"Input.h"
#include"PlayerClimb.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="modelHandle">���f���n���h��</param>
PlayerClimb::PlayerClimb(int modelHandle, VECTOR lookDir) :PlayerStateProcessBase(modelHandle)
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

	//�C���X�^���X��
	calculation = new Calculation();

	//�ϐ�������
	calculation = new Calculation();
	stopAnimation = false;
	newLookDirection = lookDir;
	Speed = jsonData["ClimbMoveSpeed"];
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

	//����
	Move(playerData, camera,objectCollision);
	//�A�j���[�V�����Đ�
	PlayAnimation(0.5f, stopAnimation);

	//R1�𗣂��ƃX�e�[�g�ύX
	if ((Input::InputNumber::R1 & playerData.inputState) != Input::InputNumber::R1)
	{
		stateChange = true;
	}

	return stateChange;
}

/// <summary>
///�o�蓮��
/// </summary>
/// <param name="playerData">�v���C���[���</param>
/// <param name="camera">�J����</param>
/// <param name="objectData">�I�u�W�F�N�g���</param>
void PlayerClimb::Move(UsePlayerData playerData, Camera camera, CollisionData objectData)
{
	//������
	moveVec = VGet(0, 0, 0);				
	float nearDistance;						//�ł��߂�����
	VECTOR nearVer0, nearVer1, nearVer2;	//�ł��߂��|���S���̒��_
	int nearPolygonNumber;					//�ł��߂��|���S���ԍ�
	playerCapStart = playerData.capsuleStart;
	playerCapEnd = playerData.capsuleEnd;
	capsuleRadius = playerData.capsuleRadius;
	stopAnimation = true;

	//�߂��|���S���̏������
	NearPolygon(nearPolygonNumber,nearVer0, nearVer1, nearVer2, nearDistance, objectData);

	//�m�F�p���S�_
	playerPosition = playerData.position;
	nearPolygonCenter = VAdd(VAdd(nearVer0, nearVer1), nearVer2);
	nearPolygonCenter.x = nearPolygonCenter.x / 3;
	nearPolygonCenter.y = nearPolygonCenter.y / 3;
	nearPolygonCenter.z = nearPolygonCenter.z / 3;

	//�@���x�N�g��
	VECTOR normVec = calculation->Normalize(nearVer0, nearVer1, nearVer2);

	//���͂����moveVec
	bool isInputStick = MoveVecForInput(playerData, camera, normVec, nearVer0);

	//�����Ă�������X�V
	newLookDirection = VScale(normVec, -1);

	//��]�s��X�V
	UpdateRotateMatrix(newLookDirection, playerData.lookDirection);

	//���͂�������ΕԂ�
	if (!isInputStick)
	{
		moveVec = VGet(0, 0, 0);
		return;
	}

	//�A�j���[�V�����𒆒f�����Ȃ�
	stopAnimation = false;

	//�X�s�[�h���Z
	moveVec = VScale(moveVec, Speed);

	//�ړ���̃|�W�V����
	VECTOR moveAfterPos = VAdd(playerData.position, moveVec);
	UpdateTentativePlayerCapsule(playerData, moveAfterPos);

	//�ړ���̃|�W�V�������L�����m�F
	VECTOR addMoveVec = IsValidMoveAfterPosition(objectData, moveAfterPos, nearVer0, nearVer1, nearVer2);

//	moveVec = VAdd(moveVec, addMoveVec);
}

/// <summary>
/// �m�F�p
/// </summary>
void PlayerClimb::Draw()
{
	//�|�W�V�����Ɠo���Ă���|���S�����_
	DrawLine3D(nearPolygonCenter, playerPosition,GetColor(127,255,212));
}

/// <summary>
/// ���͂����moveVec�쐬
/// </summary>
/// <param name="playerData">�v���C���[���</param>
/// <param name="camera">�J�������</param>
/// <param name="normVec">�@��</param>
/// <param name="vertex0">���_</param>
/// <returns>���͂���������</returns>
bool PlayerClimb::MoveVecForInput(UsePlayerData playerData, Camera camera, VECTOR normVec, VECTOR vertex0)
{
	//���͂�������ΕԂ�
	if (playerData.stickState.X == 0 && playerData.stickState.Y == 0)
	{
		return false;
	}

	//���͂���̃x�N�g���쐬
	VECTOR inputDir = VGet(0.0f, 0.0f, 0.0f);
	//��
	if (playerData.stickState.Y < 0.0f)
	{
		inputDir = VAdd(inputDir, VSub(playerData.capsuleStart, playerData.capsuleEnd));
	}
	//��
	if (playerData.stickState.Y > 0.0f)
	{
		inputDir = VAdd(inputDir, VSub(playerData.capsuleEnd, playerData.capsuleStart));
	}
	//�E
	if (playerData.stickState.X > 0.0f)
	{
		VECTOR cross = VCross(VSub(playerData.capsuleStart, playerData.capsuleEnd), playerData.lookDirection);
		inputDir = VAdd(inputDir, cross);
	}
	//��
	if (playerData.stickState.X < 0.0f)
	{
		VECTOR cross = VCross(playerData.lookDirection, VSub(playerData.capsuleStart, playerData.capsuleEnd));
		inputDir = VAdd(inputDir, cross);
	}

	//���ʂ��ړ�����悤�ɕ␳
	inputDir = VNorm(inputDir);
	moveVec = ProjectOnPlane(inputDir, normVec);
	moveVec = VNorm(moveVec);

	return true;
}

/// <summary>
/// ��]�s��X�V
/// </summary>
/// <param name="newLookDirection">�V���������Ă������</param>
/// <param name="prevLookDirection">�O�Ɍ����Ă�������</param>
void PlayerClimb::UpdateRotateMatrix(VECTOR newLookDirection, VECTOR prevLookDirection)
{
	//�O�̕����ƍ���̕����̍�
	MATRIX addMatrix = MGetRotVec2(prevLookDirection, newLookDirection);

	rotateMatrix = MMult(rotateMatrix, addMatrix);
}

/// <summary>
/// �ł��߂��|���S���̏������
/// </summary>
/// <param name="nearVer0">���_0</param>
/// <param name="nearVer1">���_1</param>
/// <param name="nearVer2">���_2</param>
/// <param name="nearDistance">�ł��߂�����</param>
/// <param name="objectData">�I�u�W�F�N�g�f�[�^</param>
void PlayerClimb::NearPolygon(int& nearPolygonNumber, VECTOR& nearVer0, VECTOR& nearVer1, VECTOR& nearVer2, float& nearDistance, const CollisionData objectData)
{
	for (int i = 0; i < objectData.meshData.polygonList.PolygonNum; i++)
	{
		VECTOR vertex0 = objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[i].VIndex[0]].Position;
		VECTOR vertex1 = objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[i].VIndex[1]].Position;
		VECTOR vertex2 = objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[i].VIndex[2]].Position;

		//���������
		float distance = Segment_Triangle_MinLength(playerCapStart, playerCapEnd, vertex0, vertex1, vertex2);

		//���ڂ̏���
		if (i == 0)
		{
			nearDistance = distance;
			nearVer0 = vertex0;
			nearVer1 = vertex1;
			nearVer2 = vertex2;
			nearPolygonNumber = i;
		}

		//�ł��߂��|���S���Ƃ��̋���
		if (nearDistance > distance)
		{
			nearDistance = distance;
			nearVer0 = vertex0;
			nearVer1 = vertex1;
			nearVer2 = vertex2;
			nearPolygonNumber = i;
		}
	}
}

/// <summary>
/// ���͂��ꂽ�����|���S���̕��ʂɉf��
/// </summary>
/// <param name="inputDir">���͂��ꂽ����</param>
/// <param name="polygonNorm">�|���S���@��</param>
/// <returns></returns>
VECTOR PlayerClimb::ProjectOnPlane(VECTOR inputDir, VECTOR polygonNorm)
{
	float dot = VDot(inputDir, polygonNorm);
	return VSub(inputDir, VScale(polygonNorm, VDot(inputDir, polygonNorm)));
}

/// <summary>
/// �ړ��悪�L�����m�F
/// </summary>
/// <param name="objectData">�I�u�W�F�N�g�f�[�^</param>
/// <param name="moveAfterPosition">�ړ���|�W�V����</param>
/// <param name="vertex0">���_</param>
/// <param name="vertex1">���_</param>
/// <param name="vertex2">���_</param>
/// <returns>�ǉ��̈ړ��x�N�g��</returns>
VECTOR PlayerClimb::IsValidMoveAfterPosition(CollisionData objectData, VECTOR moveAfterPosition, VECTOR vertex0, VECTOR vertex1, VECTOR vertex2)
{
	VECTOR addMoveVec = VGet(0, 0, 0);	//�ǉ��p�ړ��x�N�g��

	//�ړ���̍ŋߖT�_�����߂�
	VECTOR capsuleClosest, triangleClosest;
	calculation->ClosestPointCapsuleAndTriangle(playerCapStart, playerCapEnd, vertex0, vertex1, vertex2, capsuleClosest, triangleClosest);

	//�m�F�p
	float checkLen = calculation->LengthTwoPoint3D(capsuleClosest, triangleClosest);

	//���蒆�̃|���S���̒��ɓ��e�_�����邩
	bool inPolygon = false;
	VECTOR polyNorm = calculation->Normalize(vertex0, vertex1, vertex2);
	float u, v, w;
	VECTOR projectClosest = VSub(capsuleClosest, VScale(polyNorm, VDot(VSub(capsuleClosest, vertex0), polyNorm)));
	calculation->Barycentric(vertex0, vertex1, vertex2, projectClosest, u, v, w);
	if (u >= 0 && v >= 0 && w >= 0)
	{
		inPolygon = true;
	}

	//�ׂ̎O�p�`�ֈړ��ł��邩�m�F
	if (!inPolygon)
	{	
		//�ׂ̃|���S����T��
		int nextPolygonNumber;
		nextPolygonNumber = FindNextPolygon(objectData, capsuleClosest, vertex0, vertex1, vertex2);

		//�|�W�V������ׂ̃|���S���̍ŋߖT�_�ɕύX
		VECTOR nextVer0 = objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[nextPolygonNumber].VIndex[0]].Position;
		VECTOR nextVer1 = objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[nextPolygonNumber].VIndex[1]].Position;
		VECTOR nextVer2 = objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[nextPolygonNumber].VIndex[2]].Position;

		VECTOR nextCapClosest, nextTriClosest;
		calculation->ClosestPointCapsuleAndTriangle(playerCapStart, playerCapEnd, nextVer0, nextVer1, nextVer2, nextCapClosest, nextTriClosest);
		VECTOR newPos = nextTriClosest;
		newPos = VAdd(newPos, VScale(VNorm(VSub(nextCapClosest, nextTriClosest)), capsuleRadius));

		addMoveVec = VSub(moveAfterPosition, newPos);
	}

	return addMoveVec;
}

/// <summary>
/// �ׂ̃|���S����������
/// </summary>
/// <param name="point">�|�W�V�����𓊉e�����_</param>
/// <param name="vertex0">���_</param>
/// <param name="vertex1">���_</param>
/// <param name="vertex2">���_</param>
int PlayerClimb::FindNextPolygon(CollisionData objectData,VECTOR point, VECTOR vertex0, VECTOR vertex1, VECTOR vertex2)
{
	VECTOR vertex[3] = { vertex0,vertex1,vertex2};
	
	//�@��
	VECTOR normal = calculation->Normalize(vertex0, vertex1, vertex2);

	//�����Ă����ӂ����|���S�������
	int nextPolygonNumber = -1;
	if (CheckOutSide(point, normal, vertex1, vertex0, vertex2))
	{
		nextPolygonNumber = CheckSameVertexPolygon(objectData, vertex1, vertex0);
	}
	if (CheckOutSide(point, normal, vertex2, vertex1, vertex0))
	{
		nextPolygonNumber = CheckSameVertexPolygon(objectData, vertex2, vertex1);
	}
	if (CheckOutSide(point, normal, vertex2, vertex0, vertex1))
	{
		nextPolygonNumber = CheckSameVertexPolygon(objectData, vertex2, vertex0);
	}
	
	return nextPolygonNumber;
}

/// <summary>
/// �o���ӂ�T��
/// </summary>
/// <param name="point">�m�F����_</param>
/// <param name="normal">�@��</param>
/// <param name="sideVer1">�ӂ̒��_</param>
/// <param name="sideVer2">�ӂ̒��_</param>
/// <param name="noSideVer">�ӂɎg�p���Ȃ����_</param>
/// <returns>true:�ӂ̊O�@false:�ӂ̓�</returns>
bool PlayerClimb::CheckOutSide(VECTOR point, VECTOR normal, VECTOR sideVer1, VECTOR sideVer2,VECTOR noSideVer)
{
	//�ӂ̃x�N�g��
	VECTOR side = VSub(sideVer2, sideVer1);

	//�ӂɐ����ȃx�N�g��
	VECTOR sideVerticalVec = VCross(side, normal);

	//�ӂƔ��΂̒��_�̕���
	float side1 = VDot(sideVerticalVec, VSub(noSideVer, sideVer1));
	//�ӂƓ_�̕���
	float side2 = VDot(sideVerticalVec, VSub(point, sideVer1));

	//���_�̕����ƕӂ̕����������łȂ��Ȃ�O�ɏo�Ă���
	if (side1 * side2 >= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/// <summary>
/// �������_��2���|���S����T��
/// </summary>
/// <param name="vertex1">���_</param>
/// <param name="vertex2">���_</param>
/// <returns>�Ώۂ̃|���S���̔ԍ�</returns>
int PlayerClimb::CheckSameVertexPolygon(CollisionData objectData, VECTOR vertex1, VECTOR vertex2)
{
	VECTOR vertex3;
	int sameTwoVerPolygonNum;
	int sameVer1, sameVer2;

	for (int i = 0; i < objectData.meshData.polygonList.PolygonNum; i++)
	{
		VECTOR checkVer0 = objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[i].VIndex[0]].Position;
		VECTOR checkVer1 = objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[i].VIndex[1]].Position;
		VECTOR checkVer2 = objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[i].VIndex[2]].Position;

		int sameCount = 0;

		for (int j = 0; j < 3; j++)
		{
			if (calculation->SameVector(vertex1, objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[i].VIndex[j]].Position))
			{
				sameCount++;
				sameVer1 = j;
			}
		}

		for (int k = 0; k < 3; k++)
		{
			if (calculation->SameVector(vertex2, objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[i].VIndex[k]].Position))
			{
				sameCount++;
				sameVer2 = k;
			}
		}

		if (sameCount == 2)
		{
			sameTwoVerPolygonNum = i;
			break;
		}
	}

	//3�ڂ̒��_��T��
	for (int l = 0; l < 3; l++)
	{
		if (sameVer1 != l && sameVer2 != l)
		{
			vertex3 = objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[sameTwoVerPolygonNum].VIndex[l]].Position;
		}
	}

	return sameTwoVerPolygonNum;
}

/// <summary>
/// ���̃v���C���[�J�v�Z�����X�V
/// </summary>
/// <param name="playerData">�v���C���[���</param>
void PlayerClimb::UpdateTentativePlayerCapsule(UsePlayerData playerData,VECTOR moveAfterPos)
{
	VECTOR startVec = VGet(0, 1, 0);
	startVec = VTransform(startVec, rotateMatrix);
	playerCapStart = VAdd(moveAfterPos, VScale(startVec, playerData.wholeBodyCapsuleHalfLength));
	VECTOR endVec = VGet(0, -1, 0);
	endVec = VTransform(endVec, MInverse(rotateMatrix));
	playerCapEnd = VAdd(moveAfterPos, VScale(endVec, playerData.wholeBodyCapsuleHalfLength));
}