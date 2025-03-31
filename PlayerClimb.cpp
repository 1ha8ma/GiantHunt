#include<fstream>
#include<math.h>
#include"DxLib.h"
#include"nlohmann/json.hpp"
#include"CollisionData.h"
#include"Camera.h"
#include"Calculation.h"
#include"Input.h"
#include"PlayerClimb.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="modelHandle">モデルハンドル</param>
PlayerClimb::PlayerClimb(int modelHandle, VECTOR lookDir) :PlayerStateProcessBase(modelHandle)
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

	//インスタンス化
	calculation = new Calculation();

	//変数初期化
	calculation = new Calculation();
	stopAnimation = false;
	newLookDirection = lookDir;
	Speed = jsonData["ClimbMoveSpeed"];
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

	//動き
	Move(playerData, camera,objectCollision);
	//アニメーション再生
	PlayAnimation(0.5f, stopAnimation);

	//R1を離すとステート変更
	if ((Input::InputNumber::R1 & playerData.inputState) != Input::InputNumber::R1)
	{
		stateChange = true;
	}

	return stateChange;
}

/// <summary>
///登り動作
/// </summary>
/// <param name="playerData">プレイヤー情報</param>
/// <param name="camera">カメラ</param>
/// <param name="objectData">オブジェクト情報</param>
void PlayerClimb::Move(UsePlayerData playerData, Camera camera, CollisionData objectData)
{
	//初期化
	moveVec = VGet(0, 0, 0);				
	float nearDistance;						//最も近い距離
	VECTOR nearVer0, nearVer1, nearVer2;	//最も近いポリゴンの頂点
	int nearPolygonNumber;					//最も近いポリゴン番号
	playerCapStart = playerData.capsuleStart;
	playerCapEnd = playerData.capsuleEnd;
	capsuleRadius = playerData.capsuleRadius;
	stopAnimation = true;

	//近いポリゴンの情報を取る
	NearPolygon(nearPolygonNumber,nearVer0, nearVer1, nearVer2, nearDistance, objectData);

	//確認用中心点
	playerPosition = playerData.position;
	nearPolygonCenter = VAdd(VAdd(nearVer0, nearVer1), nearVer2);
	nearPolygonCenter.x = nearPolygonCenter.x / 3;
	nearPolygonCenter.y = nearPolygonCenter.y / 3;
	nearPolygonCenter.z = nearPolygonCenter.z / 3;

	//法線ベクトル
	VECTOR normVec = calculation->Normalize(nearVer0, nearVer1, nearVer2);

	//入力からのmoveVec
	bool isInputStick = MoveVecForInput(playerData, camera, normVec, nearVer0);

	//向いている方向更新
	newLookDirection = VScale(normVec, -1);

	//回転行列更新
	UpdateRotateMatrix(newLookDirection, playerData.lookDirection);

	//入力が無ければ返す
	if (!isInputStick)
	{
		moveVec = VGet(0, 0, 0);
		return;
	}

	//アニメーションを中断させない
	stopAnimation = false;

	//スピード加算
	moveVec = VScale(moveVec, Speed);

	//移動後のポジション
	VECTOR moveAfterPos = VAdd(playerData.position, moveVec);
	UpdateTentativePlayerCapsule(playerData, moveAfterPos);

	//移動後のポジションが有効か確認
	VECTOR addMoveVec = IsValidMoveAfterPosition(objectData, moveAfterPos, nearVer0, nearVer1, nearVer2);

//	moveVec = VAdd(moveVec, addMoveVec);
}

/// <summary>
/// 確認用
/// </summary>
void PlayerClimb::Draw()
{
	//ポジションと登っているポリゴン中点
	DrawLine3D(nearPolygonCenter, playerPosition,GetColor(127,255,212));
}

