#pragma once
#include<vector>

class EnemyParts;
class ArmEnemyMove;

class ArmEnemy
{
public:
	ArmEnemy();
	~ArmEnemy();

	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	void Draw();

	VECTOR GetPosition() { return position; }
private:
	//フレーム番号
	enum class ArmEnemyFrameIndex :int
	{
		Upperarm = 16,	//上腕
		Forearm,	//前腕
		Hand,		//手
	};

	const int StartHP = 1000;		//開始時HP
	const float ModelScale = 40.0f;	//モデルの描画サイズ

	ArmEnemyMove* armEnemyMove;

	//ステータス
	int HP;

	std::vector<EnemyParts*> parts;				//パーツ
	int modelHandle;							//モデルハンドル
	VECTOR position;							//描画ポジション
	int playerRidePlace;	//プレイヤーが乗っている場所
};