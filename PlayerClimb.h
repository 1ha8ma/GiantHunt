#pragma once
#include"PlayerStateProcessBase.h"
#include"Calculation.h"

class Calculation;

class PlayerClimb :public PlayerStateProcessBase
{
public:
	PlayerClimb(int modelHandle,VECTOR lookDir);
	~PlayerClimb()override;

	//初期化
	void Initialize()override;
	//更新
	bool Update(UsePlayerData playerData, const Camera& camera, CollisionData objectCollision)override;

	void Draw()override;

private:
	const float RotateSpeed = 0.01f;	//回転速度

	//動き
	void Move(UsePlayerData playerData, Camera camera,CollisionData objectData);

	//入力からのmoveVec作成
	void MoveVecForInput(UsePlayerData playerData, VECTOR normVec);

	//回転行列更新
	void UpdateRotateMatrix(VECTOR newLookDirection, VECTOR prevLookDirection,VECTOR normVec);

	//近いポリゴンを見つけ、情報を取る
	int NearPolygon(const CollisionData objectData);

	//入力された情報をポリゴンの平面に映す
	VECTOR ProjectOnPlane(VECTOR inputDir, VECTOR polygonNormal);

	//他クラス
	Calculation* calculation;

	//変数
	float Speed;			//移動速度
	bool stopAnimation;		//アニメーション停止フラグ

	//確認用
	VECTOR nearPolygonCenter;
	VECTOR playerPosition;
};