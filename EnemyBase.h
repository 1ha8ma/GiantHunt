#pragma once
#include"Camera.h"

class EnemyBase
{
public:
	EnemyBase() {};
	virtual ~EnemyBase() {};

	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize()abstract;

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="playerPos">�v���C���[�|�W�V����</param>
	/// <param name="camera">�J����</param>
	/// <returns>�Q�[���I�[�o�[��</returns>
	virtual bool Update(VECTOR playerPos, Camera* camera)abstract;

	/// <summary>
	/// �|���ꂽ��̏�����
	/// </summary>
	virtual void InitializeFallDown()abstract;

	/// <summary>
	/// �|���ꂽ��̍X�V
	/// </summary>
	/// <param name="camera">�J����</param>
	/// <returns>�����̏I��</returns>
	virtual bool UpdateFallDown(Camera* camera)abstract;

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