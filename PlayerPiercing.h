#pragma once
#include"PlayerStateProcessBase.h"

class CollisionManager;
struct CollisionData;

/// <summary>
/// 突き刺し攻撃
/// </summary>
class PlayerPiercing :public PlayerStateProcessBase
{
public:
	PlayerPiercing(int modelHandle, VECTOR prevtargetLookDirection);
	~PlayerPiercing();

	void Initialize()override {};
	bool Update(VECTOR position,float angle, int inputstate, DINPUT_JOYSTATE stickstate, const Camera& camera, CollisionData objectCollision) override;
	void Draw()override;

private:
	const int LowestAttackPower = 30;		//最低攻撃力
	const float AttackCapsuleRadius = 20;	//攻撃カプセル半径
	const float MaxSwingUp = 1.3f;			//最大振り上げ地点
	const float SwingUpSpeed = 0.01f;		//振り上げ速度
	const float SwingDownSpeed = 0.5f;		//振り下ろし速度

	//当たり判定情報更新
	void UpdateCollisionData();
	//突き刺し攻撃
	void PiercingAttack(int inputstate);
	//衝突後処理
	void OnHitObject(CollisionData objectData);

	CollisionManager* collisionManager;
	CollisionData attackCollisionData;	//攻撃当たり判定情報

	bool canInputX;					//Xボタン連続入力防止フラグ
	bool changeState;				//ステート変更
	VECTOR attackCapsuleStart;		//攻撃カプセル始点
	VECTOR attackCapsuleEnd;		//攻撃カプセル終点
	int attackPower;				//攻撃力
	int attackChargeFlame;			//攻撃貯め時間
	bool attack;					//攻撃中
	bool attackEnd;					//攻撃終了
	bool attackHit;

	VECTOR rotate;
};