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

//メッシュデータ
struct MeshData
{
	//オブジェクトタグ
	ObjectTag tag;										
	//メッシュ情報
	MV1_REF_POLYGONLIST polygonList;					//ポリゴンリスト
};

//当たり判定情報
struct CollisionData
{
	//タグ
	ObjectTag tag;
	
	//中心
	VECTOR position;

	//カプセル(メッシュ毎の前にカプセルで大まかに判定して、全てのオブジェクトとメッシュ判定するのを防ぐため)
	VECTOR startPosition;								//カプセル始点
	VECTOR endPosition;									//カプセル終点
	float radius;										//カプセル半径

	//メッシュ情報
	MeshData meshData;

	//動いた量
	VECTOR moveVec;										//動くカプセル用

	//四角ステージ用(ポジション)
	float stageLeft;									//右(x+)
	float stageRight;									//左(x-)
	float stageFront;									//前(z+)
	float stageBack;									//後(z-)

	//攻撃力
	int attackPower;

	std::function<void(CollisionData*)> HitProcess;		//当たった時に行われる処理
	std::function<void(VECTOR)> WallHitProcess;			//ステージ壁衝突時の処理
	bool isCollisionActive;								//当たり判定を適用させたいかどうか
};
