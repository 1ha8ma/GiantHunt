#pragma once
#include"PlayerStateProcessBase.h"

class PlayerNormalAttack:public PlayerStateProcessBase
{
public:
	PlayerNormalAttack(int modelHandle,VECTOR prevtargetLookDirection);
	~PlayerNormalAttack()override;

	//初期化
	void Initialize()override;
	//更新
	bool Update(int inputstate, DINPUT_JOYSTATE stickstate, const Camera& camera)override;

private:
	bool stateChangeflg;	//ステート変更フラグ
	bool animEndflg;		//アニメーション終了
};