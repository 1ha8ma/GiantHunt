#pragma once

class Input
{
public:
	enum InputNumber
	{
		Right = 1,//右          0000001
		Left = 2,//左           0000010
		Up = 4,//上             0000100
		Down = 8,//下           0001000
		BButton = 16,//Bボタン  0010000
		AButton = 32,//Aボタン　0100000
		Start = 64,//start      1000000  
	};

	int GetInputState();
};