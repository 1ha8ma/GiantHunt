#include"DxLib.h"
#include"CollisionManager.h"
#include"Effect.h"
#include"EnemyParts.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="tag">オブジェクトタグ</param>
/// <param name="modelHandle">モデルハンドル</param>
/// <param name="frameIndex">フレーム番号</param>
/// <param name="capsuleLength">カプセルの長さ</param>
/// <param name="capsuleRadius">カプセル半径</param>
/// <param name="frameVec">フレームの座標からの向き</param>
EnemyParts::EnemyParts(ObjectTag tag, int modelHandle, int formerFrameIndex, int frameIndex,float capsuleRadius)
{
	//ハンドルコピー
	this->modelHandle = modelHandle;
	//タグ設定
	this->tag = tag;

	//フレーム番号取得
	this->frameIndex = frameIndex;
	this->formerFrameIndex = formerFrameIndex;

	//カプセル設定
	this->capsuleRadius = capsuleRadius;
	capsuleStart = MV1GetFramePosition(modelHandle, frameIndex);
	capsuleEnd = MV1GetFramePosition(modelHandle, formerFrameIndex);
	
	//private変数初期化
	isPlayerRide = false;

	//当たり判定情報追加
	collisionManager = collisionManager->GetInstance();
	collisionData.HitProcess = std::bind(&EnemyParts::OnHitObject, this, std::placeholders::_1);
	UpdateCollisionData();
	collisionManager->AddCollisionData(&collisionData);

	//弱点ならエフェクトを付ける
	if (tag == ObjectTag::WeakPoint_E1 || tag == ObjectTag::WeakPoint_E2)
	{
		effect = new Effect();

		effect->PlayEffect(Effect::EffectKind::WeakPoint, capsuleStart, VGet(10, 10, 10), VGet(0, 0, 0), 1.0f);
	}
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyParts::~EnemyParts()
{
	collisionManager->RemoveCollisionData(&collisionData);
}

/// <summary>
/// 初期化
/// </summary>
void EnemyParts::Initialize()
{

}

/// <summary>
/// 更新
/// </summary>
void EnemyParts::Update()
{
	//カプセル設定
	//フレームと親フレームの間
	capsuleStart = MV1GetFramePosition(modelHandle, frameIndex);
	capsuleEnd = MV1GetFramePosition(modelHandle, formerFrameIndex);

	//当たり判定情報更新
	UpdateCollisionData();

	//弱点ならエフェクトを付ける
	if (tag == ObjectTag::WeakPoint_E1 || tag == ObjectTag::WeakPoint_E2)
	{
		bool playing = effect->IsPlayEffect(Effect::EffectKind::WeakPoint);

		if (!playing)
		{
			effect->PlayEffect(Effect::EffectKind::WeakPoint, capsuleStart, VGet(50, 50, 50), VGet(0, 0, 0), 1.0f);
		}

		effect->Update(capsuleStart, VGet(0, 0, 0));
	}

	damage = 0;
	isPlayerRide = false;
}

/// <summary>
/// 描画
/// </summary>
void EnemyParts::Draw()
{
	//DrawCapsule3D(capsuleStart, capsuleEnd, capsuleRadius, 8, GetColor(102, 0, 255), GetColor(102, 0, 255), false);
	//DrawSphere3D(framePosition, capsuleRadius, 8, GetColor(102, 0, 255), GetColor(102, 0, 255), false);//ポジションの点

	if (tag == ObjectTag::WeakPoint_E1 || tag == ObjectTag::WeakPoint_E2)
	{
		effect->Draw();
	}
}

/// <summary>
/// 衝突後の処理
/// </summary>
/// <param name="hitObjectData">衝突したオブジェクト</param>
void EnemyParts::OnHitObject(CollisionData hitObjectData)
{
	//プレイヤーが乗っている時の処理
	if (hitObjectData.tag == ObjectTag::PlayerWholeBody)
	{
		isPlayerRide = true;
	}

	//プレイヤーの攻撃だった場合
	if (hitObjectData.tag == ObjectTag::Attack_P)
	{
		damage = hitObjectData.attackPower;
	}
}

/// <summary>
/// 当たり判定更新
/// </summary>
void EnemyParts::UpdateCollisionData()
{
	collisionData.tag = tag;
	collisionData.startPosition = capsuleStart;
	collisionData.endPosition = capsuleEnd;
	collisionData.radius = capsuleRadius;
	collisionData.attackPower = 0;
	collisionData.isCollisionActive = true;
}