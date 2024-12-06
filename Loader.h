#pragma once
#include<map>

class Loader
{
public:
	static Loader* GetInstance();//インスタンスゲット

	enum Kind
	{

	};

	//ハンドルゲット
	int GetHandle(Kind kind) { return handle[kind]; }
	//ロード
	void Load();

private:
	//インスタンス
	static Loader* loader;

	//ハンドルマップ
	std::map<Kind, int> handle;
};