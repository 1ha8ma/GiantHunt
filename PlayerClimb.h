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
	bool MoveVecForInput(UsePlayerData playerData, Camera camera, VECTOR normVec, VECTOR vertex0);

	//��]�s��X�V
	void UpdateRotateMatrix(VECTOR newLookDirection, VECTOR prevLookDirection);

	//�v���C���[�̉��̃J�v�Z�����X�V
	void UpdateTentativePlayerCapsule(UsePlayerData playerData,VECTOR moveAfterPos);

	//�߂��|���S���̏������
	void NearPolygon(int& nearPolygonNumber,VECTOR& nearVer0, VECTOR& nearVer1, VECTOR& nearVer2, float& nearDistance,const CollisionData objectData);

	//���͂��ꂽ�����|���S���̕��ʂɉf��
	VECTOR ProjectOnPlane(VECTOR inputDir, VECTOR polygonNormal);

	//�ړ��悪�L�����m�F
	VECTOR IsValidMoveAfterPosition(CollisionData objectData,VECTOR moveAfterPosition, VECTOR vertex0, VECTOR vertex1, VECTOR vertex2);

	//�ׂ̃|���S�������
	int FindNextPolygon(CollisionData objectData,VECTOR point, VECTOR vertex0, VECTOR vertex1, VECTOR vertex2);

	//�o���|���S���̕ӂ�T��
	bool CheckOutSide(VECTOR point,VECTOR normal,VECTOR checkVer1,VECTOR checkVer2,VECTOR noSideVer);

	//����2�̒��_�����|���S����T��
	int CheckSameVertexPolygon(CollisionData objectData, VECTOR checkVer1, VECTOR checkVer2);

	//���N���X
	Calculation* calculation;

	//�ϐ�
	float Speed;			//�ړ����x
	bool stopAnimation;		//�A�j���[�V������~�t���O
	VECTOR pushBackVec;		//�����߂��x�N�g��
	VECTOR playerCapStart;	//�J�v�Z���n�_
	VECTOR playerCapEnd;	//�J�v�Z���I�_
	float capsuleRadius;	//�J�v�Z�����a

	//�m�F�p
	VECTOR nearPolygonCenter;
	VECTOR playerPosition;
};