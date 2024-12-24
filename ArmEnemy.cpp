#include"DxLib.h"
#include"Loader.h"
#include"ArmEnemy.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ArmEnemy::ArmEnemy()
{
	Loader* loader = loader->GetInstance();

	modelHandle = loader->GetHandle(Loader::Kind::ArmEnemyModel);

	//private�ϐ�������
	position = VGet(2000.0f, -5000.0f, 6550.0f);

	MV1SetScale(modelHandle, VGet(40.0, 40.0f, 40.0f));
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, DX_PI_F / 2, 0.0f));
	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ArmEnemy::~ArmEnemy()
{

}

/// <summary>
/// ������
/// </summary>
void ArmEnemy::Initialize()
{

}

/// <summary>
/// �X�V
/// </summary>
void ArmEnemy::Update()
{

	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// �`��
/// </summary>
void ArmEnemy::Draw()
{
	MV1DrawModel(modelHandle);
}