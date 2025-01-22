#pragma once
#include<map>

class Loader
{
public:
	static Loader* GetInstance();//�C���X�^���X�Q�b�g

	enum Kind
	{
		//3D
		PlayerModel,			//�v���C���[
		ArmEnemyModel,			//�r�̓G
		WallModel,				//��
		BossEnemyModel,			//�{�X
		WoodModel,				//��
		ArmEnemyStage,			//�r�̓G��X�e�[�W
		BossEnemyStage,			//�{�X��X�e�[�W

		//2D
		GameOverBackImage,		//�Q�[���I�[�o�[�w�i
		TitleBackImage,			//�^�C�g���w�i
		RankingArmEnemyImage,	//�����L���O��ʂ̘r�̓G�w�i
		ClearTextBackImage,		//�N���A��ʂ̃e�L�X�g�w�i

		//BGM
		TitleBGM,				//�^�C�g��BGM
		GameOverBGM,			//�Q�[���I�[�o�[BGM
		ArmEnemyBGM,			//�r�̓G��
		GameClearBGM,			//�Q�[���N���ABGM
		RankingBGM,				//�����L���O���BGM

		//SE
		MowinDownSE,			//�U�艺�낵�U��SE
		NormalAttackSE,			//�ʏ�U��SE
		SwingSE,				//�U��܂��SE
		HitWeakPointSE,			//��_�q�b�gSE
		CrickSE,				//����SE
		CursorMoveSE,			//�J�[�\���ړ�SE

		//�G�t�F�N�g
		WeakPointEffect,		//��_
		HitWeakPointEffect,		//��_�q�b�g�G�t�F�N�g
	};

	//�n���h���Q�b�g
	int GetHandle(Kind kind) { return handle[kind]; }
	//���[�h
	void Load();

private:
	//�C���X�^���X
	static Loader* loader;

	//�n���h���}�b�v
	std::map<Kind, int> handle;
};