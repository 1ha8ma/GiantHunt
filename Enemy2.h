#pragma once
#include<vector>
#include"EnemyBase.h"

class EnemyParts;

class Enemy2 :public EnemyBase
{
public:
	Enemy2();
	~Enemy2()override;

	//������
	void Initialize()override;
	//�X�V
	bool Update(VECTOR playerPos, Camera* camera)override;

	//�|���ꂽ��̏�����
	void InitializeFallDown()override;
	//�|���ꂽ��̍X�V
	bool UpdateFallDown(Camera* camera)override;

	//�`��
	void Draw()override;

private:
	//�p�[�c�̖��O
	enum class PartsName :int
	{
		Head,			//��
		Body,			//����
		LeftUpperArm,	//����r
		LeftForeArm,	//���O�r
		LeftHand,		//����
		LeftSowrd,		//����̌��̕���
		RightUpperArm,	//�E��r
		RightForeArm,	//�E�O�r
		RightHand,		//�E��
		LeftThigh,		//��������
		LeftCalf,		//���ӂ���͂�
		LeftFoot,		//����
		RightThigh,		//�E�ӂƂ���
		RightCalf,		//�E�ӂ���͂�
		RightFoot,		//�E��
		WeakPoint,		//��_
	};

	/// <summary>
	/// �����̎��
	/// </summary>
	enum class MoveKind :int
	{
		Walk,			//����

	};

	const float ModelScale = 40.0f;		//���f���X�P�[��
	const int MaxHP = 2000;				//�ő�HP

	std::vector<EnemyParts*> parts;		//�����蔻��p�[�c
};
