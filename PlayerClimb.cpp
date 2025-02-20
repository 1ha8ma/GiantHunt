#include<fstream>
#include<math.h>
#include"DxLib.h"
#include"nlohmann/json.hpp"
#include"CollisionData.h"
#include"Camera.h"
#include"Input.h"
#include"PlayerClimb.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="modelHandle">モデルハンドル</param>
PlayerClimb::PlayerClimb(int modelHandle,VECTOR lookDir) :PlayerStateProcessBase(modelHandle)
{
	//アニメーションアタッチ
	nowPlayAnim = MV1AttachAnim(modelHandle, PlayerAnimationNumber::Climb);
	//アニメーションの総再生時間を取る
	animTotalTime = MV1GetAnimTotalTime(modelHandle, nowPlayAnim);
	animTotalTime *= 2;

	//ファイル読み込み
	using Json = nlohmann::json;
	Json jsonData;
	std::ifstream ifs("Data/PlayerData.json");
	if (ifs)
	{
		ifs >> jsonData;
	}

	//変数初期化
	calculation = new Calculation();
	stopanimflg = false;
	targetLookDirection = lookDir;
	Speed = jsonData["ClimbMoveSpeed"];
	rotateY = 0.0f;
	rotateH = 0.0f;
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerClimb::~PlayerClimb()
{
	DetachAnimation(nowPlayAnim);
}

/// <summary>
/// 初期化
/// </summary>
void PlayerClimb::Initialize()
{

}

/// <summary>
/// 更新
/// </summary>
/// <param name="inputstate">入力状態</param>
/// <param name="stickstate">スティック入力情報</param>
/// <param name="camera">カメラ</param>
/// <param name="objectCapsuleStart">衝突しているカプセル始点</param>
/// <param name="objectCapsuleEnd">カプセル終点</param>
/// <returns>状態を変更するか</returns>
bool PlayerClimb::Update(UsePlayerData playerData, const Camera& camera,CollisionData objectCollision)
{
	bool stateChange = false;//状態変更フラグ

	//MoveCapsule(playerData, camera, objectCollision);
	MoveMesh(playerData, camera,objectCollision);
	PlayAnimation(0.5f, stopanimflg);

	//R1を離すとステート変更
	if ((Input::InputNumber::R1 & playerData.inputState) != Input::InputNumber::R1)
	{
		stateChange = true;
	}

	return stateChange;
}

/// <summary>
/// メッシュとの登り動作
/// </summary>
/// <param name="playerData">プレイヤー情報</param>
/// <param name="camera">カメラ</param>
/// <param name="objectData">オブジェクト情報</param>
void PlayerClimb::MoveMesh(UsePlayerData playerData, Camera camera,CollisionData objectData)
{
	stopanimflg = true;										//アニメーション停止フラグ初期化
	moveVec = VGet(0.0f, 0.0f, 0.0f);						//moveVec初期化
	bool hit = false;										//メッシュに当たった
	float nearDistance = 0;										//一番近かったポリゴンとプレイヤーの距離
	int nearNumber = 0;											//一番近かったポリゴンの番号

	//左スティックの角度を取る
	float stickX = playerData.stickState.X;
	float stickY = -playerData.stickState.Y;//コントローラー上入力が+の値になるように

	//入力が無ければ返す
	if (stickX == 0 && stickY == 0)
	{
		return;
	}
	else
	{
		stopanimflg = false;
	}
	
	for (int i = 0; i < objectData.meshData.polygonList.PolygonNum; i++)
	{
		VECTOR vertex0 = objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[i].VIndex[0]].Position;
		VECTOR vertex1 = objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[i].VIndex[1]].Position;
		VECTOR vertex2 = objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[i].VIndex[2]].Position;

		//距離を取る
		float distance = Segment_Triangle_MinLength(playerData.capsuleStart, playerData.capsuleEnd, vertex0, vertex1, vertex2);

		//一回目の時
		if (i == 0)
		{
			nearDistance = distance;
		}

		//あたり判定
		if (distance < playerData.capsuleRadius)
		{
			hit = true;
		}

		//一番近い距離を更新
		if (nearDistance > distance)
		{
			nearDistance = distance;
			nearNumber = i;
		}

		if (hit)
		{
			VECTOR vec01 = VSub(vertex1, vertex0);	//0→1
			VECTOR vec02 = VSub(vertex2, vertex0);	//0→2
			VECTOR normVec = VCross(vec01, vec02);	//法線ベクトル
			normVec = VNorm(normVec);

			//法線とは逆の方向(ポリゴンの方向に向ける)
			moveVec = normVec;
			//法線の辺面との角度
			float angley = calculation->AngleTwoVector(normVec, VGet(normVec.x, 0, normVec.z));

			//上
			if (stickY > 0)
			{
				//方向ベクトル
				VECTOR vecDir = VSub(playerData.capsuleStart, playerData.centerPosition);
				vecDir = VNorm(vecDir);

				moveVec = VScale(vecDir, Speed);
			}
			//下
			if (stickY < 0)
			{
				//方向ベクトル
				VECTOR vecDir = VSub(playerData.capsuleEnd, playerData.centerPosition);
				vecDir = VNorm(vecDir);

				moveVec = VScale(vecDir, Speed);
			}
			//右
			if (stickX > 0)
			{
				//回転軸を取る
				VECTOR shaft = VSub(playerData.capsuleStart, playerData.capsuleEnd);
				shaft = VNorm(shaft);
				//正面から90度横に移動ベクトルの向きを設定
				MATRIX rot = MGetRotAxis(shaft, DX_PI_F / 2);
				VECTOR vecDir = playerData.lookDirection;
				vecDir = VNorm(vecDir);
				vecDir = VTransform(vecDir, rot);
				
				moveVec = VScale(vecDir, Speed);
			}
			//左
			if (stickX < 0)
			{
				//回転軸を取る
				VECTOR shaft = VSub(playerData.capsuleStart, playerData.capsuleEnd);
				shaft = VNorm(shaft);
				//正面から-90度横に移動ベクトルの向きを設定
				MATRIX rot = MGetRotAxis(shaft, -DX_PI_F / 2);
				VECTOR vecDir = playerData.lookDirection;
				vecDir = VNorm(vecDir);
				vecDir = VTransform(vecDir, rot);

				moveVec = VScale(vecDir, Speed);
			}

			//前のベクトルから新しいベクトルに変換したときの回転行列
			//rotateMatrix = MGetRotVec2(targetLookDirection, VScale(normVec, -1));
			//法線の逆の方向に向ける
			targetLookDirection = VScale(normVec, -1);

			break;
		}
	}

	//どこにも当たっていなければ一番近かったポリゴンに近づける
	if (!hit)
	{
		VECTOR vertex0 = objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[nearNumber].VIndex[0]].Position;
		VECTOR vertex1 = objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[nearNumber].VIndex[1]].Position;
		VECTOR vertex2 = objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[nearNumber].VIndex[2]].Position;
		VECTOR vec01 = VSub(vertex1, vertex0);	//0→1
		VECTOR vec02 = VSub(vertex2, vertex0);	//0→2
		VECTOR normVec = VCross(vec01, vec02);	//法線ベクトル
		normVec = VNorm(normVec);

		moveVec = VScale(normVec, -1);
		moveVec = VScale(moveVec, nearDistance);

		//法線の逆の方向に向ける
		targetLookDirection = VScale(normVec, -1);
	}
}

