#include"DxLib.h"
#include"Loader.h"
#include"CollisionData.h"
#include"CollisionManager.h"
#include"Wood.h"

/// <summary>
/// コンストラクタ
/// </summary>
Wood::Wood()
{
	Loader* loader = loader->GetInstance();

	modelHandle = loader->GetHandle(Loader::Kind::WoodModel);

	collisionManager = collisionManager->GetInstance();

	//衝突後の処理を設定
	capsule1CollisionData.HitProcess = std::bind(&Wood::OnHitObject, this);
	capsule2CollisionData.HitProcess = std::bind(&Wood::OnHitObject, this);
	collisionManager->AddCollisionData(&capsule1CollisionData);
	collisionManager->AddCollisionData(&capsule2CollisionData);

	RegisterCollisionData();

	//ポジション等反映
	MV1SetScale(modelHandle, VGet(40.0f, 40.0f, 40.0f));
	MV1SetRotationXYZ(modelHandle, VGet(-DX_PI_F / 2, 0.0f, -0.7f));
	MV1SetPosition(modelHandle, drawPosition);

	PolyInit();
}

/// <summary>
/// デストラクタ
/// </summary>
Wood::~Wood()
{
	collisionManager->RemoveCollisionData(&capsule1CollisionData);
	collisionManager->RemoveCollisionData(&capsule2CollisionData);
}

/// <summary>
/// 描画
/// </summary>
void Wood::Draw()
{
	//MV1DrawModel(modelHandle);
	//DrawPolygon3D(vertex.data(), polygonList.PolygonNum, modelHandle, FALSE);

	for (int i = 0; i < polygonList.PolygonNum; i++)
	{
		DrawLine3D(
			polygonList.Vertexs[polygonList.Polygons[i].VIndex[0]].Position,
			polygonList.Vertexs[polygonList.Polygons[i].VIndex[1]].Position,
			GetColor(255, 255, 0));

		DrawLine3D(
			polygonList.Vertexs[polygonList.Polygons[i].VIndex[1]].Position,
			polygonList.Vertexs[polygonList.Polygons[i].VIndex[2]].Position,
			GetColor(255, 255, 0));

		DrawLine3D(
			polygonList.Vertexs[polygonList.Polygons[i].VIndex[2]].Position,
			polygonList.Vertexs[polygonList.Polygons[i].VIndex[0]].Position,
			GetColor(255, 255, 0));
	}

	//確認用
	//DrawCapsule3D(cap1Start, cap1End, CapsuleRadius, 8, GetColor(127, 127, 0), GetColor(127, 127, 0), FALSE);
	//DrawCapsule3D(cap2Start, cap2End, CapsuleRadius, 8, GetColor(0, 255, 255), GetColor(0, 255, 255), FALSE);
}

/// <summary>
/// 衝突時の処理
/// </summary>
void Wood::OnHitObject()
{

}

/// <summary>
/// 当たり判定情報セット
/// </summary>
void Wood::RegisterCollisionData()
{
	//カプセル1
	capsule1CollisionData.tag = ObjectTag::StageObject;
	capsule1CollisionData.position = cap1pos;
	capsule1CollisionData.startPosition = cap1Start;
	capsule1CollisionData.endPosition = cap1End;
	capsule1CollisionData.radius = CapsuleRadius;
	capsule1CollisionData.moveVec = VGet(0, 0, 0);
	capsule1CollisionData.isCollisionActive = true;

	//カプセル2
	capsule2CollisionData.tag = ObjectTag::StageObject;
	capsule2CollisionData.position = cap2pos;
	capsule2CollisionData.startPosition = cap2Start;
	capsule2CollisionData.endPosition = cap2End;
	capsule2CollisionData.radius = CapsuleRadius;
	capsule2CollisionData.moveVec = VGet(0, 0, 0);
	capsule2CollisionData.isCollisionActive = true;
}

void Wood::PolyInit()
{
	//モデル全体の参照用メッシュを構築
	MV1SetupReferenceMesh(modelHandle, -1, TRUE);
	//参照用メッシュ情報の取得
	polygonList = MV1GetReferenceMesh(modelHandle, -1, TRUE);
}