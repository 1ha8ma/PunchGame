#pragma once

class InputManager;
class SEManager;

class Pause
{
public:
	enum CursorPoint
	{
		None = -1,
		GameReturn,//ゲームに戻る
		TitleReturn,//タイトルに戻る
	};

	Pause();
	void Initialize();
	int Update();
	void Draw();

private:
	InputManager* input;
	SEManager* semanager;

	//ボタン位置関係定数
	const float ButtonWidth = 680.0f;
	const float ButtonHeight = 50.0f;
	const VECTOR ButtonPos1 = VGet(470.0f, 400.0f, 0.0f);
	const VECTOR ButtonPos2 = VGet(470.0f, 480.0f, 0.0f);

	//入力可能
	bool inputpossibleflg;

	//画像
	int textboximage;
	int button;
	int button_hover;

	//選択
	int cursor;
};