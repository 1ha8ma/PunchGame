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

	const float FontScalingSpeed = 1.0f;//�g��k���X�s�[�h

	int gamepadimage;//�Q�[���p�b�h�摜
	int titlelogo;//�^�C�g�����S
	bool inputpossibleflg;//���͉\

	//�_��
	bool blinkingflg;
	int blinkingflame;
};