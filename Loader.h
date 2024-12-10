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
		ArmEnemyStage,		//�r�̓G��X�e�[�W
		BossEnemyStage,		//�{�X��X�e�[�W

		//2D

		//��

		//�G�t�F�N�g
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