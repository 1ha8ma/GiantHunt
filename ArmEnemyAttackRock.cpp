#include"DxLib.h"
#include"CollisionData.h"
#include"CollisionManager.h"
#include"Camera.h"
#include"Effect.h"
#include"SoundEffect.h"
#include"Loader.h"
#include"ArmEnemyAttackRock.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="playerPosition">プレイヤーポジション</param>
ArmEnemyAttackRock::ArmEnemyAttackRock(VECTOR playerPosition,Camera* camera)
{
	//インスタンス化
	Loader* loader = loader->GetInstance();
	effect = new Effect();
	se = new SoundEffect();
	this->camera = camera;

	//変数初期化
	modelHandle = loader->GetHandle(Loader::Kind::RockModel4);
	position = playerPosition;
	warningEffectPosition = position;
	position.y = 8000.0f;
	collisionPosition = VAdd(position, VGet(0.0f, 130.0f, 0.0f));
	rotateY = 0.0f;
	collisionActive = true;
	end = false;

	//当たり判定情報
	collisionManager = collisionManager->GetInstance();
	collisionData.HitProcess = std::bind(&ArmEnemyAttackRock::OnHitObject, this, std::placeholders::_1);
	UpdateCollisionData();
	collisionManager->AddCollisionData(&collisionData);

	//ポジションセット
	MV1SetScale(modelHandle, VGet(ModelScale, ModelScale, ModelScale));
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, 0.0f, rotateY));
	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// デストラクタ
/// </summary>
ArmEnemyAttackRock::~ArmEnemyAttackRock()
{
	collisionManager->RemoveCollisionData(&collisionData);

	delete effect;
}

/// <summary>
/// 更新
/// </summary>
void ArmEnemyAttackRock::Update()
{
	position.y -= FallSpeed;
	rotateY += 0.04f;
	collisionPosition = VAdd(position, VGet(0.0f, 170.0f, 0.0f));

	//当たり判定情報更新
	UpdateCollisionData();

	//注意エフェクト
	if (!effect->IsPlayEffect(Effect::EffectKind::Warning))
	{
		effect->PlayEffect(Effect::EffectKind::Warning, warningEffectPosition, VGet(80, 20, 80), VGet(0, 0, 0), 1.0f);
	}
	effect->Update(Effect::EffectKind::Warning, warningEffectPosition, VGet(0, 0, 0));

	//衝突後
	if (!collisionActive)
	{
		effect->Update(Effect::EffectKind::RockHit, hitEffectPosition, VGet(DX_PI_F / 2, 0.0f, 0.0f));
		if (!effect->IsPlayEffect(Effect::EffectKind::RockHit))
		{
			end = true;
		}
	}

	//地面との衝突
	if (position.y <= 0.0f && collisionActive)
	{
		hitEffectPosition = VAdd(position,VGet(0.0f,70.0f,0.0f));
		effect->PlayEffect(Effect::EffectKind::RockHit, hitEffectPosition, VGet(50, 50, 50), VGet(DX_PI_F / 2, 0.0f, 0.0f), 0.1f);
		//上下揺れ
		camera->PlayShakingVertical(1.0f, 5, 50);
		//振動
		StartJoypadVibration(DX_INPUT_PAD1, 150, 1000, -1);
		//se
		se->PlaySE(SoundEffect::SEKind::RockHit);
		collisionActive = false;
	}

	MV1SetRotationXYZ(modelHandle, VGet(0.0f, rotateY, 0));
	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// 描画
/// </summary>
void ArmEnemyAttackRock::Draw()
{
	if (collisionActive)
	{
		MV1DrawModel(modelHandle);
	}
	effect->Draw();

	//確認用
	//DrawCapsule3D(collisionPosition, collisionPosition, CapsuleRadius, 8, GetColor(124, 34, 232), GetColor(124, 34, 232), false);
}

/// <summary>
/// 当たり判定情報更新
/// </summary>
void ArmEnemyAttackRock::UpdateCollisionData()
{
	collisionData.tag = ObjectTag::EnemyAttack;
	collisionData.attackPower = 20;
	collisionData.startPosition = collisionPosition;
	collisionData.endPosition = collisionPosition;
	collisionData.radius = CapsuleRadius;
	collisionData.isCollisionActive = collisionActive;
}

/// <summary>
/// オブジェクト衝突時
/// </summary>
/// <param name="collisionData">衝突したオブジェクト</param>
void ArmEnemyAttackRock::OnHitObject(CollisionData* collisionData)
{
	if (collisionActive && (collisionData->tag == ObjectTag::StageObject || collisionData->tag == ObjectTag::PlayerWholeBody))
	{
		hitEffectPosition = VAdd(position, VGet(0.0f, 70.0f, 0.0f));
		effect->PlayEffect(Effect::EffectKind::RockHit, hitEffectPosition, VGet(50, 50, 50), VGet(DX_PI_F / 2, 0.0f, 0.0f), 0.1f);
		//振動
		//上下揺れ
		camera->PlayShakingVertical(0.5, 5, 50);
		//振動
		StartJoypadVibration(DX_INPUT_PAD1, 150, 1000, -1);
		//se
		se->PlaySE(SoundEffect::SEKind::RockHit);
		collisionActive = false;
	}
}