#pragma once
#include<vector>

class EnemyParts;
class ArmEnemyMoveBase;
class Calculation;

class ArmEnemy
{
public:
	ArmEnemy();
	~ArmEnemy();

	//初期化
	void Initialize();
	//更新
	void Update(VECTOR playerPos,Camera* camera);
	//描画
	void Draw();

	VECTOR GetPosition() { return position; }
	VECTOR GetTargetCameraPosition() { return targetCameraPosition; }
	int GetHP() { return HP; }
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

	//ステータス
	int HP;

	std::vector<EnemyParts*> parts;			//パーツ
	int modelHandle;						//モデルハンドル
	VECTOR position;						//描画ポジション
	RidePlace playerRidePlace;				//プレイヤーが乗っている場所
	VECTOR targetCameraPosition;			//ターゲットカメラ用ポジション
	bool moveChangeflg;						//状態からの動き変更指示フラグ
	MoveKind nowMoveKind;					//現在の動きの種類
	int playerRideFlame;					//プレイヤーが乗っている時間
	bool playerRideflg;//プレイヤーが乗っているフラグ
	bool swingflg;							//振り回しフラグ
};