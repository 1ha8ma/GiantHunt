#pragma once
#include<functional>
#include"DxLib.h"

//オブジェクトの種類
enum class ObjectTag :int
{
	//ステージ
	Stage,

	//プレイヤー
	PlayerWholeBody,	//全身
	PlayerFoot,			//足
	Attack_P,			//攻撃

	//敵
	EnemyParts,			//敵のパーツ
	EnemyAttack,		//敵の攻撃
	WeakPoint,			//敵の弱点

	//木
	StageObject,
};

//当たり判定情報
struct CollisionData
{
	//タグ
	ObjectTag tag;
	
	//中心
	VECTOR position;

	//カプセル用
	VECTOR startPosition;   //カプセル始点
	VECTOR endPosition;     //カプセル終点
	float radius;           //カプセル半径

	//動いた量
	VECTOR moveVec;			//動くカプセル用

	//四角ステージ用(ポジション)
	float stageLeft;
	float stageRight;
	float stageFront;
	float stageBack;

	//攻撃力
	int attackPower;

	std::function<void(CollisionData*)> HitProcess;		//当たった時に行われる処理
	std::function<void(VECTOR)> WallHitProcess;			//ステージ壁衝突時の処理
	bool isCollisionActive;								//当たり判定を適用させたいかどうか
};