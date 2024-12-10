#pragma once

class Input
{
public:
	enum InputNumber
	{
		Right_L = 1,		//右
		Left_L = 2,			//左
		Up_L = 4,			//上
		Down_L = 8,			//下
		BButton = 16,		//Bボタン
		AButton = 32,		//Aボタン
		Start = 64,			//start
		Right_R = 128,		//右
		Left_R = 256,		//左
		Up_R = 512,			//上
		Down_R = 1024,		//下
	};

	int GetInputState();
};