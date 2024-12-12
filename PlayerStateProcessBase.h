#pragma once

class PlayerStateProcessBase
{
public:
	PlayerStateProcessBase(int modelHandle);
	virtual ~PlayerStateProcessBase() {};

	//初期化
	virtual void Initialize() abstract;
	//更新
	virtual PlayerStateProcessBase* Update(const Camera& camera) abstract;

	//NOTE:確認のためだけ別にいらない
	virtual void Draw()abstract;

	//Get,Set
	VECTOR GetmoveVec() { return moveVec; }
	VECTOR GettargetLookDirection() { return targetLookDirection; }

protected:
	//アニメーション番号
	enum PlayerAnimationNumber
	{
		Run,
	};
	
	//アニメーション再生
	void PlayAnimation(float playSpeed,bool stop);
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