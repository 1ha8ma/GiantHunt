#pragma once
#include"PlayerStateProcessBase.h"

class PlayerClimb :public PlayerStateProcessBase
{
public:
	PlayerClimb(int modelHandle,VECTOR lookDir);
	~PlayerClimb()override;

	//初期化
	void Initialize()override;
	//更新
	bool Update(int inputstate, DINPUT_JOYSTATE stickstate, const Camera& camera, VECTOR objectCapsuleStart, VECTOR objectCapsuleEnd)override;

private:
	//移動処理
	void Move(DINPUT_JOYSTATE stickstate, Camera camera);

	//登っているオブジェクトのカプセル
	VECTOR climbCapStart;
	VECTOR climbCapEnd;

	bool moveflg;		//移動中
};