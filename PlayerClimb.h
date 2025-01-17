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
	bool Update(VECTOR position,float angle,int inputstate, DINPUT_JOYSTATE stickstate, const Camera& camera,CollisionData objectCollision)override;

private:
	const float RotateSpeed = 0.01;	//回転速度
	const float Speed = 5;			//移動速度

	//移動処理
	void Move(VECTOR position, DINPUT_JOYSTATE stickstate, Camera camera, CollisionData objectCollision);

	Calculation* calculation;

	//登っているオブジェクトのカプセル
	VECTOR climbCapStart;
	VECTOR climbCapEnd;

	bool stopanimflg;		//アニメーション停止フラグ
};