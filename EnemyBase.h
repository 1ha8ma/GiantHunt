#pragma once

class EnemyBase
{
public:
	EnemyBase() {};
	virtual ~EnemyBase() {};

	virtual void Initialize()abstract;
	virtual bool Update(VECTOR playerPos, Camera* camera)abstract;
	virtual void Draw()abstract;

	//GetSet
	int GetHP() { return HP; }
	VECTOR GetTargetCameraPosition() { return targetCameraPosition; }

protected:
	//�X�e�[�^�X
	int HP;

	int modelHandle;						//���f���n���h��
	VECTOR position;						//�`��|�W�V����
	VECTOR targetCameraPosition;			//�^�[�Q�b�g�J�����p�|�W�V����
};