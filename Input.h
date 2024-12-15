#pragma once

class Input
{
public:
	enum InputNumber
	{
		BButton = 1,		//B�{�^��
		AButton = 2,		//A�{�^��
		Start = 4,			//start
		L1 = 8,			//L2
	};

	int GetInputState();

	DINPUT_JOYSTATE GetStickInput() { GetJoypadDirectInputState(DX_INPUT_PAD1, &stickInput); return stickInput; }

private:
	DINPUT_JOYSTATE stickInput;//�X�e�B�b�N���͏��
};