#pragma once
#include<functional>
#include"DxLib.h"

//オブジェクトの種類
enum class ObjectTag :int
{
	//プレイヤー
	Player,
	Attack_P,

	//腕の敵
	Upperarm_E1,	  //上腕
	Forearm_E1,		  //前腕
	Hand_E1,			//手
	Attack_E1,			//攻撃

	//巨人
	LeftArm_E2,			//左腕
	RightArm_E2,		//右腕
	LeftLeg_E2,			//左足
	RightLeg_E2,		//右足
	Body_E2,			//胴体
	Head_E2,			//頭
	Attack_E2,			//攻撃

	//木
	Wood1,				//上
	Wood2,				//下
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

	//攻撃力
	int attackPower;

	std::function<void(CollisionData)> HitProcess;   //当たった時に行われる処理
	bool isCollisionActive;						//当たり判定を適用させたいかどうか
};