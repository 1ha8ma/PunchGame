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

	int titlelogo;
	bool inputpossibleflg;//“ü—Í‰Â”\

public:
	TitleScene();
	~TitleScene() override;
	void Initialize()override;
	SceneBase* Update() override;
	void Draw()override;
};