#include"DxLib.h"
#include"Loader.h"
#include"Camera.h"
#include"EnemyParts.h"
#include"Enemy2MoveBase.h"
#include"Enemy2.h"

/// <summary>
/// コンストラクタ
/// </summary>
Enemy2::Enemy2()
{
	//インスタンス化
	Loader* loader = loader->GetInstance();
	//モデルロード
	modelHandle = loader->GetHandle(Loader::Kind::Enemy2Model);

	//ステータス初期化
	HP = MaxHP;

	//変数初期化
	position = VGet(0, 0, 0);

	//描画モデル
	MV1SetScale(modelHandle, VGet(ModelScale, ModelScale, ModelScale));
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, DX_PI_F / 2, 0.0f));
	MV1SetPosition(modelHandle, position);

	//部位初期化
	parts.push_back(new EnemyParts(ObjectTag::EnemyParts, (int)PartsName::Head, modelHandle, 7, 6, 200.0f));
}

/// <summary>
/// デストラクタ
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
///	初期化
/// </summary>
void Enemy2::Initialize()
{

}

/// <summary>
/// 更新
/// </summary>
/// <param name="playerPosition">プレイヤーポジション</param>
/// <param name="camera">カメラ</param>
/// <returns>死んでいるか</returns>
bool Enemy2::Update(VECTOR playerPosition,Camera* camera)
{
	bool isDead = false;	//死んでいるか

	//HP確認
	if (HP == 0)
	{
		isDead = true;
	}

	MV1SetPosition(modelHandle, position);

	return isDead;
}

/// <summary>
/// 倒された後の初期化
/// </summary>
void Enemy2::InitializeFallDown()
{

}

/// <summary>
/// 倒された後の更新
/// </summary>
/// <param name="camera">カメラ</param>
/// <returns>動きの終了</returns>
bool Enemy2::UpdateFallDown(Camera* camera)
{
	return false;
}

/// <summary>
/// 描画
/// </summary>
void Enemy2::Draw()
{
	MV1DrawModel(modelHandle);
}