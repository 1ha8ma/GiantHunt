#pragma once
#include"CollisionData.h"
#include<vector>

class CollisionManager final
{
public:
	virtual ~CollisionManager();

	//初期化
	void Initialize();
	//更新
	void Update();

	//インスタンスゲット
	static CollisionManager* GetInstance();

	//インスタンス削除
	static void DeleteInstance();

	//当たり判定情報追加
	static void AddCollisionData(CollisionData* data);

	static void RemoveCollisionData(CollisionData* data);

private:
	CollisionManager();

	static CollisionManager* collisionManager;				//インスタンス

	static std::vector<CollisionData*> collisionDataList;	//当たり判定情報リスト

	//カプセルどうしの当たり判定
	bool CapsuleWithCapsule(VECTOR capsuleStart1, VECTOR capsuleEnd1, float capsuleRadius1, VECTOR capsuleStart2, VECTOR capsuleEnd2, float capsuleRadius2);
};