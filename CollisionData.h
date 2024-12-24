#pragma once
#include<functional>
#include"DxLib.h"

//�I�u�W�F�N�g�̎��
enum class ObjectTag :int
{
	//�v���C���[
	Player,
	Attack_P,

	//�r�̓G
	Upperarm_E1,	  //��r
	Forearm_E1,		  //�O�r
	Hand_E1,			//��
	Attack_E1,			//�U��

	//���l
	LeftArm_E2,			//���r
	RightArm_E2,		//�E�r
	LeftLeg_E2,			//����
	RightLeg_E2,		//�E��
	Body_E2,			//����
	Head_E2,			//��
	Attack_E2,			//�U��

	//��
	Wood1,				//��
	Wood2,				//��
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

	//�U����
	int attackPower;

	std::function<void(CollisionData)> HitProcess;   //�����������ɍs���鏈��
	bool isCollisionActive;						//�����蔻���K�p�����������ǂ���
};