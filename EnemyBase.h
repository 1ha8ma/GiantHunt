#pragma once
#include"Camera.h"

class EnemyBase
{
public:
	EnemyBase() {};
	virtual ~EnemyBase() {};

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize()abstract;

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="playerPos">プレイヤーポジション</param>
	/// <param name="camera">カメラ</param>
	/// <returns>ゲームオーバーか</returns>
	virtual bool Update(VECTOR playerPos, Camera* camera)abstract;

	/// <summary>
	/// 倒された後の初期化
	/// </summary>
	virtual void InitializeFallDown()abstract;

	/// <summary>
	/// 倒された後の更新
	/// </summary>
	/// <param name="camera">カメラ</param>
	/// <returns>動きの終了</returns>
	virtual bool UpdateFallDown(Camera* camera)abstract;

	virtual void Draw()abstract;

	//GetSet
	int GetHP() { return HP; }
	VECTOR GetTargetCameraPosition() { return targetCameraPosition; }

protected:
	//ステータス
	int HP;

	int modelHandle;						//モデルハンドル
	VECTOR position;						//描画ポジション
	VECTOR targetCameraPosition;			//ターゲットカメラ用ポジション
};