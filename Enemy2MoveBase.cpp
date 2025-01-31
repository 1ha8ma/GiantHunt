#include"DxLib.h"
#include"Camera.h"
#include"Enemy2MoveBase.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="modelHandle">モデルハンドル</param>
Enemy2MoveBase::Enemy2MoveBase(int modelHandle)
{
	this->modelHandle = modelHandle;
}