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
	virtual bool Update(VECTOR position, float angle, int inputstate, DINPUT_JOYSTATE stickstate, const Camera& camera, CollisionData objectCollision) abstract;

	/// <summary>
	/// 描画(確認用)
	/// </summary>
	virtual void Draw() {};

	//走っている場所
	enum class RunPlaceKind :int
	{
		air,		//空中
		ground,		//地面上
		capsule,	//カプセル上
	};

	//Get,Set
	VECTOR GetmoveVec() { return moveVec; }
	VECTOR GettargetLookDirection() { return targetLookDirection; }
	void SetRunPlace(RunPlaceKind place) { runPlace = place; }
	//登り用
	void SetCapsule(VECTOR capsuleStart, VECTOR capsuleEnd, float radius) { playerCapsuleStart = capsuleStart; playerCapsuleEnd = capsuleEnd; playerCapsuleRadius = radius; }

protected:
	//アニメーション番号
	enum PlayerAnimationNumber
	{
		Run,			//走る
		Jump,			//ジャンプ
		NormalAttack,	//通常攻撃
		Climb,			//登り
		Squat,			//しゃがみ
	};

	//フレーム番号
	enum PlayerFrameNumber
	{
		RightArmFrameNumber = 45,	//右腕のフレーム番号
		RightHandFrameNumber = 50,	//右手のフレーム番号(小指)
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
	RunPlaceKind runPlace;		//走っている場所　false:地面 true:カプセル上

	//登り用
	VECTOR playerCapsuleStart;
	VECTOR playerCapsuleEnd;
	float playerCapsuleRadius;
};