#pragma once

class PlayerStateProcessBase;
class Input;

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
		Run,			//走る
		Jump,			//ジャンプ
		NormalAttack,	//通常攻撃
		ThrustAttack,	//突き刺し攻撃
		Climb,			//登り
		Hanging,		//ぶら下がり
		Roll,			//転げる
	};

	const float AngleSpeed = 0.2f;  //角度変更速度
	const float Speed = 10.0f;      //スピード

	//角度更新
	void UpdateAngle();
	//ステート変更
	void ChangeState();
	//足がついているか確認
	void CheckOnGround();

	//他クラス
	PlayerStateProcessBase* nowstate;
	Input* input;

	//ステータス
	int HP;				//体力
	int gripPoint;		//握力ゲージ

	//入力
	int inputstate;					//入力情報
	DINPUT_JOYSTATE stickstate;		//スティック入力情報

	int modelHandle;				//モデルハンドル
	VECTOR position;				//ポジション
	float angle;					//角度
	VECTOR moveVec;					//移動量
	VECTOR targetLookDirection;		//モデルの向く目標方向 
	int nowstateKind;				//現在の状態
	bool onGround;					//足がついているか

	bool changeStateflg;			//状態からの状態変更指示がある場合
};