#pragma once

class InputManager
{
public:
	enum InputNumber
	{
		Right = 4,//右
		Left = 2,//左
		Up = 8,//上
		Down = 1,//下
		Decision = 16,//決定ボタン(B)
		Start = 32,//start
	};

	int GetInputState();
};