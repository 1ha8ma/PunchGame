#pragma once
#include"SceneBase.h"

class InputManager;

class TitleScene:public SceneBase
{
private:
	InputManager* input;
	bool inputpossibleflg;

public:
	TitleScene();
	~TitleScene() override;
	void Initialize()override;
	SceneBase* Update() override;
	void Draw()override;
};