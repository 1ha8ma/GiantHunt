#pragma once

class Camera;

class Enemy2MoveBase
{
public:
	//�t���[���ԍ�
	enum class FlameIndex :int
	{
		HeadTop = 7,	//���̏�
		HeadLow = 6,	//���̉�
	};

	Enemy2MoveBase(int modelHandle);
	virtual ~Enemy2MoveBase() {};

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="camera">�J����</param>
	/// <returns>�����̏I��</returns>
	virtual bool Update(Camera* camera) { return false; }

	/// <summary>
	/// �|���ꂽ��p�X�V
	/// </summary>
	/// <param name="camera">�J����</param>
	/// <returns>�����̏I��</returns>
	virtual bool UpdateFallDown(Camera* camera) { return false; }

	/// <summary>
	/// �`��(�m�F)
	/// </summary>
	virtual void Draw()abstract;	//�m�F�p

	VECTOR GetRotate() { return rotate; }

protected:
	int modelHandle;	//���f���n���h��
	VECTOR rotate;		//��]�p
	int moveState;		//�������

};