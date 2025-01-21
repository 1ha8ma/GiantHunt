#include"DxLib.h"
#include"Loader.h"
#include"CollisionManager.h"
#include"BGM.h"
#include"Wood.h"
#include"Wall.h"
#include"ArmEnemyStage.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ArmEnemyStage::ArmEnemyStage()
{
	Loader* loader = loader->GetInstance();

	modelHandle = loader->GetHandle(Loader::Kind::ArmEnemyStage);
	circleRadius = 2000.0f;
	position = VGet(0.0f, 0.0f, 0.0f);
	stageScale = 25.0f;

	MV1SetScale(modelHandle, VGet(stageScale, stageScale, stageScale));
	MV1SetPosition(modelHandle, position);

	//�C���X�^���X��
	wood = new Wood();
	wall = new Wall();
	bgm = new BGM(BGM::BGMKind::ArmEnemyStage);

	//�����蔻��
	collisionManager = collisionManager->GetInstance();
	collisionData.stageLeft = StageLeft;
	collisionData.stageRight = StageRight;
	collisionData.stageFront = StageFront;
	collisionData.stageBack = StageBack;

	collisionManager->AddCollisionData(&collisionData);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ArmEnemyStage::~ArmEnemyStage()
{
	bgm->StopBGM();
	collisionManager->RemoveCollisionData(&collisionData);
	delete wood;
	delete wall;
	delete bgm;
}

/// <summary>
/// �Q�[���I�[�o�[�V�[��������
/// </summary>
void ArmEnemyStage::InitializeGameOver()
{
	bgm->StopBGM();
}

/// <summary>
/// �X�V
/// </summary>
void ArmEnemyStage::Update()
{
	bgm->PlayBGM(BGM::BGMKind::ArmEnemyStage);
}

/// <summary>
/// �`��
/// </summary>
void ArmEnemyStage::Draw()
{
	MV1DrawModel(modelHandle);
	wall->Draw();
	wood->Draw();
}