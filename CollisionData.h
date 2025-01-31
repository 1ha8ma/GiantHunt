#pragma once
#include<functional>
#include"DxLib.h"

//�I�u�W�F�N�g�̎��
enum class ObjectTag :int
{
	//�X�e�[�W
	Stage,

	//�v���C���[
	PlayerWholeBody,	//�S�g
	PlayerFoot,			//��
	Attack_P,			//�U��

	//�G
	EnemyParts,			//�G�̃p�[�c
	EnemyAttack,		//�G�̍U��
	WeakPoint,			//�G�̎�_

	//��
	StageObject,
};

//�����蔻����
struct CollisionData
{
	//�^�O
	ObjectTag tag;
	
	//���S
	VECTOR position;

	//�J�v�Z���p
	VECTOR startPosition;   //�J�v�Z���n�_
	VECTOR endPosition;     //�J�v�Z���I�_
	float radius;           //�J�v�Z�����a

	//��������
	VECTOR moveVec;			//�����J�v�Z���p

	//�l�p�X�e�[�W�p(�|�W�V����)
	float stageLeft;
	float stageRight;
	float stageFront;
	float stageBack;

	//�U����
	int attackPower;

	std::function<void(CollisionData*)> HitProcess;		//�����������ɍs���鏈��
	std::function<void(VECTOR)> WallHitProcess;			//�X�e�[�W�ǏՓˎ��̏���
	bool isCollisionActive;								//�����蔻���K�p�����������ǂ���
};