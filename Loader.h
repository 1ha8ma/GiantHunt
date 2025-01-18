#pragma once
#include<map>

class Loader
{
public:
	static Loader* GetInstance();//�C���X�^���X�Q�b�g

	enum Kind
	{
		//3D
		PlayerModel,        //�v���C���[
		ArmEnemyModel,		//�r�̓G
		WallModel,			//��
		BossEnemyModel,		//�{�X
		WoodModel,			//��
		ArmEnemyStage,		//�r�̓G��X�e�[�W
		BossEnemyStage,		//�{�X��X�e�[�W

		//2D
		GameOverBackImage,	//�Q�[���I�[�o�[�w�i
		TitleBackImage,		//�^�C�g���w�i

		//BGM
		ArmEnemyBGM,		//�r�̓G��

		//SE
		MowinDownSE,		//�U�艺�낵�U��SE
		NormalAttackSE,		//�ʏ�U��SE
		SwingSE,			//�U��܂��SE

		//�G�t�F�N�g
		WeakPointEffect,	//��_
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