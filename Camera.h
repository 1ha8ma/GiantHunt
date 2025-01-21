#pragma once

class Input;
class Calculation;

class Camera
{
public:
	Camera();

	//スタートシーン初期化
	void StartSceneInitialize();
	//スタートシーン更新
	void UpdateStartScene();

	//ゲームシーン初期化
	void GameInitialize(VECTOR playerpos);
	//更新
	void UpdateGame(VECTOR playerPosition,VECTOR targetCameraPosition);

	//ゲームオーバーシーン初期化
	void InitializeGameOver(VECTOR playerPosition);
	//ゲームオーバーシーン更新
	void UpdateGameOver();
	
	//演出
	void PlayShakingVertical(float shakingPower, int shakingDirectionChangeflame, int flame);

	//GetSet
	float GetangleH() { return angleH; }
	float GetangleV() { return angleV; }
	VECTOR GetLookPosition() { return lookPosition; }
	VECTOR GetPosition() { return position; }

private:
	const float AngleSpeed = 0.03f;					//旋回角度
	const float CameraPlayerTargetHeight = 100.0f;	//プレイヤーのどれだけ高いところを見るか
	const float PlayerDistance = 300;				//プレイヤーとの距離
	const float CollisionSize = 50.0f;				//カメラの当たり判定サイズ

	//演出更新
	void UpdateProduction(VECTOR playerPosition);
	//上下揺れ
	void ShakingVertical(VECTOR playerPosition);

	//他クラス
	Input* input;
	Calculation* calculation;

	VECTOR position;		//ポジション
	VECTOR lookPosition;	//注視点
	float angleH;			//平面角度
	float angleV;			//垂直角度
	VECTOR lookTargetPos;	//目標の注視点座標
	float t;				//Lerp用
	bool lerpflg;			//Lerp開始フラグ

	//演出
	bool productionflg;					//演出中フラグ
	int totalflame;						//演出フレーム
	//縦揺れ
	int changeflame;					//切り替えまでのフレーム
	bool shakingDirection;				//揺れる方向フラグ
	bool shakingVerticalflg;			//縦揺れフラグ
	float shakingPower;					//揺れの強さ
	int shakingDirectionChangeflame;	//揺れる方向を変更するフレーム
	int playflame;						//再生時間
};