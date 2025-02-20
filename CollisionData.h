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

//���b�V���f�[�^
struct MeshData
{
	//�I�u�W�F�N�g�^�O
	ObjectTag tag;										
	//���b�V�����
	MV1_REF_POLYGONLIST polygonList;					//�|���S�����X�g
};

//�����蔻����
struct CollisionData
{
	//�^�O
	ObjectTag tag;
	
	//���S
	VECTOR position;

	//�J�v�Z��(���b�V�����̑O�ɃJ�v�Z���ő�܂��ɔ��肵�āA�S�ẴI�u�W�F�N�g�ƃ��b�V�����肷��̂�h������)
	VECTOR startPosition;								//�J�v�Z���n�_
	VECTOR endPosition;									//�J�v�Z���I�_
	float radius;										//�J�v�Z�����a

	//���b�V�����
	MeshData meshData;

	//��������
	VECTOR moveVec;										//�����J�v�Z���p

	//�l�p�X�e�[�W�p(�|�W�V����)
	float stageLeft;									//�E(x+)
	float stageRight;									//��(x-)
	float stageFront;									//�O(z+)
	float stageBack;									//��(z-)

	//�U����
	int attackPower;

	std::function<void(CollisionData*)> HitProcess;		//�����������ɍs���鏈��
	std::function<void(VECTOR)> WallHitProcess;			//�X�e�[�W�ǏՓˎ��̏���
	bool isCollisionActive;								//�����蔻���K�p�����������ǂ���
};
