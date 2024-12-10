#pragma once
#include<functional>
#include"DxLib.h"

struct CapsuleCollisionData;

class HitObjectAddress
{

};

//オブジェクトの種類
enum ObjectTag
{
	//プレイヤー
	LeftArm_P,		  //左腕
	RightArm_P,		  //右腕
	LeftLeg_P,        //左足
	RightLeg_P,       //右足
	Body_P,           //胴体
	Head_P,           //頭
	Attack_P,         //攻撃

	//腕の敵
	Upperarm_E1,	  //上腕
	Forearm_E1,		  //前腕
	Hand_E1,		  //手
	Attack_E1,		  //攻撃

	//巨人
	LeftArm_E2,		  //左腕
	RightArm_E2,	  //右腕
	LeftLeg_E2,		  //左足
	RightLeg_E2,	  //右足
	Body_E2,		  //胴体
	Head_E2,		  //頭
	Attack_E2,		  //攻撃
};

//当たり判定情報
struct CollisionData
{
	//タグ
	ObjectTag tag;
	
	//カプセル用
	VECTOR startPosition;   //カプセル始点
	VECTOR endPosition;     //カプセル終点
	float radius;           //カプセル半径

	//インタラクト
	float interactRadius;     //そのオブジェクトにアクセス出来る範囲
	int interactionCost;      //そのオブジェクトのインタラクトにかかるコスト
	bool isInteracted;        //インタラクトを行ったかどうか

	std::function<void(CollisionData)> onHit;   //当たった時に行われる処理
	bool isCollisionActive;						//当たり判定を適用させたいかどうか

	HitObjectAddress* objectAddress;
};