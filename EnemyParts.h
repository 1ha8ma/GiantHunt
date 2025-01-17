#pragma once
#include"CollisionData.h"

class CollisionManager;
class Effect;

class EnemyParts
{
public:
	EnemyParts(ObjectTag tag, int modelHandle,int frameIndex,int formerFrameIndex,float capsuleRadius);
	~EnemyParts();

	void Initialize();
	void Update();
	void Draw();

	void OnHitObject(CollisionData hitObjectData);

	//ダメージを渡す
	int TakeDamage() { return damage; }

	//Get.Set
	bool GetIsPlayerRide() { return isPlayerRide; }

private:
	void UpdateCollisionData();

	Effect* effect;
	CollisionManager* collisionManager;
	CollisionData collisionData;

	int modelHandle;			//モデルハンドル
	int frameIndex;				//フレーム番号
	int formerFrameIndex;		//カプセルの元になるフレーム
	ObjectTag tag;				//場所のタグ
	VECTOR capsuleStart;		//カプセル始点
	VECTOR capsuleEnd;			//カプセル終点
	float capsuleRadius;		//カプセル半径
	bool isPlayerRide;			//プレイヤーが乗っているか
	int damage;					//与えるダメージ
};