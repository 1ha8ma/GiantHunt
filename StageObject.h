#pragma once

class CollisionManager;
struct CollisionData;

class StageObject
{
public:
	StageObject(int modelHandle, VECTOR addCapsuleStart, VECTOR addCapsuleEnd, float capsuleRadius, VECTOR drawPosition, VECTOR rotate, float scale);
	~StageObject();

	//�`��
	void Draw();

private:
	//�����������̏���
	void OnHitObject();
	//�����蔻����Z�b�g
	void RegisterCollisionData();

	void InitializePolygonData();
	void DrawPolygon();

	//���N���X
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