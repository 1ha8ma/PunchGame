#pragma once

class InputManager;

class Pause
{
private:
	InputManager* input;

	//���͉\
	bool inputpossibleflg;

	//�w�i�e�L�X�g�{�b�N�X�摜
	int textboximage;
	
public:
	Pause();
	void Initialize();
	bool Update();
	void Draw();
};