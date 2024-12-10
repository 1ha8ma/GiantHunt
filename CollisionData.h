#pragma once
#include<functional>
#include"DxLib.h"

struct CapsuleCollisionData;

class HitObjectAddress
{

};

//�I�u�W�F�N�g�̎��
enum ObjectTag
{
	//�v���C���[
	LeftArm_P,		  //���r
	RightArm_P,		  //�E�r
	LeftLeg_P,        //����
	RightLeg_P,       //�E��
	Body_P,           //����
	Head_P,           //��
	Attack_P,         //�U��

	//�r�̓G
	Upperarm_E1,	  //��r
	Forearm_E1,		  //�O�r
	Hand_E1,		  //��
	Attack_E1,		  //�U��

	//���l
	LeftArm_E2,		  //���r
	RightArm_E2,	  //�E�r
	LeftLeg_E2,		  //����
	RightLeg_E2,	  //�E��
	Body_E2,		  //����
	Head_E2,		  //��
	Attack_E2,		  //�U��
};

//�����蔻����
struct CollisionData
{
	//�^�O
	ObjectTag tag;
	
	//�J�v�Z���p
	VECTOR startPosition;   //�J�v�Z���n�_
	VECTOR endPosition;     //�J�v�Z���I�_
	float radius;           //�J�v�Z�����a

	//�C���^���N�g
	float interactRadius;     //���̃I�u�W�F�N�g�ɃA�N�Z�X�o����͈�
	int interactionCost;      //���̃I�u�W�F�N�g�̃C���^���N�g�ɂ�����R�X�g
	bool isInteracted;        //�C���^���N�g���s�������ǂ���

	std::function<void(CollisionData)> onHit;   //�����������ɍs���鏈��
	bool isCollisionActive;						//�����蔻���K�p�����������ǂ���

	HitObjectAddress* objectAddress;
};