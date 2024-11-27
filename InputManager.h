#pragma once

class InputManager
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

	//Right = 4,//右
	//	Left = 2,//左
	//	Up = 8,//上
	//	Down = 1,//下
	//	Decision = 16,//決定ボタン(B)
	//	Start = 32,//start
};