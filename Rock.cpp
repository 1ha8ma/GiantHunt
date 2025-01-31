#include"DxLib.h"
#include"CollisionData.h"
#include"CollisionManager.h"
#include"Rock.h"

/// <summary>
/// コンストラクタ
/// </summary>
Rock::Rock(int modelHandle, VECTOR addCapsuleStart, VECTOR addCapsuleEnd, float capsuleRadius, VECTOR drawPosition, VECTOR rotate, float scale)
{
	this->modelHandle = modelHandle;

	this->drawPosition = drawPosition;
	this->capsuleStart = VAdd(drawPosition, addCapsuleStart);
	this->capsuleEnd = VAdd(drawPosition, addCapsuleEnd);
	this->capsuleRadius = capsuleRadius;

	//当たり判定情報
	collisionManager = collisionManager->GetInstance();
	RegisterCollisionData();
	collisionData.HitProcess = std::bind(&Rock::OnHitObject, this);
	collisionManager->AddCollisionData(&collisionData);

	//ポジション等反映
	MV1SetScale(modelHandle, VGet(scale, scale, scale));
	MV1SetRotationXYZ(modelHandle, VGet(rotate.x, rotate.y, rotate.z));
	MV1SetPosition(modelHandle, drawPosition);
}

/// <summary>
/// デストラクタ
/// </summary>
Rock::~Rock()
{
	collisionManager->RemoveCollisionData(&collisionData);
}

/// <summary>
/// 描画
/// </summary>
void Rock::Draw()
{
	MV1DrawModel(modelHandle);

	//確認用
	//DrawCapsule3D(capsuleStart, capsuleEnd, capsuleRadius, 8, GetColor(0, 255, 255), GetColor(0, 255, 255), FALSE);
}

/// <summary>
/// オブジェクト衝突時処理
/// </summary>
void Rock::OnHitObject()
{

}

/// <summary>
/// 当たり判定情報セット
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