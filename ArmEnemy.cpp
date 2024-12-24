#include"DxLib.h"
#include"Loader.h"
#include"ArmEnemy.h"

/// <summary>
/// コンストラクタ
/// </summary>
ArmEnemy::ArmEnemy()
{
	Loader* loader = loader->GetInstance();

	modelHandle = loader->GetHandle(Loader::Kind::ArmEnemyModel);

	//private変数初期化
	position = VGet(2000.0f, -5000.0f, 6550.0f);

	MV1SetScale(modelHandle, VGet(40.0, 40.0f, 40.0f));
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, DX_PI_F / 2, 0.0f));
	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// デストラクタ
/// </summary>
ArmEnemy::~ArmEnemy()
{

}

/// <summary>
/// 初期化
/// </summary>
void ArmEnemy::Initialize()
{

}

/// <summary>
/// 更新
/// </summary>
void ArmEnemy::Update()
{

	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// 描画
/// </summary>
void ArmEnemy::Draw()
{
	MV1DrawModel(modelHandle);
}