/// <summary>
/// 入力からのmoveVec作成
/// </summary>
/// <param name="playerData">プレイヤー情報</param>
/// <param name="camera">カメラ情報</param>
/// <param name="normVec">法線</param>
/// <param name="vertex0">頂点</param>
/// <returns>入力があったか</returns>
bool PlayerClimb::MoveVecForInput(UsePlayerData playerData, Camera camera, VECTOR normVec, VECTOR vertex0)
{
	//入力が無ければ返す
	if (playerData.stickState.X == 0 && playerData.stickState.Y == 0)
	{
		return false;
	}

	//入力からのベクトル作成
	VECTOR inputDir = VGet(0.0f, 0.0f, 0.0f);
	//上
	if (playerData.stickState.Y < 0.0f)
	{
		inputDir = VAdd(inputDir, VSub(playerData.capsuleStart, playerData.capsuleEnd));
	}
	//下
	if (playerData.stickState.Y > 0.0f)
	{
		inputDir = VAdd(inputDir, VSub(playerData.capsuleEnd, playerData.capsuleStart));
	}
	//右
	if (playerData.stickState.X > 0.0f)
	{
		VECTOR cross = VCross(VSub(playerData.capsuleStart, playerData.capsuleEnd), playerData.lookDirection);
		inputDir = VAdd(inputDir, cross);
	}
	//左
	if (playerData.stickState.X < 0.0f)
	{
		VECTOR cross = VCross(playerData.lookDirection, VSub(playerData.capsuleStart, playerData.capsuleEnd));
		inputDir = VAdd(inputDir, cross);
	}

	//平面を移動するように補正
	inputDir = VNorm(inputDir);
	moveVec = ProjectOnPlane(inputDir, normVec);
	moveVec = VNorm(moveVec);

	return true;
}

/// <summary>
/// 回転行列更新
/// </summary>
/// <param name="newLookDirection">新しい向いている方向</param>
/// <param name="prevLookDirection">前に向いていた方向</param>
void PlayerClimb::UpdateRotateMatrix(VECTOR newLookDirection, VECTOR prevLookDirection)
{
	//前の方向と今回の方向の差
	MATRIX addMatrix = MGetRotVec2(prevLookDirection, newLookDirection);

	rotateMatrix = MMult(rotateMatrix, addMatrix);
}

/// <summary>
/// 最も近いポリゴンの情報を取る
/// </summary>
/// <param name="nearVer0">頂点0</param>
/// <param name="nearVer1">頂点1</param>
/// <param name="nearVer2">頂点2</param>
/// <param name="nearDistance">最も近い距離</param>
/// <param name="objectData">オブジェクトデータ</param>
void PlayerClimb::NearPolygon(int& nearPolygonNumber, VECTOR& nearVer0, VECTOR& nearVer1, VECTOR& nearVer2, float& nearDistance, const CollisionData objectData)
{
	for (int i = 0; i < objectData.meshData.polygonList.PolygonNum; i++)
	{
		VECTOR vertex0 = objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[i].VIndex[0]].Position;
		VECTOR vertex1 = objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[i].VIndex[1]].Position;
		VECTOR vertex2 = objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[i].VIndex[2]].Position;

		//距離を取る
		float distance = Segment_Triangle_MinLength(playerCapStart, playerCapEnd, vertex0, vertex1, vertex2);

		//一回目の処理
		if (i == 0)
		{
			nearDistance = distance;
			nearVer0 = vertex0;
			nearVer1 = vertex1;
			nearVer2 = vertex2;
			nearPolygonNumber = i;
		}

		//最も近いポリゴンとその距離
		if (nearDistance > distance)
		{
			nearDistance = distance;
			nearVer0 = vertex0;
			nearVer1 = vertex1;
			nearVer2 = vertex2;
			nearPolygonNumber = i;
		}
	}
}

/// <summary>
/// 入力された情報をポリゴンの平面に映す
/// </summary>
/// <param name="inputDir">入力された方向</param>
/// <param name="polygonNorm">ポリゴン法線</param>
/// <returns></returns>
VECTOR PlayerClimb::ProjectOnPlane(VECTOR inputDir, VECTOR polygonNorm)
{
	float dot = VDot(inputDir, polygonNorm);
	return VSub(inputDir, VScale(polygonNorm, VDot(inputDir, polygonNorm)));
}

