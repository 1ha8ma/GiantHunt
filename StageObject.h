#pragma once

class CollisionManager;
struct CollisionData;

class StageObject
{
public:
	StageObject(int modelHandle, VECTOR addCapsuleStart, VECTOR addCapsuleEnd, float capsuleRadius, VECTOR drawPosition, VECTOR rotate, float scale);
	~StageObject();

	//描画
	void Draw();

private:
	//当たった時の処理
	void OnHitObject();
	//当たり判定情報セット
	void RegisterCollisionData();

	void InitializePolygonData();
	void DrawPolygon();

	//他クラス
	CollisionManager* collisionManager;
	CollisionData collisionData;

	int modelHandle;
	float capsuleRadius;
	VECTOR capsuleStart;
	VECTOR capsuleEnd;
	VECTOR drawPosition;

	bool objecthit;
	MV1_REF_POLYGONLIST polygonList;
};