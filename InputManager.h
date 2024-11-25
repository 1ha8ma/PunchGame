#pragma once

class InputManager
{
public:
	enum InputNumber
	{
		Right = 4,//‰E
		Left = 2,//¶
		Up = 8,//ã
		Down = 1,//‰º
		Decision = 16,//Œˆ’èƒ{ƒ^ƒ“(B)
		Start = 32,//start
	};

	int GetInputState();
};