#pragma once

class InputManager
{
public:
	enum InputNumber
	{
		Right = 4,//�E
		Left = 2,//��
		Up = 8,//��
		Down = 1,//��
		Decision = 16,//����{�^��(B)
		Start = 32,//start
	};

	int GetInputState();
};