/// <summary>
/// 移動先が有効か確認
/// </summary>
/// <param name="objectData">オブジェクトデータ</param>
/// <param name="moveAfterPosition">移動後ポジション</param>
/// <param name="vertex0">頂点</param>
/// <param name="vertex1">頂点</param>
/// <param name="vertex2">頂点</param>
/// <returns>追加の移動ベクトル</returns>
VECTOR PlayerClimb::IsValidMoveAfterPosition(CollisionData objectData, VECTOR moveAfterPosition, VECTOR vertex0, VECTOR vertex1, VECTOR vertex2)
{
	VECTOR addMoveVec = VGet(0, 0, 0);	//追加用移動ベクトル

	//移動後の最近傍点を求める
	VECTOR capsuleClosest, triangleClosest;
	calculation->ClosestPointCapsuleAndTriangle(playerCapStart, playerCapEnd, vertex0, vertex1, vertex2, capsuleClosest, triangleClosest);

	//確認用
	float checkLen = calculation->LengthTwoPoint3D(capsuleClosest, triangleClosest);

	//判定中のポリゴンの中に投影点があるか
	bool inPolygon = false;
	VECTOR polyNorm = calculation->Normalize(vertex0, vertex1, vertex2);
	float u, v, w;
	VECTOR projectClosest = VSub(capsuleClosest, VScale(polyNorm, VDot(VSub(capsuleClosest, vertex0), polyNorm)));
	calculation->Barycentric(vertex0, vertex1, vertex2, projectClosest, u, v, w);
	if (u >= 0 && v >= 0 && w >= 0)
	{
		inPolygon = true;
	}

	//隣の三角形へ移動できるか確認
	if (!inPolygon)
	{	
		//隣のポリゴンを探す
		int nextPolygonNumber;
		nextPolygonNumber = FindNextPolygon(objectData, capsuleClosest, vertex0, vertex1, vertex2);

		//ポジションを隣のポリゴンの最近傍点に変更
		VECTOR nextVer0 = objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[nextPolygonNumber].VIndex[0]].Position;
		VECTOR nextVer1 = objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[nextPolygonNumber].VIndex[1]].Position;
		VECTOR nextVer2 = objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[nextPolygonNumber].VIndex[2]].Position;

		VECTOR nextCapClosest, nextTriClosest;
		calculation->ClosestPointCapsuleAndTriangle(playerCapStart, playerCapEnd, nextVer0, nextVer1, nextVer2, nextCapClosest, nextTriClosest);
		VECTOR newPos = nextTriClosest;
		newPos = VAdd(newPos, VScale(VNorm(VSub(nextCapClosest, nextTriClosest)), capsuleRadius));

		addMoveVec = VSub(moveAfterPosition, newPos);
	}

	return addMoveVec;
}

/// <summary>
/// 隣のポリゴンを見つける
/// </summary>
/// <param name="point">ポジションを投影した点</param>
/// <param name="vertex0">頂点</param>
/// <param name="vertex1">頂点</param>
/// <param name="vertex2">頂点</param>
int PlayerClimb::FindNextPolygon(CollisionData objectData,VECTOR point, VECTOR vertex0, VECTOR vertex1, VECTOR vertex2)
{
	VECTOR vertex[3] = { vertex0,vertex1,vertex2};
	
	//法線
	VECTOR normal = calculation->Normalize(vertex0, vertex1, vertex2);

	//超えていた辺を持つポリゴンを取る
	int nextPolygonNumber = -1;
	if (CheckOutSide(point, normal, vertex1, vertex0, vertex2))
	{
		nextPolygonNumber = CheckSameVertexPolygon(objectData, vertex1, vertex0);
	}
	if (CheckOutSide(point, normal, vertex2, vertex1, vertex0))
	{
		nextPolygonNumber = CheckSameVertexPolygon(objectData, vertex2, vertex1);
	}
	if (CheckOutSide(point, normal, vertex2, vertex0, vertex1))
	{
		nextPolygonNumber = CheckSameVertexPolygon(objectData, vertex2, vertex0);
	}
	
	return nextPolygonNumber;
}

