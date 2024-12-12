#pragma once

class PlayerStateProcessBase;

class Player
{
public:
	Player();
	~Player();

	//初期化
	void Initialize();
	//更新
	void Update(const Camera& camera);
	//描画
	void Draw();

	//GetSet
	VECTOR GetPosition() { return position; }
	float GetAngle() { return angle; }

private:
	//状態
	enum State
	{
		Run,		//走る
		Attack,		//攻撃
		Jump,		//ジャンプ
		Climb,		//登り
		Hanging,	//ぶら下がり
	};

	const float AngleSpeed = 0.2f;  //角度変更速度
	const float Speed = 10.0f;      //スピード

	//CollisionData collisiondata;//当たり判定情報

	//角度更新
	void UpdateAngle();
	//ステート変更
	void ChangeState();

	//他クラス
	PlayerStateProcessBase* nowstate;
	PlayerStateProcessBase* nextstate;

	//ステータス
	int HP;				//体力
	int gripPoint;		//握力ゲージ

	int modelHandle;				//モデルハンドル
	VECTOR position;				//ポジション
	float angle;					//角度
	VECTOR moveVec;					//移動量
	VECTOR targetLookDirection;		//モデルの向く目標方向 
};