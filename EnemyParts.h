#pragma once
#include"CollisionData.h"

class CollisionManager;

class EnemyParts
{
public:

	EnemyParts(ObjectTag tag, int modelHandle,int frameIndex,float capsuleLength,float capsuleRadius,VECTOR frameVec);
	~EnemyParts();

	void Initialize();
	void Update();
	void Draw();

	void OnHitObject(CollisionData hitObjectData);

	//Get.Set
	bool GetIsPlayerRid() { return isPlayerRide; }

private:
	void UpdateCollisionData();

	CollisionManager* collisionManager;
	CollisionData collisionData;

	int modelHandle;			//モデルハンドル
	int frameIndex;				//フレーム番号
	float capsuleLength;		//カプセルの長さ
	ObjectTag tag;				//場所のタグ
	VECTOR initFramePosition;	//最初のフレームのポジション
	VECTOR framePosition;		//フレームのポジション
	VECTOR frameVec;			//フレームのベクトル
	VECTOR capsuleStart;		//カプセル始点
	VECTOR capsuleEnd;			//カプセル終点
	float capsuleRadius;		//カプセル半径
	bool isPlayerRide;			//プレイヤーが乗っているか
};