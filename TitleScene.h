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

	int gamepadimage;//�Q�[���p�b�h�摜
	int titlelogo;//�^�C�g�����S
	bool inputpossibleflg;//���͉\
	int fontsize;//start�̃t�H���g�T�C�Y
	int fontsizechangeflame;
	bool fontsizechangeflg;

public:
	TitleScene();
	~TitleScene() override;
	void Initialize()override;
	SceneBase* Update() override;
	void Draw()override;
};