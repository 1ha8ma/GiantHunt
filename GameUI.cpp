#include"DxLib.h"
#include"GameUI.h"

GameUI::GameUI(int enemyHP, int playerHP, int playerGrip)
{
	//���݂̃X�e�[�^�X������
	this->enemyHP = enemyHP;
	this->playerHP = playerHP;
	this->playerGrip = playerGrip;

	//�J�n���X�e�[�^�X
	startEnemyHP = enemyHP;
	startPlayerHP = playerHP;
	startPlayerGrip = playerGrip;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameUI::~GameUI()
{

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="enemyHP">�GHP</param>
/// <param name="playerHP">�v���C���[HP</param>
/// <param name="playerGrip">�v���C���[����</param>
void GameUI::Update(int enemyHP, int playerHP, int playerGrip)
{
	//�X�e�[�^�X�擾
	this->enemyHP = enemyHP;
	this->playerHP = playerHP;
	this->playerGrip = playerGrip;

	//�����v�Z
	enemyHPPer = this->enemyHP / startEnemyHP;
	playerHPPer = this->playerHP / startPlayerHP;
	playerGripPer = this->playerGrip / startPlayerGrip;
}

/// <summary>
/// �`��
/// </summary>
void GameUI::Draw()
{
	//�GHP
	DrawBox(50, 38, 50 + EnemyHPLength, 57, GetColor(75, 75, 75),TRUE);
	DrawBox(50, 40, 50 + EnemyHPLength * enemyHPPer, 55, GetColor(0, 191, 255), TRUE);
	//�v���C���[HP
	DrawBox(1200, 798, 1200+ PlayerHPLength, 827, GetColor(75, 75, 75), TRUE);
	DrawBox(1200, 800, 1200 + PlayerHPLength*playerHPPer, 825, GetColor(220, 20, 60), TRUE);
	//�v���C���[����
	DrawCircle(1400, 700, PlayerGripSize+2, GetColor(75, 75, 75), TRUE);
	DrawCircle(1400, 700, PlayerGripSize * playerGripPer, GetColor(240, 230, 140), TRUE);
}