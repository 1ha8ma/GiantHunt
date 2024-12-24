#pragma once

class PlayerStateProcessBase
{
public:
	PlayerStateProcessBase(int modelHandle);
	virtual ~PlayerStateProcessBase() {};

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize() abstract;
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="inputstate">ボタン入力状態</param>
	/// <param name="stickstate">スティック入力情報</param>
	/// <param name="camera">カメラ</param>
	/// <returns>ステートからのステート変更指示</returns>
	virtual bool Update(int inputstate, DINPUT_JOYSTATE stickstate,const Camera& camera,VECTOR objectCapsuleStart,VECTOR objectCapsuleEnd) abstract;

	//Get,Set
	VECTOR GetmoveVec() { return moveVec; }
	VECTOR GettargetLookDirection() { return targetLookDirection; }
	void SetRunPlace(bool place) { runPlace = place; }

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
	bool runPlace;				//走っている場所　false:地面 true:カプセル上
};