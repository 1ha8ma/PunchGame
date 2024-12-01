#pragma once
#include"SceneBase.h"

class InputManager;
class Camera;
class SkyDome;
class Stage;
class BGMManager;
class SEManager;
class UI;

class TitleScene:public SceneBase
{
public:
	TitleScene();
	~TitleScene() override;
	void Initialize()override;
	SceneBase* Update() override;
	void Draw()override;

private:
	InputManager* input;
	Camera* camera;
	SkyDome* skydome;
	Stage* stage;
	BGMManager* bgmmanager;
	SEManager* semanager;
	UI* ui;

	const float FontScalingSpeed = 1.0f;//拡大縮小スピード

	int gamepadimage;//ゲームパッド画像
	int titlelogo;//タイトルロゴ
	bool inputpossibleflg;//入力可能

	//点滅
	bool blinkingflg;
	int blinkingflame;
};