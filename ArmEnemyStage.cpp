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
	//�C���X�^���X��
	wood = new Wood();
	wall = new Wall();
	bgm = new BGM(BGM::BGMKind::ArmEnemyStage);
	Loader* loader = loader->GetInstance();

	//�ϐ�������
	modelHandle = loader->GetHandle(Loader::Kind::ArmEnemyStage);
	skyDomeHandle = loader->GetHandle(Loader::Kind::SkyDome);
	stagePosition = VGet(0.0f, 0.0f, 0.0f);
	stageScale = 25.0f;

	//�X�e�[�W�ݒ�
	MV1SetScale(modelHandle, VGet(stageScale, stageScale, stageScale));
	MV1SetPosition(modelHandle, stagePosition);

	//�X�J�C�h�[���ݒ�
	MV1SetScale(skyDomeHandle, VGet(SkyDomeScale, SkyDomeScale, SkyDomeScale));
	MV1SetPosition(skyDomeHandle, VGet(1000, 0, -1000));

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
/// �Q�[���N���A������
/// </summary>
void ArmEnemyStage::InitializeGameClear()
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
	MV1DrawModel(skyDomeHandle);
	MV1DrawModel(modelHandle);
	wall->Draw();
	wood->Draw();
}