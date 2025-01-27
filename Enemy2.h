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
	const float ModelScale = 40.0f;		//���f���X�P�[��
	const int MaxHP = 2000;				//�ő�HP

	std::vector<EnemyParts*> parts;		//�����蔻��p�[�c
};
