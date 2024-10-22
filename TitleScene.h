#pragma once
#include"SceneBase.h"

class InputManager;
class Camera;
class SkyDome;
class WoodBoard;
class BGMManager;
class SEManager;

class TitleScene:public SceneBase
{
private:
	InputManager* input;
	Camera* camera;
	SkyDome* skydome;
	WoodBoard* woodboard;
	BGMManager* bgmmanager;
	SEManager* semanager;

	int gamepadimage;//ゲームパッド画像
	int titlelogo;//タイトルロゴ
	bool inputpossibleflg;//入力可能
	int fontsize;//startのフォントサイズ
	int fontsizechangeflame;
	bool fontsizechangeflg;

public:
	TitleScene();
	~TitleScene() override;
	void Initialize()override;
	SceneBase* Update() override;
	void Draw()override;
};