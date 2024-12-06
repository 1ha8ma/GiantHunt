#include"DxLib.h"
#include"SceneBase.h"
#include"GameManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
GameManager::GameManager()
{
	//シーン初期化s
	nowscene = SceneBase::InitializeBase();
}

/// <summary>
/// 更新
/// </summary>
void GameManager::Update()
{
	//シーン更新
	nextscene = nowscene->Update();

	//nextsceneがnowsceneと違えばシーン変更
	if (nextscene != nowscene)
	{
		ChangeScene();
	}
}

void GameManager::Draw()
{
	nowscene->Draw();
}

void GameManager::ChangeScene()
{
	//現在のシーンを削除
	delete nowscene;

	//シーン切り替え
	nowscene = nextscene;

	//シーン初期化
	nowscene->Initialize();

	//nextsceneを空にする
	nextscene = NULL;
}