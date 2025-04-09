#pragma once
#include"PlayerStateProcessBase.h"
#include"Calculation.h"

class Calculation;

class PlayerClimb :public PlayerStateProcessBase
{
public:
	PlayerClimb(int modelHandle,VECTOR lookDir);
	~PlayerClimb()override;

	//������
	void Initialize()override;
	//�X�V
	bool Update(UsePlayerData playerData, const Camera& camera, CollisionData objectCollision)override;

	void Draw()override;

private:
	const float RotateSpeed = 0.01f;	//��]���x

	//����
	void Move(UsePlayerData playerData, Camera camera,CollisionData objectData);

	//���͂����moveVec�쐬
	void MoveVecForInput(UsePlayerData playerData, VECTOR normVec);

	//��]�s��X�V
	void UpdateRotateMatrix(VECTOR newLookDirection, VECTOR prevLookDirection,VECTOR normVec);

	//�߂��|���S���������A�������
	int NearPolygon(const CollisionData objectData);

	//���͂��ꂽ�����|���S���̕��ʂɉf��
	VECTOR ProjectOnPlane(VECTOR inputDir, VECTOR polygonNormal);

	//���N���X
	Calculation* calculation;

	//�ϐ�
	float Speed;			//�ړ����x
	bool stopAnimation;		//�A�j���[�V������~�t���O

	//�m�F�p
	VECTOR nearPolygonCenter;
	VECTOR playerPosition;
};