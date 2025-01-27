#pragma once
#include"SceneBase.h"

class Camera;
class Player;
class Enemy2;
class ArmEnemyStage;

class Enemy2StartScene :public SceneBase
{
public:
	Enemy2StartScene();
	~Enemy2StartScene()override;

	void Initialize()override;
	SceneBase* Update()override;
	void Draw()override;

private:
	const int MaxBlackBandAlpha = 255;	//���эő�Z��

	//���N���X
	Camera* camera;
	Player* player;
	Enemy2* enemy;
	ArmEnemyStage* stage;

	int flame;					//�J�n����̃t���[����
	int blackBandAlpha;			//���т̓����x
	VECTOR cameraPosition;		//�J�����|�W�V����
	VECTOR cameraLookPosition;	//�J���������_
};