#pragma once

class Input
{
public:
	enum InputNumber
	{
		Right_L = 1,		//�E
		Left_L = 2,			//��
		Up_L = 4,			//��
		Down_L = 8,			//��
		BButton = 16,		//B�{�^��
		AButton = 32,		//A�{�^��
		Start = 64,			//start
		Right_R = 128,		//�E
		Left_R = 256,		//��
		Up_R = 512,			//��
		Down_R = 1024,		//��
	};

	int GetInputState();
};