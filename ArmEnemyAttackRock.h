#pragma once

class CollisionManager;
struct CollisionData;
class Effect;
class Camera;
class SoundEffect;

class ArmEnemyAttackRock
{
public:
	ArmEnemyAttackRock(VECTOR playerPosition,Camera* camera);
	~ArmEnemyAttackRock();
	
	void Update();

	void Draw();

	bool GetEnd() { return end; }

private:
	const float ModelScale = 100.0f;		//モデルスケール
	const float FallSpeed = 35.0f;			//落ちるスピード
	const float CapsuleRadius = 300.0f;		//カプセル半径

	void OnHitObject(CollisionData* objectData);

	void UpdateCollisionData();

	CollisionManager* collisionManager;
	CollisionData collisionData;
	Effect* effect;
	Camera* camera;
	SoundEffect* se;

	int modelHandle;				//モデルハンドル
	VECTOR position;				//ポジション
	float rotateY;					//岩のY座標回転
	bool collisionActive;			//当たり判定を付けるか
	bool end;						//エフェクトまで終了
	VECTOR collisionPosition;		//当たり判定ポジション
	VECTOR hitEffectPosition;		//衝突エフェクトポジション
	VECTOR warningEffectPosition;	//注意エフェクトポジション
};