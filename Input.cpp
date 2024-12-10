#include"DxLib.h"
#include"Input.h"

/// <summary>
/// 入力ゲット
/// </summary>
/// <returns>入力状態</returns>
int Input::GetInputState()
{
	int inputstate = 0;
	
	DINPUT_JOYSTATE StickInput;//左スティック入力
	GetJoypadDirectInputState(DX_INPUT_PAD1, &StickInput);
	

	if (StickInput.X > 0 || (CheckHitKey(KEY_INPUT_RIGHT)))//右
	{
		inputstate |= InputNumber::Right_L;
	}
	if (StickInput.X < 0 || (CheckHitKey(KEY_INPUT_LEFT)))//左
	{
		inputstate |= InputNumber::Left_L;
	}
	if (StickInput.Y < 0 || (CheckHitKey(KEY_INPUT_UP)))//上
	{
		inputstate |= InputNumber::Up_L;
	}
	if (StickInput.Y > 0 || (CheckHitKey(KEY_INPUT_DOWN)))//下
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
	if (StickInput.Rx > 0)//右
	{
		inputstate |= InputNumber::Right_R;
	}
	if (StickInput.Rx < 0)//左
	{
		inputstate |= InputNumber::Left_R;
	}
	if (StickInput.Ry < 0)//上
	{
		inputstate |= InputNumber::Up_R;
	}
	if (StickInput.Ry > 0)//下
	{
		inputstate |= InputNumber::Down_R;
	}


	return inputstate;
}