#pragma once
#include"PlayerStateProcessBase.h"

class Input;
class CollisonManager;
struct CollisionData;

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

	//ポジション反映
	void ReflectPosition();
	//衝突した時の処理
	void OnHitObject(CollisionData hitObjectData);

	//GetSet
	VECTOR GetPosition() { return position; }
	float GetAngle() { return angle; }

private:
	//状態
	enum class State :int
	{
		Run,			//走る
		Jump,			//ジャンプ
		NormalAttack,	//通常攻撃
		ThrustAttack,	//突き刺し攻撃
		Climb,			//登り
		Hanging,		//ぶら下がり
		Roll,			//転げる
	};

	const float AngleSpeed = 0.2f;			//角度変更速度
	const float CapsuleRadius = 50.0f;		//カプセル半径
	const int AttackPower = 100;			//攻撃力
	const float Gravity = 0.5f;				//重力

	//角度更新
	void UpdateAngle();
	//ステート変更
	void ChangeState();
	//足がついているか確認
	void CheckOnGround();
	//カプセル更新
	void UpdateCapsule();
	//当たり判定情報更新
	void UpdateCollisionData();
	//描画位置修正
	void CorrectionDrawPosition();
	//押し戻し
	void CollisionPushBack(CollisionData hitCollisionData);
	
	//他クラス
	PlayerStateProcessBase* nowstate;
	Input* input;
	CollisionManager* collisionManager;
	CollisionData collisionData;

	//ステータス
	int HP;				//体力
	int gripPoint;		//握力ゲージ

	//入力
	int inputstate;									//入力情報
	DINPUT_JOYSTATE stickstate;						//スティック入力情報

	int modelHandle;								//モデルハンドル
	VECTOR position;								//ポジション
	VECTOR drawPosition;							//描画用ポジション
	VECTOR capStart;								//カプセル始点(頭)
	VECTOR capEnd;									//カプセル終点(足)
	float angle;									//描画角度
	VECTOR moveVec;									//移動量
	VECTOR targetLookDirection;						//モデルの向く目標方向 
	State nowstateKind;								//現在の状態
	bool onGround;									//足がついているか
	bool isCatch;									//掴める状態か
	bool isStand;									//立てる状態か
	PlayerStateProcessBase::RunPlaceKind runPlace;	//走っている場所

	float fallSpeed;								//落下速度
	bool changeStateflg;							//状態からの状態変更指示がある場合

	//当たっているオブジェクトのデータ
	VECTOR hitObjectCapStart;
	VECTOR hitObjectCapEnd;
};