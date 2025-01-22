#pragma once
#include"SceneBase.h"

class Input;
class BGM;
class StageBase;
class EnemyBase;
class Camera;
class Player;

class GameClearScene :public SceneBase
{
public:
	GameClearScene(StageBase* stage, EnemyBase* enemy, Camera* camera, Player* player, bool rankIn,int time);
	~GameClearScene()override;

	void Initialize()override;
	SceneBase* Update()override;
	void Draw()override;

private:
	Input* input;
	BGM* bgm;
	StageBase* stage;
	EnemyBase* enemy;
	Camera* camera;
	Player* player;

	bool canInputB;			//B�A�����͖h�~
	int blackBandAlpha;		//���т̓����x
	bool enemyMoveEnd;		//�G�̓����I��
	bool rankIn;			//�����N�C��
	int clearTextBackImage;	//�e�L�X�g�w�i
	int time;				//���̉�̃^�C��
};