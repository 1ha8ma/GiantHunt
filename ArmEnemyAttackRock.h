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
	const float ModelScale = 100.0f;		//���f���X�P�[��
	const float FallSpeed = 35.0f;			//������X�s�[�h
	const float CapsuleRadius = 300.0f;		//�J�v�Z�����a

	void OnHitObject(CollisionData* objectData);

	void UpdateCollisionData();

	CollisionManager* collisionManager;
	CollisionData collisionData;
	Effect* effect;
	Camera* camera;
	SoundEffect* se;

	int modelHandle;				//���f���n���h��
	VECTOR position;				//�|�W�V����
	float rotateY;					//���Y���W��]
	bool collisionActive;			//�����蔻���t���邩
	bool end;						//�G�t�F�N�g�܂ŏI��
	VECTOR collisionPosition;		//�����蔻��|�W�V����
	VECTOR hitEffectPosition;		//�Փ˃G�t�F�N�g�|�W�V����
	VECTOR warningEffectPosition;	//���ӃG�t�F�N�g�|�W�V����
};