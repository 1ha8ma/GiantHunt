#pragma once
#include"CollisionData.h"

class CollisionManager;
class Effect;
class SoundEffect;

class EnemyParts
{
public:
	EnemyParts(ObjectTag tag, int modelHandle,int frameIndex1,int frameIndex2,float capsuleRadius);
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
	const int PlayHitWeakPointEffectFlame = 300;

	//当たり判定情報更新
	void UpdateCollisionData();

	Effect* effect;
	SoundEffect* se;
	CollisionManager* collisionManager;
	CollisionData collisionData;

	int modelHandle;					//モデルハンドル
	int frameIndex1;						//フレーム番号
	int frameIndex2;				//カプセルの元になるフレーム
	ObjectTag tag;						//場所のタグ
	VECTOR capsuleStart;				//カプセル始点
	VECTOR capsuleEnd;					//カプセル終点
	float capsuleRadius;				//カプセル半径
	bool isPlayerRide;					//プレイヤーが乗っているか
	int damage;							//与えるダメージ

	//弱点の場合
	bool hitWeakPointEffectflg;			//弱点ヒットエフェクトフラグ
	int hitWeakPointEffectflame;		//弱点ヒットエフェクトフレーム
};