#pragma once
#include"CollisionData.h"

class CollisionManager;
class Effect;
class SoundEffect;

class WeakPoint
{
public:
	WeakPoint(int modelHandle, int frameIndex1, int frameIndex2, float capsuleRadius);
	~WeakPoint();

	void Initialize();
	void Update();
	void Draw();

	//オブジェクトに衝突した時の処理
	void OnHitObject(CollisionData* hitObjectData);
	//ダメージを渡す
	int TakeDamage() { return damage; }

private:
	const int PlayHitWeakPointEffectFlame = 300;	//弱点ヒットエフェクトの再生時間
	const int WeakPointDamageMultiplier = 2;		//弱点のダメージ倍率

	//当たり判定情報更新
	void UpdateCollisionData();

	Effect* effect;
	SoundEffect* se;
	CollisionManager* collisionManager;
	CollisionData collisionData;

	int modelHandle;					//モデルハンドル
	int frameIndex1;					//フレーム番号1
	int frameIndex2;					//フレーム番号2   1と2の座標からカプセルを作る
	ObjectTag tag;						//タグ
	VECTOR capsuleStart;				//カプセル始点
	VECTOR capsuleEnd;					//カプセル終点
	float capsuleRadius;				//カプセル半径
	int damage;							//与えるダメージ
	
	//弱点の場合
	bool hitWeakPointEffectflg;			//弱点ヒットエフェクトフラグ
	int hitWeakPointEffectflame;		//弱点ヒットエフェクトフレーム
};