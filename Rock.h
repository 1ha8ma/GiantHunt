#pragma once

class CollisionManager;
struct CollisionData;

class Rock
{
public:
	Rock(int modelHandle, VECTOR addCapsuleStart, VECTOR addCapsuleEnd, float capsuleRadius, VECTOR drawPosition, VECTOR rotate, float scale);
	~Rock();

	//描画
	void Draw();

private:
	//当たった時の処理
	void OnHitObject();
	//当たり判定情報セット
	void RegisterCollisionData();

	//他クラス
	CollisionManager* collisionManager;
	CollisionData collisionData;

	int modelHandle;
	float capsuleRadius;
	VECTOR capsuleStart;
	VECTOR capsuleEnd;
	VECTOR drawPosition;
};