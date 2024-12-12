#include<math.h>
#include"DxLib.h"
#include"Camera.h"
#include"PlayerStateProcessBase.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="modelHandle">モデルハンドル</param>
PlayerStateProcessBase::PlayerStateProcessBase(int modelHandle)
{
	this->modelHandle = modelHandle;

	nowAnimPlayTime = 0.0f;
}

/// <summary>
/// アニメーション再生
/// </summary>
/// <param name="playSpeed">再生速度</param>
/// <param name="stop">一時停止</param>
void PlayerStateProcessBase::PlayAnimation(float playSpeed,bool stop)
{
	if (!stop)
	{
		nowAnimPlayTime += playSpeed;
	}

	//アニメーション時間が総再生時間に達していた場合
	if (nowAnimPlayTime >= animTotalTime)
	{
		nowAnimPlayTime = 0.0f;
	}

	//アニメーション反映
	MV1SetAttachAnimTime(modelHandle, nowPlayAnim, nowAnimPlayTime);
}

/// <summary>
/// アニメーションの終了
/// </summary>
void PlayerStateProcessBase::DetachAnimation(int attachIndex)
{
	MV1DetachAnim(modelHandle, attachIndex);
}