#pragma once

class Input
{
public:
	enum InputNumber
	{
		BButton = 1,		//Bボタン
		AButton = 2,		//Aボタン
		Start = 4,			//start
		L1 = 8,			//L2
	};

	int GetInputState();

	DINPUT_JOYSTATE GetStickInput() { GetJoypadDirectInputState(DX_INPUT_PAD1, &stickInput); return stickInput; }

private:
	DINPUT_JOYSTATE stickInput;//スティック入力情報
};