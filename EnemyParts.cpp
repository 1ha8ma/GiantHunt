#include"DxLib.h"
#include"CollisionManager.h"
#include"SoundEffect.h"
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
EnemyParts::EnemyParts(ObjectTag tag, int modelHandle, int frameIndex1, int frameIndex2,float capsuleRadius)
{
	//ハンドルコピー
	this->modelHandle = modelHandle;
	//タグ設定
	this->tag = tag;

	//フレーム番号取得
	this->frameIndex1 = frameIndex1;
	this->frameIndex2 = frameIndex2;

	//カプセル設定
	this->capsuleRadius = capsuleRadius;
	capsuleStart = MV1GetFramePosition(modelHandle, frameIndex1);
	capsuleEnd = MV1GetFramePosition(modelHandle, frameIndex2);
	
	//インスタンス化
	se = new SoundEffect();

	//private変数初期化
	isPlayerRide = false;
	hitWeakPointEffectflg = false;
	hitWeakPointEffectflame = 0;

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
	MV1ResetFrameUserLocalMatrix(modelHandle, frameIndex1);
	MV1ResetFrameUserLocalMatrix(modelHandle, frameIndex2);
	collisionManager->RemoveCollisionData(&collisionData);
	delete se;
	if (tag == ObjectTag::WeakPoint_E1 || tag == ObjectTag::WeakPoint_E2)
	{
		effect->RemoveEffect(Effect::EffectKind::WeakPoint);
		delete effect;
	}
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
	capsuleStart = MV1GetFramePosition(modelHandle, frameIndex1);
	capsuleEnd = MV1GetFramePosition(modelHandle, frameIndex2);

	//当たり判定情報更新
	UpdateCollisionData();

	//弱点ならエフェクトを付ける
	if (tag == ObjectTag::WeakPoint_E1 || tag == ObjectTag::WeakPoint_E2)
	{
		bool playing = effect->IsPlayEffect(Effect::EffectKind::WeakPoint);

		//終了していたらまた再生
		if (!playing)
		{
			effect->PlayEffect(Effect::EffectKind::WeakPoint, capsuleStart, VGet(50, 50, 50), VGet(0, 0, 0), 1.0f);
		}

		effect->Update(Effect::EffectKind::WeakPoint, capsuleStart, VGet(0, 0, 0));
	}

	//弱点ヒットのエフェクト更新
	if (hitWeakPointEffectflg)
	{
		effect->Update(Effect::EffectKind::HitWeakPoint, capsuleStart, VGet(0, 0, 0));

		if (hitWeakPointEffectflame == PlayHitWeakPointEffectFlame)
		{
			effect->RemoveEffect(Effect::EffectKind::HitWeakPoint);
			hitWeakPointEffectflg = false;
		}

		//フレーム加算
		hitWeakPointEffectflame++;
	}

	damage = 0;
	isPlayerRide = false;
}

/// <summary>
/// 描画
/// </summary>
void EnemyParts::Draw()
{
	if (tag == ObjectTag::WeakPoint_E1 || tag == ObjectTag::WeakPoint_E2)
	{
		effect->Draw();
	}

	//確認用
	//DrawCapsule3D(capsuleStart, capsuleEnd, capsuleRadius, 8, GetColor(102, 0, 255), GetColor(102, 0, 255), false);
	//DrawSphere3D(framePosition, capsuleRadius, 8, GetColor(102, 0, 255), GetColor(102, 0, 255), false);//ポジションの点
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
		//弱点の場合
		if (tag == ObjectTag::WeakPoint_E1)
		{
			effect->PlayEffect(Effect::EffectKind::HitWeakPoint, capsuleStart, VGet(120.0f, 120.0f, 120.0f), VGet(0, 0, 0), 1.0f);
			se->PlaySE(SoundEffect::SEKind::HitWeakPoint);
			damage = hitObjectData.attackPower * 2;
			if (!hitWeakPointEffectflg)
			{
				hitWeakPointEffectflame = 0;
				hitWeakPointEffectflg = true;
			}
		}
		//その他
		else
		{
			damage = hitObjectData.attackPower;
		}
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