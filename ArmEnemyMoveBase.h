#pragma once
#include"Camera.h"

class ArmEnemyMoveBase
{
public:
	//フレーム番号
	enum class ArmEnemyFrameIndex :int
	{
		Upperarm = 16,	//上腕
		Forearm = 18,	//前腕
		Hand = 30,		//手(中指第二関節)
		Finger1 = 22,	//親指
		Finger2 = 40,	//小指の先
	};

	ArmEnemyMoveBase(int modelHandle,float modelScale);
	virtual ~ArmEnemyMoveBase() {};
	
	virtual bool Update(Camera* camera) { return false; }
	virtual bool UpdateFallDown(Camera* camera) { return false; }
	virtual void Draw()abstract;	//確認用


	VECTOR GetRotate() { return rotate; }

protected:
	//フレームの回転処理
	MATRIX FrameRotateProcess(int frameIndex, float Xaxis, float Yaxis, float Zaxis);

	int modelHandle;	//モデルハンドル
	float modelScale;	//モデルのサイズ
	VECTOR rotate;		//回転用
	int moveState;		//動き状態
};