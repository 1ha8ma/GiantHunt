#include"DxLib.h"
//#include"CollisionData.h"
#include"CollisionManager.h"

//初期化
CollisionManager* CollisionManager::collisionManager = nullptr;
std::vector<CollisionData*> CollisionManager::collisionDataList;

/// <summary>
/// コンストラクタ
/// </summary>
CollisionManager::CollisionManager()
{

}

/// <summary>
/// デストラクタ
/// </summary>
CollisionManager::~CollisionManager()
{
	collisionDataList.clear();
}

/// <summary>
/// 初期化
/// </summary>
void CollisionManager::Initialize()
{

}

/// <summary>
/// インスタンスゲット
/// </summary>
/// <returns>インスタンス</returns>
CollisionManager* CollisionManager::GetInstance()
{
	if (collisionManager == nullptr)
	{
		collisionManager = new CollisionManager();
	}

	return collisionManager;
}

/// <summary>
/// 当たり判定情報追加
/// </summary>
/// <param name="data">データ</param>
void CollisionManager::AddCollisionData(CollisionData* data)
{
	collisionDataList.push_back(data);
}

/// <summary>
/// 全ての当たり判定処理
/// </summary>
void CollisionManager::Update()
{
	for (int i = 0; i < collisionDataList.size(); i++)
	{
		for (int j = 0; j < collisionDataList.size(); j++)
		{
			//同じものだったらスキップ
			if (i == j)
			{
				continue;
			}

			//どのタイプの当たり判定を行うか調べる
			CollisionData data1 = *collisionDataList[i];
			CollisionData data2 = *collisionDataList[j];

			//当たり判定を行って欲しいか確認
			if (data1.isCollisionActive && data2.isCollisionActive)
			{
				//プレイヤーと木
				if (data1.tag == ObjectTag::Player && data2.tag == ObjectTag::Wood1 || data1.tag == ObjectTag::Player && data2.tag == ObjectTag::Wood2)
				{
					bool hit = CapsuleWithCapsule(data1.startPosition, data1.endPosition, data1.radius, data2.startPosition, data2.endPosition, data2.radius);

					if (hit)
					{
						data1.HitProcess(data2);
						data2.HitProcess(data1);
					}
				}
			}
		}
	}
}

/// <summary>
/// カプセルどうしの当たり判定
/// </summary>
/// <param name="capsuleStart1">カプセル1始点</param>
/// <param name="capsuleEnd1">カプセル1終点</param>
/// <param name="capsuleRadius1">カプセル1半径</param>
/// <param name="capsuleStart2">カプセル2始点</param>
/// <param name="capsuleEnd2">カプセル2終点</param>
/// <param name="capsuleRadius2">カプセル2半径</param>
/// <returns>当たっているか</returns>
bool CollisionManager::CapsuleWithCapsule(VECTOR capsuleStart1, VECTOR capsuleEnd1, float capsuleRadius1, VECTOR capsuleStart2, VECTOR capsuleEnd2, float capsuleRadius2)
{
	bool hit = false;

	//カプセル間の最短距離
	float length = Segment_Segment_MinLength(capsuleStart1, capsuleEnd1, capsuleStart2, capsuleEnd2);

	//判定
	if (length < capsuleRadius1 + capsuleRadius2)
	{
		hit = true;
	}

	return hit;
}