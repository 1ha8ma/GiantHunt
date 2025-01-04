#include"DxLib.h"
#include"Loader.h"
#include"EnemyParts.h"
#include"ArmEnemyMove.h"
#include"ArmEnemy.h"

/// <summary>
/// コンストラクタ
/// </summary>
ArmEnemy::ArmEnemy()
{
	Loader* loader = loader->GetInstance();
	//モデルロード
	modelHandle = loader->GetHandle(Loader::Kind::ArmEnemyModel);

	//ステータス初期化
	HP = StartHP;

	//private変数初期化
	position = VGet(2000.0f, -5000.0f, 6550.0f);
	playerRidePlace = (int)ArmEnemyMove::RidePlace::None;

	//描画モデル
	MV1SetScale(modelHandle, VGet(ModelScale, ModelScale, ModelScale));
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, DX_PI_F / 2, 0.0f));
	MV1SetPosition(modelHandle, position);

	//部位当たり判定
	parts.clear();
	parts.push_back(new EnemyParts(ObjectTag::Upperarm_E1, modelHandle, (int)ArmEnemyFrameIndex::Upperarm, 800, 600, VGet(0, 0, -1)));
	parts.push_back(new EnemyParts(ObjectTag::Forearm_E1, modelHandle, (int)ArmEnemyFrameIndex::Forearm, 700, 500, VGet(0, 0, -1)));
	parts.push_back(new EnemyParts(ObjectTag::Hand_E1, modelHandle, (int)ArmEnemyFrameIndex::Hand, 500, 400, VGet(0, 0, -1)));

	armEnemyMove = new ArmEnemyMove(modelHandle);
}

/// <summary>
/// デストラクタ
/// </summary>
ArmEnemy::~ArmEnemy()
{
	parts.clear();
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
	for (int i = 0; i < parts.size(); i++)
	{
		parts[i]->Update();
	}

	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// 描画
/// </summary>
void ArmEnemy::Draw()
{
	MV1DrawModel(modelHandle);

	for (int i = 0; i < parts.size(); i++)
	{
		parts[i]->Draw();
	}
}