/// <summary>
/// カプセルとの登り動作(使用しない)
/// </summary>
/// <param name="playerData">プレイヤーデータ</param>
/// <param name="camera">カプセル</param>
/// <param name="objectCollision">オブジェクト情報</param>
void PlayerClimb::MoveCapsule(UsePlayerData playerData, Camera camera, CollisionData objectCollision )
{
	stopanimflg = true;										//アニメーション停止フラグ初期化
	moveVec = VGet(0.0f, 0.0f, 0.0f);						//moveVec初期化
	VECTOR afterPos = VGet(0.0f, 0.0f, 0.0f);				//計算後ポジション
	VECTOR positionFromShaftstart = VGet(0.0f, 0.0f, 0.0f);	//軸の始点からのポジションまでのベクトル
	
	//左スティックの角度を取る
	float stickX = playerData.stickState.X;
	float stickY = -playerData.stickState.Y;

	//対象カプセルの軸を取る
	VECTOR shaft = VSub(objectCollision.startPosition, objectCollision.endPosition);

	//登っている場所がカプセルの筒の部分か先端の球の部分か判定
	int capsuleRidePlace;	//0:筒 1:カプセル始点 2:カプセル終点

	//カプセルの両端のどちらに近いか
	float sphere1 = calculation->LengthTwoPoint3D(playerData.position, objectCollision.startPosition);
	float sphere2 = calculation->LengthTwoPoint3D(playerData.position, objectCollision.endPosition);

	//始点に近い場合
	if (sphere1 < sphere2)
	{
		VECTOR OA = VSub(objectCollision.endPosition, objectCollision.startPosition);		//始点→終点
		VECTOR OB = VSub(playerData.position, objectCollision.startPosition);				//始点→プレイヤーポジション
		VECTOR tipPoint = VNorm(OA);														//終点→始点ベクトルの正規化 * 半径 = カプセルの先端ポジション
		tipPoint = VScale(tipPoint, -1);
		tipPoint = VScale(tipPoint, objectCollision.radius);
		VECTOR OH = calculation->OrthogonalProjectionVector(OA, OB);
		float distanceForH = calculation->LengthTwoPoint3D(OH, tipPoint);					//カプセルの先端と垂線の距離
		if (distanceForH < objectCollision.radius)
		{
			capsuleRidePlace = 1;
		}
		else
		{
			capsuleRidePlace = 0;
		}
	}
	else //終点に近い場合
	{
		VECTOR OA = VSub(objectCollision.startPosition, objectCollision.endPosition);
		VECTOR OB = VSub(playerData.position, objectCollision.endPosition);
		VECTOR tipPoint = VNorm(OA);
		tipPoint = VScale(tipPoint, -1);
		tipPoint = VScale(tipPoint, objectCollision.radius);
		VECTOR OH = calculation->OrthogonalProjectionVector(OA, OB);
		float distanceForH = calculation->LengthTwoPoint3D(OH, tipPoint);	//カプセルの先端と垂線の距離
		if (distanceForH < objectCollision.radius)
		{
			capsuleRidePlace = 2;
		}
		else
		{
			capsuleRidePlace = 0;
		}
	}

	//球にいる場合の球とプレイヤーの角度計算
	if (capsuleRidePlace == 1)
	{
		CalculationAngle(playerData.position, objectCollision.startPosition);
	}
	if (capsuleRidePlace == 2)
	{
		CalculationAngle(playerData.position, objectCollision.endPosition);
	}

	//上
	if (stickY > 0)
	{
		if (capsuleRidePlace == 0)
		{
			stopanimflg = false;
			//軸の垂直方向に回転
			positionFromShaftstart = VSub(playerData.position, objectCollision.startPosition);
			afterPos = calculation->RodriguesRotationFormula(shaft, -RotateSpeed, positionFromShaftstart);
			//計算前と計算後の差
			moveVec = VSub(afterPos, positionFromShaftstart);
		}
		if (capsuleRidePlace == 1)
		{
			stopanimflg = false;

			rotateY += RotateSpeed;
			
			afterPos.x = objectCollision.startPosition.x + objectCollision.radius * cos(rotateY) * cos(rotateH);
			afterPos.y = objectCollision.startPosition.y + objectCollision.radius * sin(rotateY);
			afterPos.z = objectCollision.startPosition.z + objectCollision.radius * cos(rotateY) * sin(rotateH);

			//計算前と計算後の差
			moveVec = VSub(afterPos, playerData.position);
		}
		if (capsuleRidePlace == 2)
		{
			stopanimflg = false;

			rotateY += RotateSpeed;

			afterPos.x = objectCollision.endPosition.x + objectCollision.radius * cos(rotateY) * cos(rotateH);
			afterPos.y = objectCollision.endPosition.y + objectCollision.radius * sin(rotateY);
			afterPos.z = objectCollision.endPosition.z + objectCollision.radius * cos(rotateY) * sin(rotateH);

			//計算前と計算後の差
			moveVec = VSub(afterPos, playerData.position);
		}
	}
	//下
	if (stickY < 0)
	{
		if (capsuleRidePlace == 0)
		{
			stopanimflg = false;
			//軸の垂直方向に回転
			positionFromShaftstart = VSub(playerData.position, objectCollision.startPosition);
			afterPos = calculation->RodriguesRotationFormula(shaft, RotateSpeed, positionFromShaftstart);
			//計算前と計算後の差
			moveVec = VSub(afterPos, positionFromShaftstart);
		}
		if (capsuleRidePlace == 1)
		{
			stopanimflg = false;

			rotateY -= RotateSpeed;

			afterPos.x = objectCollision.startPosition.x + objectCollision.radius * cos(rotateY) * cos(rotateH);
			afterPos.y = objectCollision.startPosition.y + objectCollision.radius * sin(rotateY);
			afterPos.z = objectCollision.startPosition.z + objectCollision.radius * cos(rotateY) * sin(rotateH);

			//計算前と計算後の差
			moveVec = VSub(afterPos, playerData.position);
		}
		if (capsuleRidePlace == 2)
		{
			stopanimflg = false;

			rotateY -= RotateSpeed;

			afterPos.x = objectCollision.endPosition.x + objectCollision.radius * cos(rotateY) * cos(rotateH);
			afterPos.y = objectCollision.endPosition.y + objectCollision.radius * sin(rotateY);
			afterPos.z = objectCollision.endPosition.z + objectCollision.radius * cos(rotateY) * sin(rotateH);

			//計算前と計算後の差
			moveVec = VSub(afterPos, playerData.position);
		}
	}
	//左
	if (stickX < 0)
	{
		if (capsuleRidePlace == 0)
		{
			//軸の方向に移動
			stopanimflg = false;

			VECTOR shaftVec = VNorm(shaft);
			VECTOR speedVec = VScale(shaftVec, Speed);
			moveVec = VAdd(moveVec, speedVec);
		}
		if (capsuleRidePlace == 1)
		{
			stopanimflg = false;

			rotateH -= RotateSpeed;

			afterPos.x = objectCollision.startPosition.x + objectCollision.radius * cos(rotateY) * cos(rotateH);
			afterPos.y = objectCollision.startPosition.y + objectCollision.radius * sin(rotateY);
			afterPos.z = objectCollision.startPosition.z + objectCollision.radius * cos(rotateY) * sin(rotateH);

			//計算前と計算後の差
			moveVec = VSub(afterPos, playerData.position);
		}
		if (capsuleRidePlace == 2)
		{
			stopanimflg = false;

			rotateH -= RotateSpeed;

			afterPos.x = objectCollision.endPosition.x + objectCollision.radius * cos(rotateY) * cos(rotateH);
			afterPos.y = objectCollision.endPosition.y + objectCollision.radius * sin(rotateY);
			afterPos.z = objectCollision.endPosition.z + objectCollision.radius * cos(rotateY) * sin(rotateH);

			//計算前と計算後の差
			moveVec = VSub(afterPos, playerData.position);
		}
	}
	//右
	if (stickX > 0)
	{
		if (capsuleRidePlace == 0)
		{
			//軸の方向に移動
			stopanimflg = false;

			VECTOR shaftVec = VNorm(shaft);
			VECTOR speedVec = VScale(shaftVec, -Speed);
			moveVec = VAdd(moveVec, speedVec);
		}
		if (capsuleRidePlace == 1)
		{
			stopanimflg = false;

			rotateH += RotateSpeed;

			afterPos.x = objectCollision.startPosition.x + objectCollision.radius * cos(rotateY) * cos(rotateH);
			afterPos.y = objectCollision.startPosition.y + objectCollision.radius * sin(rotateY);
			afterPos.z = objectCollision.startPosition.z + objectCollision.radius * cos(rotateY) * sin(rotateH);

			//計算前と計算後の差
			moveVec = VSub(afterPos, playerData.position);
		}
		if (capsuleRidePlace == 2)
		{
			stopanimflg = false;

			rotateH += RotateSpeed;

			afterPos.x = objectCollision.endPosition.x + objectCollision.radius * cos(rotateY) * cos(rotateH);
			afterPos.y = objectCollision.endPosition.y + objectCollision.radius * sin(rotateY);
			afterPos.z = objectCollision.endPosition.z + objectCollision.radius * cos(rotateY) * sin(rotateH);

			//計算前と計算後の差
			moveVec = VSub(afterPos, playerData.position);
		}
	}

	//オブジェクトのmoveVecを加算
	moveVec = VAdd(moveVec, objectCollision.moveVec);
}

/// <summary>
/// 角度計算
/// </summary>
/// <param name="playerPosition">プレイヤーポジション</param>
/// <param name="objectPosition">判定対象のポジション</param>
void PlayerClimb::CalculationAngle(VECTOR playerPosition, VECTOR objectPosition)
{
	//差分
	float dx = playerPosition.x - objectPosition.x;
	float dy = playerPosition.y - objectPosition.y;
	float dz = playerPosition.z - objectPosition.z;

	//半径
	float r = sqrt(dx * dx + dy * dy + dz * dz);

	//角度計算
	rotateY = asinf(dy / r);
	rotateH = atan2f(dz, dx);
}