#pragma once
#include<map>

class BGM
{
public:
	//BGM�̎��
	enum class BGMKind :int
	{
		Title,				//�^�C�g��
		GameOver,			//�����V�[��
		ArmEnemyStage,		//�r�̓G��
		Win,				//�����V�[��
	};

	BGM(BGMKind kind);
	~BGM();

	//BGM�Đ�
	void PlayBGM(BGMKind kind);

	//BGM���~�߂�
	void StopBGM();

private:
	//���ʊ���
	enum class Ratio :int
	{
		Title = 100,
		GameOver = 100,
		ArmEnemyStage = 80,
	};

	std::map<BGMKind, int> handle;	//�n���h��
	int playingBGM;					//�Đ�����BGM
};