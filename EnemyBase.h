#pragma once

class EnemyBase
{
public:
	EnemyBase() {};
	virtual ~EnemyBase() {};

	virtual void Initialize()abstract;
	virtual bool Update(VECTOR playerPos, Camera* camera)abstract;
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