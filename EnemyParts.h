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

	//オブジェクトに衝突した時の処理
	void OnHitObject(CollisionData hitObjectData);
	//ダメージを渡す
	int TakeDamage() { return damage; }
	//moveVec計算
	void CalculationMoveVec();

	//Get.Set
	bool GetIsPlayerRide() { return isPlayerRide; }

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
	ObjectTag tag;						//場所のタグ
	VECTOR capsuleStart;				//カプセル始点
	VECTOR capsuleEnd;					//カプセル終点
	float capsuleRadius;				//カプセル半径
	bool isPlayerRide;					//プレイヤーが乗っているか
	int damage;							//与えるダメージ
	VECTOR movePrevPos;					//動く前のポジション
	VECTOR moveAfterPos;				//動いた後のポジション
	VECTOR moveVec;						//動く前と後での差

	//弱点の場合
	bool hitWeakPointEffectflg;			//弱点ヒットエフェクトフラグ
	int hitWeakPointEffectflame;		//弱点ヒットエフェクトフレーム
};