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
	bool MoveVecForInput(UsePlayerData playerData, Camera camera, VECTOR normVec, VECTOR vertex0);

	//回転行列更新
	void UpdateRotateMatrix(VECTOR newLookDirection, VECTOR prevLookDirection);

	//プレイヤーの仮のカプセルを更新
	void UpdateTentativePlayerCapsule(UsePlayerData playerData,VECTOR moveAfterPos);

	//近いポリゴンの情報を取る
	void NearPolygon(int& nearPolygonNumber,VECTOR& nearVer0, VECTOR& nearVer1, VECTOR& nearVer2, float& nearDistance,const CollisionData objectData);

	//入力された情報をポリゴンの平面に映す
	VECTOR ProjectOnPlane(VECTOR inputDir, VECTOR polygonNormal);

	//移動先が有効か確認
	VECTOR IsValidMoveAfterPosition(CollisionData objectData,VECTOR moveAfterPosition, VECTOR vertex0, VECTOR vertex1, VECTOR vertex2);

	//隣のポリゴンを取る
	int FindNextPolygon(CollisionData objectData,VECTOR point, VECTOR vertex0, VECTOR vertex1, VECTOR vertex2);

	//出たポリゴンの辺を探す
	bool CheckOutSide(VECTOR point,VECTOR normal,VECTOR checkVer1,VECTOR checkVer2,VECTOR noSideVer);

	//同じ2つの頂点を持つポリゴンを探す
	int CheckSameVertexPolygon(CollisionData objectData, VECTOR checkVer1, VECTOR checkVer2);

	//他クラス
	Calculation* calculation;

	//変数
	float Speed;			//移動速度
	bool stopAnimation;		//アニメーション停止フラグ
	VECTOR pushBackVec;		//押し戻しベクトル
	VECTOR playerCapStart;	//カプセル始点
	VECTOR playerCapEnd;	//カプセル終点
	float capsuleRadius;	//カプセル半径

	//確認用
	VECTOR nearPolygonCenter;
	VECTOR playerPosition;
};