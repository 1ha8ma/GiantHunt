#pragma once
#include"PlayerStateProcessBase.h"
#include"Calculation.h"

class PlayerClimb :public PlayerStateProcessBase
{
public:
	PlayerClimb(int modelHandle,VECTOR lookDir);
	~PlayerClimb()override;

	//初期化
	void Initialize()override;
	//更新
	bool Update(UsePlayerData playerData, const Camera& camera,CollisionData objectCollision)override;

private:
	const float RotateSpeed = 0.01f;	//回転速度
	const float Speed = 5.0f;			//移動速度

	//移動処理
	void Move(UsePlayerData playerData, Camera camera, CollisionData objectCollision);

	//角度計算
	void CalculationAngle(VECTOR playerPosition, VECTOR objectPosition);

	//他クラス
	Calculation* calculation;

	bool stopanimflg;		//アニメーション停止フラグ
	float rotateY;			//球に着いている時
	float rotateH;			
};