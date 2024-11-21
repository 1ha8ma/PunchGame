#pragma once
#include"SceneBase.h"

class InputManager;
class Camera;
class SkyDome;
class Stage;
class BGMManager;
class SEManager;

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

	const float FontScalingSpeed = 1.0f;//拡大縮小スピード

	int gamepadimage;//ゲームパッド画像
	int titlelogo;//タイトルロゴ
	bool inputpossibleflg;//入力可能

	int fontsize;//フォントサイズ
	int fontsizechangeflame;//フォント拡大縮小フレーム
	bool fontsizechangeflg;//フォント拡大縮小フラグ
	VECTOR startpos;//スタート表記のポジション
};