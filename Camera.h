#pragma once

class Input;

class Camera
{
public:
	Camera();

	//初期化
	void Initialize(VECTOR playerpos);
	//更新
	void Update(VECTOR playerPosition,float lookAngle,VECTOR enemyPosition);

	float GetangleH() { return angleH; }
	float GetangleV() { return angleV; }
	VECTOR GetLookPosition() { return lookPosition; }
	VECTOR GetPosition() { return position; }

private:
	const float AngleSpeed = 0.03f;					//旋回角度
	const float CameraPlayerTargetHeight = 100.0f;	//プレイヤーのどれだけ高いところを見るか
	const float PlayerDistance = 300;				//プレイヤーとの距離
	const float CollisionSize = 50.0f;				//カメラの当たり判定サイズ

	//他クラス
	Input* input;

	VECTOR position;		//ポジション
	VECTOR lookPosition;	//注視点
	float angleH;			//平面角度
	float angleV;			//垂直角度
	VECTOR lookTargetPos;	//目標の注視点座標
	float t;				//Lerp用
	bool lerpflg;			//Lerp開始フラグ
};