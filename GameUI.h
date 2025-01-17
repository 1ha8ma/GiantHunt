#pragma once

class GameUI
{
public:
	GameUI(int enemyHP,int playerHP,int playerGrip);
	~GameUI();

	void Update(int enemyHP, int playerHP, int playerGrip);
	void Draw();

private:
	const float PlayerHPLength = 300.0f;	//�`��v���C���[HP�Q�[�W�̒���
	const float EnemyHPLength = 500.0f;		//�`��GHP�Q�[�W�̒���
	const float PlayerGripSize = 60.0f;		//�`��v���C���[���͂̑傫��

	float startEnemyHP;			//�J�n���GHP
	float startPlayerHP;		//�J�n���v���C���[HP
	float startPlayerGrip;		//�J�n���v���C���[����

	float enemyHP;				//���݂̓GHP
	float playerHP;				//���݂̃v���C���[HP
	float playerGrip;			//���݂̃v���C���[����

	float enemyHPPer;			//�GHP����
	float playerHPPer;			//�v���C���[HP����
	float playerGripPer;		//�v���C���[���͊���
};