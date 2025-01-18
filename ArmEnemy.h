#pragma once
#include<vector>
#include"EnemyBase.h"

class EnemyParts;
class ArmEnemyMoveBase;
class Calculation;

class ArmEnemy:public EnemyBase
{
public:
	ArmEnemy();
	~ArmEnemy();

	//初期化
	void Initialize()override;
	//更新
	bool Update(VECTOR playerPos, Camera* camera)override;
	//描画
	void Draw()override;

private:
	//乗っている場所
	enum class RidePlace :int
	{
		None,		//乗っていない
		Upperarm,	//上腕
		Forearm,	//前腕
		Hand,		//手
	};

	//動きの種類
	enum class MoveKind :int
	{
		Idle,		//待機
		MowingDown,	//薙ぎ払い
		Swing,		//振り回し
	};

	const int StartHP = 1000;		//開始時HP
	const float ModelScale = 40.0f;	//モデルの描画サイズ

	void ChangeMove(VECTOR playerPos);

	ArmEnemyMoveBase* move;
	Calculation* calclation;

	std::vector<EnemyParts*> parts;			//パーツ
	RidePlace playerRidePlace;				//プレイヤーが乗っている場所
	bool moveChangeflg;						//状態からの動き変更指示フラグ
	MoveKind nowMoveKind;					//現在の動きの種類
	int playerRideFlame;					//プレイヤーが乗っている時間
	bool playerRideflg;						//プレイヤーが乗っているフラグ
	bool swingflg;							//振り回しフラグ
};