/// <summary>
/// 出た辺を探す
/// </summary>
/// <param name="point">確認する点</param>
/// <param name="normal">法線</param>
/// <param name="sideVer1">辺の頂点</param>
/// <param name="sideVer2">辺の頂点</param>
/// <param name="noSideVer">辺に使用しない頂点</param>
/// <returns>true:辺の外　false:辺の内</returns>
bool PlayerClimb::CheckOutSide(VECTOR point, VECTOR normal, VECTOR sideVer1, VECTOR sideVer2,VECTOR noSideVer)
{
	//辺のベクトル
	VECTOR side = VSub(sideVer2, sideVer1);

	//辺に垂直なベクトル
	VECTOR sideVerticalVec = VCross(side, normal);

	//辺と反対の頂点の方向
	float side1 = VDot(sideVerticalVec, VSub(noSideVer, sideVer1));
	//辺と点の方向
	float side2 = VDot(sideVerticalVec, VSub(point, sideVer1));

	//頂点の方向と辺の方向が同じでないなら外に出ている
	if (side1 * side2 >= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/// <summary>
/// 同じ頂点を2つもつポリゴンを探す
/// </summary>
/// <param name="vertex1">頂点</param>
/// <param name="vertex2">頂点</param>
/// <returns>対象のポリゴンの番号</returns>
int PlayerClimb::CheckSameVertexPolygon(CollisionData objectData, VECTOR vertex1, VECTOR vertex2)
{
	VECTOR vertex3;
	int sameTwoVerPolygonNum;
	int sameVer1, sameVer2;

	for (int i = 0; i < objectData.meshData.polygonList.PolygonNum; i++)
	{
		VECTOR checkVer0 = objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[i].VIndex[0]].Position;
		VECTOR checkVer1 = objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[i].VIndex[1]].Position;
		VECTOR checkVer2 = objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[i].VIndex[2]].Position;

		int sameCount = 0;

		for (int j = 0; j < 3; j++)
		{
			if (calculation->SameVector(vertex1, objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[i].VIndex[j]].Position))
			{
				sameCount++;
				sameVer1 = j;
			}
		}

		for (int k = 0; k < 3; k++)
		{
			if (calculation->SameVector(vertex2, objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[i].VIndex[k]].Position))
			{
				sameCount++;
				sameVer2 = k;
			}
		}

		if (sameCount == 2)
		{
			sameTwoVerPolygonNum = i;
			break;
		}
	}

	//3つ目の頂点を探す
	for (int l = 0; l < 3; l++)
	{
		if (sameVer1 != l && sameVer2 != l)
		{
			vertex3 = objectData.meshData.polygonList.Vertexs[objectData.meshData.polygonList.Polygons[sameTwoVerPolygonNum].VIndex[l]].Position;
		}
	}

	return sameTwoVerPolygonNum;
}

/// <summary>
/// 仮のプレイヤーカプセルを更新
/// </summary>
/// <param name="playerData">プレイヤー情報</param>
void PlayerClimb::UpdateTentativePlayerCapsule(UsePlayerData playerData,VECTOR moveAfterPos)
{
	VECTOR startVec = VGet(0, 1, 0);
	startVec = VTransform(startVec, rotateMatrix);
	playerCapStart = VAdd(moveAfterPos, VScale(startVec, playerData.wholeBodyCapsuleHalfLength));
	VECTOR endVec = VGet(0, -1, 0);
	endVec = VTransform(endVec, MInverse(rotateMatrix));
	playerCapEnd = VAdd(moveAfterPos, VScale(endVec, playerData.wholeBodyCapsuleHalfLength));
}