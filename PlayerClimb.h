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

	//旧移動処理
	void MoveCapsule(UsePlayerData playerData, Camera camera, CollisionData objectCollision);
	//
	void MoveMesh(UsePlayerData playerData, Camera camera,CollisionData objectData);

	//角度計算
	void CalculationAngle(VECTOR playerPosition, VECTOR objectPosition);

	//他クラス
	Calculation* calculation;

	//変数
	float Speed;			//移動速度
	bool stopanimflg;		//アニメーション停止フラグ
	float rotateY;			//球に着いている時
	float rotateH;			
};