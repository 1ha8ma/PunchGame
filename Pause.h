#pragma once

class InputManager;
class SEManager;

class Pause
{
public:
	enum CursorPoint
	{
		None = -1,
		GameReturn,//�Q�[���ɖ߂�
		TitleReturn,//�^�C�g���ɖ߂�
	};

	Pause();
	void Initialize();
	int Update();
	void Draw();

private:
	InputManager* input;
	SEManager* semanager;

	//�{�^���ʒu�֌W�萔
	const float ButtonWidth = 680.0f;
	const float ButtonHeight = 50.0f;
	const VECTOR ButtonPos1 = VGet(470.0f, 400.0f, 0.0f);
	const VECTOR ButtonPos2 = VGet(470.0f, 480.0f, 0.0f);

	//���͉\
	bool inputpossibleflg;

	//�摜
	int textboximage;
	int button;
	int button_hover;

	//�I��
	int cursor;
};