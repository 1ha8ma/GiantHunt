#include"DxLib.h"
#include"CollisionData.h"
#include"CollisionManager.h"
#include"Rock.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Rock::Rock(int modelHandle, VECTOR addCapsuleStart, VECTOR addCapsuleEnd, float capsuleRadius, VECTOR drawPosition, VECTOR rotate, float scale)
{
	this->modelHandle = modelHandle;

	this->drawPosition = drawPosition;
	this->capsuleStart = VAdd(drawPosition, addCapsuleStart);
	this->capsuleEnd = VAdd(drawPosition, addCapsuleEnd);
	this->capsuleRadius = capsuleRadius;

	//�����蔻����
	collisionManager = collisionManager->GetInstance();
	RegisterCollisionData();
	collisionData.HitProcess = std::bind(&Rock::OnHitObject, this);
	collisionManager->AddCollisionData(&collisionData);

	//�|�W�V���������f
	MV1SetScale(modelHandle, VGet(scale, scale, scale));
	MV1SetRotationXYZ(modelHandle, VGet(rotate.x, rotate.y, rotate.z));
	MV1SetPosition(modelHandle, drawPosition);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Rock::~Rock()
{
	collisionManager->RemoveCollisionData(&collisionData);
}

/// <summary>
/// �`��
/// </summary>
void Rock::Draw()
{
	MV1DrawModel(modelHandle);

	//�m�F�p
	//DrawCapsule3D(capsuleStart, capsuleEnd, capsuleRadius, 8, GetColor(0, 255, 255), GetColor(0, 255, 255), FALSE);
}

/// <summary>
/// �I�u�W�F�N�g�Փˎ�����
/// </summary>
void Rock::OnHitObject()
{

}

/// <summary>
/// �����蔻����Z�b�g
/// </summary>
void Rock::RegisterCollisionData()
{
	collisionData.tag = ObjectTag::StageObject;
	collisionData.startPosition = capsuleStart;
	collisionData.endPosition =	capsuleEnd;
	collisionData.radius = capsuleRadius;
	collisionData.moveVec = VGet(0, 0, 0);
	collisionData.isCollisionActive = true;
}