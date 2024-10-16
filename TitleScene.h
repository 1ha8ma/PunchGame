#pragma once
#include"SceneBase.h"

class InputManager;
class Camera;
class SkyDome;
class WoodBoard;

class TitleScene:public SceneBase
{
private:
	InputManager* input;
	Camera* camera;
	SkyDome* skydome;
	WoodBoard* woodboard;

	int gamepadimage;//ゲームパッド画像
	int titlelogo;//タイトルロゴ
	bool inputpossibleflg;//入力可能

public:
	TitleScene();
	~TitleScene() override;
	void Initialize()override;
	SceneBase* Update() override;
	void Draw()override;
};