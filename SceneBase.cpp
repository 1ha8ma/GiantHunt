#include"SceneBase.h"
#include"GameScene.h"

/// <summary>
/// �ŏ��̃V�[����ݒ�
/// </summary>
/// <returns>�V�[��</returns>
SceneBase* SceneBase::InitializeBase()
{
	return new GameScene();
}