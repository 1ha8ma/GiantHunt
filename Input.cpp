#include"DxLib.h"
#include"Input.h"

/// <summary>
/// 入力ゲット
/// </summary>
/// <returns>入力状態</returns>
int Input::GetInputState()
{
	int inputstate = 0;
	
	GetJoypadDirectInputState(DX_INPUT_PAD1, &stickInput);
	

	if (stickInput.X > 0 || (CheckHitKey(KEY_INPUT_RIGHT)))//右
	{
		inputstate |= InputNumber::Right_L;
	}
	if (stickInput.X < 0 || (CheckHitKey(KEY_INPUT_LEFT)))//左
	{
		inputstate |= InputNumber::Left_L;
	}
	if (stickInput.Y < 0 || (CheckHitKey(KEY_INPUT_UP)))//上
	{
		inputstate |= InputNumber::Up_L;
	}
	if (stickInput.Y > 0 || (CheckHitKey(KEY_INPUT_DOWN)))//下
	{
		inputstate |= InputNumber::Down_L;
	}
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_4 || (CheckHitKey(KEY_INPUT_SPACE)))//Bボタン
	{
		inputstate |= InputNumber::BButton;
	}
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_3 || (CheckHitKey(KEY_INPUT_A)))
	{
		inputstate |= InputNumber::AButton;
	}
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_12 || (CheckHitKey(KEY_INPUT_S)))//startボタン
	{
		inputstate |= InputNumber::Start;
	}
	if (stickInput.Rx > 0)//右
	{
		inputstate |= InputNumber::Right_R;
	}
	if (stickInput.Rx < 0)//左
	{
		inputstate |= InputNumber::Left_R;
	}
	if (stickInput.Ry < 0)//上
	{
		inputstate |= InputNumber::Up_R;
	}
	if (stickInput.Ry > 0)//下
	{
		inputstate |= InputNumber::Down_R;
	}
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_5)
	{
		inputstate |= InputNumber::L1;
	}


	return inputstate;
}

void Input::Draw()
{
	//DrawFormatString(100, 100, GetColor(127, 255, 0), "LX:%d LY:%d LZ:%d", stickInput.X, stickInput.Y, stickInput.Z);
}