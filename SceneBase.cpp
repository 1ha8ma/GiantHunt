#include"SceneBase.h"
#include"TitleScene.h"
//#include"GameScene.h"

/// <summary>
/// 最初のシーンを設定
/// </summary>
/// <returns>シーン</returns>
SceneBase* SceneBase::InitializeBase()
{
	return new TitleScene();
}