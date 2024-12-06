#pragma once
#include<map>

class Loader
{
public:
	static Loader* GetInstance();//�C���X�^���X�Q�b�g

	enum Kind
	{

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