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

	//当たり判定情報追加
	static void AddCollisionData(CollisionData* data);

	//当たり判定情報の取り除き
	static void RemoveCollisionData(CollisionData* data);

	//取りたい当たり判定情報を取る
	static CollisionData GetCollisionData(CollisionData data);

private:
	CollisionManager();

	static CollisionManager* collisionManager;				//インスタンス

	static std::vector<CollisionData*> collisionDataList;	//当たり判定情報リスト

	//カプセルどうしの当たり判定
	bool CapsuleWithCapsule(VECTOR capsuleStart1, VECTOR capsuleEnd1, float capsuleRadius1, VECTOR capsuleStart2, VECTOR capsuleEnd2, float capsuleRadius2);
};