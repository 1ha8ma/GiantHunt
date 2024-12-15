#pragma once

class PlayerStateProcessBase
{
public:
	PlayerStateProcessBase(int modelHandle);
	virtual ~PlayerStateProcessBase() {};

	//初期化
	virtual void Initialize() abstract;
	//更新
	virtual bool Update(int inputstate, DINPUT_JOYSTATE stickstate,const Camera& camera) abstract;

	//Get,Set
	VECTOR GetmoveVec() { return moveVec; }
	VECTOR GettargetLookDirection() { return targetLookDirection; }

protected:
	//アニメーション番号
	enum PlayerAnimationNumber
	{
		Run,			//走る
		Jump,			//ジャンプ
		NormalAttack,	//通常攻撃
		Climb,			//登り
	};
	
	//アニメーション再生
	void PlayAnimation(float playSpeed,bool stop);
	//アニメーション再生(1回のみ)
	bool PlayAnimationOnce(float playSpeed);
	//アニメーション逆再生
	bool ReversePlaybackAnimation(float playSpeed, float backPoint);
	//アニメーションの終了
	void DetachAnimation(int attachIndex);

	//モデル・アニメーション
	int modelHandle;			//モデルハンドル
	int nowPlayAnim;			//再生中のアニメーション
	float animTotalTime;		//アニメーションの総再生時間
	float nowAnimPlayTime;		//現在のアニメーション再生時間

	//移動
	VECTOR moveVec;				//移動ベクトル
	VECTOR targetLookDirection;	//目標角度
};