#include"DxLib.h"
#include"Loader.h"
#include"CollisionData.h"
#include"CollisionManager.h"
#include"Wood.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Wood::Wood()
{
	Loader* loader = loader->GetInstance();

	modelHandle = loader->GetHandle(Loader::Kind::WoodModel);

	collisionManager = collisionManager->GetInstance();

	//�Փˌ�̏�����ݒ�
	capsule1CollisionData.HitProcess = std::bind(&Wood::OnHitObject, this);
	capsule2CollisionData.HitProcess = std::bind(&Wood::OnHitObject, this);
	collisionManager->AddCollisionData(&capsule1CollisionData);
	collisionManager->AddCollisionData(&capsule2CollisionData);

	RegisterCollisionData();

	//�|�W�V���������f
	MV1SetScale(modelHandle, VGet(40.0f, 40.0f, 40.0f));
	MV1SetRotationXYZ(modelHandle, VGet(-DX_PI_F / 2, 0.0f, -0.7f));
	MV1SetPosition(modelHandle, drawPosition);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Wood::~Wood()
{
	collisionManager->RemoveCollisionData(&capsule1CollisionData);
	collisionManager->RemoveCollisionData(&capsule2CollisionData);
}

/// <summary>
/// �`��
/// </summary>
void Wood::Draw()
{
	MV1DrawModel(modelHandle);

	//�m�F�p
	//DrawCapsule3D(cap1Start, cap1End, CapsuleRadius, 8, GetColor(127, 127, 0), GetColor(127, 127, 0), FALSE);
	//DrawCapsule3D(cap2Start, cap2End, CapsuleRadius, 8, GetColor(0, 255, 255), GetColor(0, 255, 255), FALSE);
}

/// <summary>
/// �Փˎ��̏���
/// </summary>
void Wood::OnHitObject()
{

}

/// <summary>
/// �����蔻����Z�b�g
/// </summary>
void Wood::RegisterCollisionData()
{
	//�J�v�Z��1
	capsule1CollisionData.tag = ObjectTag::StageObject;
	capsule1CollisionData.position = cap1pos;
	capsule1CollisionData.startPosition = cap1Start;
	capsule1CollisionData.endPosition = cap1End;
	capsule1CollisionData.radius = CapsuleRadius;
	capsule1CollisionData.moveVec = VGet(0, 0, 0);
	capsule1CollisionData.isCollisionActive = true;

	//�J�v�Z��2
	capsule2CollisionData.tag = ObjectTag::StageObject;
	capsule2CollisionData.position = cap2pos;
	capsule2CollisionData.startPosition = cap2Start;
	capsule2CollisionData.endPosition = cap2End;
	capsule2CollisionData.radius = CapsuleRadius;
	capsule2CollisionData.moveVec = VGet(0, 0, 0);
	capsule2CollisionData.isCollisionActive = true;
}