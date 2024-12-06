#include"DxLib.h"
#include"Input.h"

/// <summary>
/// 入力ゲット
/// </summary>
/// <returns>入力状態</returns>
int Input::GetInputState()
{
	int inputstate = 0;

	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) || (CheckHitKey(KEY_INPUT_RIGHT)))//右
	{
		inputstate |= InputNumber::Right;
	}
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT || (CheckHitKey(KEY_INPUT_LEFT)))//左
	{
		inputstate |= InputNumber::Left;
	}
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP || (CheckHitKey(KEY_INPUT_UP)))//上
	{
		inputstate |= InputNumber::Up;
	}
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN || (CheckHitKey(KEY_INPUT_DOWN)))//下
	{
		inputstate |= InputNumber::Down;
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

	return inputstate;
}