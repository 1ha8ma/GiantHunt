#pragma once

class CollisionManager;
struct CollisionData;

class Rock
{
public:
	Rock(int modelHandle, VECTOR addCapsuleStart, VECTOR addCapsuleEnd, float capsuleRadius, VECTOR drawPosition, VECTOR rotate, float scale);
	~Rock();

	//�`��
	void Draw();

private:
	//�����������̏���
	void OnHitObject();
	//�����蔻����Z�b�g
	void RegisterCollisionData();

	//���N���X
	CollisionManager* collisionManager;
	CollisionData collisionData;

	int modelHandle;
	float capsuleRadius;
	VECTOR capsuleStart;
	VECTOR capsuleEnd;
	VECTOR drawPosition;
};