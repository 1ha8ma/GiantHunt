#include"DxLib.h"
#include"Loader.h"
#include"ArmEnemyStage.h"

/// <summary>
/// コンストラクタ
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
}