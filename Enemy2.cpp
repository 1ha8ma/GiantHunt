#include"DxLib.h"
#include"Loader.h"
#include"Camera.h"
#include"EnemyParts.h"
#include"Enemy2MoveBase.h"
#include"Enemy2.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Enemy2::Enemy2()
{
	//�C���X�^���X��
	Loader* loader = loader->GetInstance();
	//���f�����[�h
	modelHandle = loader->GetHandle(Loader::Kind::Enemy2Model);

	//�X�e�[�^�X������
	HP = MaxHP;

	//�ϐ�������
	position = VGet(0, 0, 0);

	//�`�惂�f��
	MV1SetScale(modelHandle, VGet(ModelScale, ModelScale, ModelScale));
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, DX_PI_F / 2, 0.0f));
	MV1SetPosition(modelHandle, position);

	//���ʏ�����
	parts.push_back(new EnemyParts(ObjectTag::EnemyParts, (int)PartsName::Head, modelHandle, 7, 6, 200.0f));
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Enemy2::~Enemy2()
{
	for (int i = 0; i < parts.size(); i++)
	{
		delete parts[i];
	}

	parts.clear();
}

/// <summary>
///	������
/// </summary>
void Enemy2::Initialize()
{

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="playerPosition">�v���C���[�|�W�V����</param>
/// <param name="camera">�J����</param>
/// <returns>����ł��邩</returns>
bool Enemy2::Update(VECTOR playerPosition,Camera* camera)
{
	bool isDead = false;	//����ł��邩

	//HP�m�F
	if (HP == 0)
	{
		isDead = true;
	}

	MV1SetPosition(modelHandle, position);

	return isDead;
}

/// <summary>
/// �|���ꂽ��̏�����
/// </summary>
void Enemy2::InitializeFallDown()
{

}

/// <summary>
/// �|���ꂽ��̍X�V
/// </summary>
/// <param name="camera">�J����</param>
/// <returns>�����̏I��</returns>
bool Enemy2::UpdateFallDown(Camera* camera)
{
	return false;
}

/// <summary>
/// �`��
/// </summary>
void Enemy2::Draw()
{
	MV1DrawModel(modelHandle);
}