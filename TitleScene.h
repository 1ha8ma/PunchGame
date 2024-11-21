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

	const float FontScalingSpeed = 1.0f;//�g��k���X�s�[�h

	int gamepadimage;//�Q�[���p�b�h�摜
	int titlelogo;//�^�C�g�����S
	bool inputpossibleflg;//���͉\

	int fontsize;//�t�H���g�T�C�Y
	int fontsizechangeflame;//�t�H���g�g��k���t���[��
	bool fontsizechangeflg;//�t�H���g�g��k���t���O
	VECTOR startpos;//�X�^�[�g�\�L�̃|�W�V����
};