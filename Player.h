#pragma once

class Input;

class Player
{
public:
	Player();
	~Player();
	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	void Draw();

	VECTOR GetPosition() { return position; }
	float GetAngle() { return angle; }

private:
	//状態
	enum State
	{
		Run,		//走る
		Attack,		//攻撃
		Climb,		//登り
		Hanging,	//ぶら下がり
	};

	//パーツの種類
	enum PartsKind
	{
		LeftArm,
		RightArm,
		LeftLeg,
		RightLeg,
		Body,
		Head,
	};

	const float AngleSpeed = 0.02f;  //角度変更速度
	const float Speed = 10.0f;      //スピード

	//CollisionData collisiondata;//当たり判定情報
	Input* input;

	void Move();
	void UpdateAngle();

	int modelHandle;				//モデルハンドル
	VECTOR position;				//ポジション
	float angle;					//角度
	VECTOR moveVec;					//移動量
	VECTOR targetLookDirection;		//モデルの向く目標方向
};