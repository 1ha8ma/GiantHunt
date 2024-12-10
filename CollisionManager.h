#pragma once
#include<vector>

class CollisionManager final
{
public:
	virtual ~CollisionManager();

	//初期化
	void Initialize();
	//更新
	void Update();

	//インスタンス作製
	static void CreateInstance();

	//インスタンスゲット
	static CollisionManager* GetInstance();

	//インスタンス削除
	static void DeleteInstance();

	//当たり判定情報読み込み
	static void RegisterCollisionData(CollisionData data);

private:
	CollisionManager();

	static CollisionManager* collisionmanager;//インスタンス
	
	std::vector<CapsuleCollisionData*> capsuleCollisionData;//カプセルの当たり判定を行うリスト

	//カプセルどうしの当たり判定
	bool CapsuleWithCapsule(VECTOR capsuleStart1, VECTOR capsuleEnd1, float capsuleRadius1, VECTOR capsuleStart2, VECTOR capsuleEnd2, float capsuleRadius2);
};