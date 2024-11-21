#pragma once

class InputManager;

class Pause
{
private:
	InputManager* input;

	//入力可能
	bool inputpossibleflg;

	//背景テキストボックス画像
	int textboximage;
	
public:
	Pause();
	void Initialize();
	bool Update();
	void Draw();
};