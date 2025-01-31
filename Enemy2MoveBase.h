#pragma once

class Camera;

class Enemy2MoveBase
{
public:
	//フレーム番号
	enum class FlameIndex :int
	{
		HeadTop = 7,	//頭の上
		HeadLow = 6,	//頭の下
	};

	Enemy2MoveBase(int modelHandle);
	virtual ~Enemy2MoveBase() {};

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="camera">カメラ</param>
	/// <returns>動きの終了</returns>
	virtual bool Update(Camera* camera) { return false; }

	/// <summary>
	/// 倒された後用更新
	/// </summary>
	/// <param name="camera">カメラ</param>
	/// <returns>動きの終了</returns>
	virtual bool UpdateFallDown(Camera* camera) { return false; }

	/// <summary>
	/// 描画(確認)
	/// </summary>
	virtual void Draw()abstract;	//確認用

	VECTOR GetRotate() { return rotate; }

protected:
	int modelHandle;	//モデルハンドル
	VECTOR rotate;		//回転用
	int moveState;		//動き状態

};