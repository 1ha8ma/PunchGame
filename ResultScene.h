#pragma once
#include"SceneBase.h"

class ResultScene :public SceneBase
{
private:
	InputManager* input;

	bool inputpossibleflg;

public:
	ResultScene();
	~ResultScene() override;
	void Initialize()override;
	SceneBase* Update() override;
	void Draw()override;
};