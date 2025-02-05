#pragma once
#include"PlayerStateProcessBase.h"
#include"CollisionData.h"
#include"CollisionManager.h"

class Input;
class Camera;

class Player
{
public:
	Player();
	~Player();

	//スタートシーン初期化
	void InitializeStartScene();
	//スタートシーン終了処理
	void StartSceneEnd() { delete nowstate; }

	//ゲーム初期化
	void InitializeGame();
	//ゲーム更新
	bool UpdateGame(Camera* camera);

	//ゲームオーバーシーン初期化
	void InitializeGameOver();
	//ゲームオーバーシーン更新
	void UpdateGameOver();
	//描画
	void Draw();

	//衝突した時の処理
	void BodyOnHitObject(CollisionData* hitObjectData);
	void FootOnHitObject(CollisionData* hitObjectData);
	//壁衝突時の処理
	void WallHitProcess(VECTOR sinkIntoDepth);

	//GetSet
	VECTOR GetPosition() { return position; }
	float GetAngle() { return angle; }
	int GetHP() { return HP; }
	int GetGripPoint() { return gripPoint; }
	float GetCameraZoom() { return cameraZoom; }
	float GetPiercingArmRotateZ() { return piercingArmRotateZ; }
	bool GetOnPiercingGauge() { return onPiercingGauge; }

private:
	//状態
	enum class State :int
	{
		Idle,			//待機
		Run,			//走る
		Jump,			//ジャンプ
		NormalAttack,	//通常攻撃
		Climb,			//登り
		Squat,			//しゃがみ
		Piercing,		//突き刺し攻撃
		FallDown,		//倒れる(負けた時)
		Falling,		//落下
	};

	const float AngleSpeed = 0.2f;					//角度変更速度
	const float WholeBodyCapsuleRadius = 50.0f;		//全身カプセル半径
	const float WholeBodyCapsuleLength = 50.0f;		//カプセルの長さ
	const float FootCapsuleRadius = 20.0f;			//足カプセル半径
	const float Gravity = 0.5f;						//重力
	const int MaxHP = 100;							//最大HP
	const int MaxGripPoint = 600;					//最大握力
	const int MinusGripPoint = 1;					//減らす握力量

	//角度更新
	void UpdateAngle();
	//ステート変更
	void ChangeState();
	//足がついているか確認
	void CheckOnGround(Camera* camera);
	//カプセル更新
	void UpdateCapsule();
	//当たり判定情報更新
	void UpdateCollisionData();
	//描画位置修正
	void CorrectionDrawPosition();
	//押し戻し
	void CollisionPushBack(CollisionData partsData,CollisionData hitCollisionData);
	//連続入力防止
	void PreventionContinuousInput();
	//動きに使う構造体の中身のセット
	void MoveUseDataSet();
	
	//他クラス
	PlayerStateProcessBase* nowstate;
	Input* input;
	CollisionManager* collisionManager;
	CollisionData bodyCollisionData;
	CollisionData footCollisionData;
	CollisionData hitObjectData;
	CollisionData* hitObjectDataPointer;
	PlayerStateProcessBase::UsePlayerData moveUseData;	//動きに使うデータ構造体

	//ステータス
	int HP;				//体力
	int gripPoint;		//握力ゲージ

	//入力
	int inputstate;									//入力情報
	DINPUT_JOYSTATE stickstate;						//スティック入力情報
	bool canInputX;									//攻撃連続入力防止

	//モデル関係
	int modelHandle;								//モデルハンドル
	VECTOR drawPosition;							//描画用ポジション

	//当たり判定
	VECTOR position;								//ポジション
	VECTOR wholebodyCapStart;						//カプセル始点(上)
	VECTOR wholebodyCapEnd;							//カプセル終点(下)
	VECTOR footCapStart;							//足カプセル
	VECTOR footCapEnd;								//足カプセル

	//移動関係
	float angle;									//プレイヤーの向き
	VECTOR moveVec;									//移動量
	VECTOR targetLookDirection;						//モデルの向く目標方向
	bool jumpAfterLeaveFoot;						//ジャンプした後に足が離れた
	bool onGround;									//足がついているか
	bool onFootObject;								//足がオブジェクトに着いている
	bool isCatch;									//掴める状態か
	PlayerStateProcessBase::RunPlaceKind runPlace;	//走っている場所

	//動き関係
	State nowstateKind;								//現在の状態
	bool changeStateflg;							//状態からの状態変更指示がある場合

	//落下
	float fallSpeed;								//落下速度
	int fallFrame;									//落下時間

	//突き刺し攻撃時
	float cameraZoom;								//カメラのズーム
	float piercingArmRotateZ;						//腕の回転度
	bool onPiercingGauge;							//突き刺し攻撃ゲージ表示

	//登り時
	VECTOR putCloseVec;								//オブジェクトと離れている分近づけるベクトル


	//その他
	bool gameOverflg;								//ゲームオーバーフラグ
};