#include"DxLib.h"
#include"Loader.h"

//インスタンスを最初に空にする
Loader* Loader::loader = nullptr;

/// <summary>
/// インスタンスゲット
/// </summary>
/// <returns>インスタンス</returns>
Loader* Loader::GetInstance()
{
	//インスタンスが無ければ生成
	if (loader == nullptr)
	{
		loader = new Loader();
	}

	return loader;
}

/// <summary>
/// ロード
/// </summary>
void Loader::Load()
{

}