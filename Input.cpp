#include"DxLib.h"
#include"Input.h"

/// <summary>
/// 入力ゲット
/// </summary>
/// <returns>入力状態</returns>
int Input::GetInputState()
{
	int inputstate = 0;
	
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2 || (CheckHitKey(KEY_INPUT_SPACE)))
	{
		inputstate |= InputNumber::BButton;
	}
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1 || (CheckHitKey(KEY_INPUT_A)))
	{
		inputstate |= InputNumber::AButton;
	}
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_12 || (CheckHitKey(KEY_INPUT_S)))
	{
		inputstate |= InputNumber::Start;
	}
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_5)
	{
		inputstate |= InputNumber::L1;
	}

	return inputstate;
}