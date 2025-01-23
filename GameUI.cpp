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

	//1�t���[���O�̃X�e�[�^�X
	prevEnemyHP = enemyHP;
	prevPlayerHP = playerHP;

	//���̑��ϐ�������
	enemyTakeDamage = false;
	playerTakeDamage = false;
	enemyTakeDamageFlame = 0;
	playerTakeDamageFlame = 0;
	enemyColorR = 75;
	enemyColorG = 75;
	enemyColorB = 75;
	playerColorR = 75;
	playerColorG = 75;
	playerColorB = 75;
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

	//�_���[�W���󂯂����m�F
	if (enemyHP != prevEnemyHP)
	{
		//enemyHPBackbarColor = GetColor(224, 255, 255);
		enemyTakeDamageFlame = 0;
		enemyTakeDamage = true;
	}
	if (playerHP != prevPlayerHP)
	{
		//playerHPBackbarColor = GetColor(255, 224, 255);
		playerTakeDamageFlame = 0;
		playerTakeDamage = true;
	}

	//�_���[�W���󂯂Ă����牉�o
	if (enemyTakeDamage)
	{
		//�F�ύX
		enemyColorR += 4;
		if (enemyColorR > 224) { enemyColorR = 224; }
		enemyColorG += 5;
		if (enemyColorG > 255) { enemyColorG = 255; }
		enemyColorB += 5;
		if (enemyColorB > 255) { enemyColorB = 255; }

		enemyTakeDamageFlame++;

		//���t���[���o������
		if (enemyTakeDamageFlame >= 40)
		{
			enemyColorR = 75;
			enemyColorG = 75;
			enemyColorB = 75;
			enemyTakeDamage = false;
		}
	}
	if (playerTakeDamage)
	{
		//�F�ύX
		playerColorR += 5;
		if (playerColorR > 255) { playerColorR = 255; }
		playerColorG += 4;
		if (playerColorG > 224) { playerColorG = 224; }
		playerColorB += 5;
		if (playerColorB > 255) { playerColorB = 255; }

		playerTakeDamageFlame++;

		//���t���[���o������
		if (playerTakeDamageFlame >= 40)
		{
			playerColorR = 75;
			playerColorG = 75;
			playerColorB = 75;
			playerTakeDamage = false;
		}
	}

	//�����v�Z
	enemyHPPer = this->enemyHP / startEnemyHP;
	playerHPPer = this->playerHP / startPlayerHP;
	playerGripPer = this->playerGrip / startPlayerGrip;

	//1�t���[���O�Ƃ��ċL��
	prevEnemyHP = enemyHP;
	prevPlayerHP = playerHP;
}

/// <summary>
/// �`��
/// </summary>
void GameUI::Draw()
{
	//�GHP
	DrawBox(50, 37, 50 + EnemyHPLength, 58, GetColor(enemyColorR,enemyColorG,enemyColorB), TRUE);
	DrawBox(50, 40, 50 + EnemyHPLength * enemyHPPer, 55, GetColor(0, 191, 255), TRUE);
	//�v���C���[HP
	DrawBox(1200, 797, 1200 + PlayerHPLength, 828, GetColor(playerColorR,playerColorG,playerColorB), TRUE);
	DrawBox(1200, 800, 1200 + PlayerHPLength * playerHPPer, 825, GetColor(220, 20, 60), TRUE);
	//�v���C���[����
	DrawCircle(1450, 730, PlayerGripSize + 3, GetColor(75, 75, 75), TRUE);
	DrawCircle(1450, 730, PlayerGripSize * playerGripPer, GetColor(240, 230, 140), TRUE);
}