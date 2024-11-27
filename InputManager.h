#pragma once

class InputManager
{
public:
	enum InputNumber
	{
		Right = 1,//�E          0000001
		Left = 2,//��           0000010
		Up = 4,//��             0000100
		Down = 8,//��           0001000
		BButton = 16,//B�{�^��  0010000
		AButton = 32,//A�{�^���@0100000
		Start = 64,//start      1000000  
	};

	int GetInputState();

	//Right = 4,//�E
	//	Left = 2,//��
	//	Up = 8,//��
	//	Down = 1,//��
	//	Decision = 16,//����{�^��(B)
	//	Start = 32,//start
};