#include"DxLib.h"
#include"Loader.h"
#include"CollisionData.h"
#include"CollisionManager.h"
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
	collisionManager->RemoveCollisionData(&collisionData);
}