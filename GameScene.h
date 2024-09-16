#pragma once
#include"SceneBase.h"

class Camera;
class Player;
class WoodBoard;
class SkyDome;
class InputManager;
class Shield;

class GameScene :public SceneBase
{
private:
	WoodBoard* wood;
	Camera* camera;
	Player* player;
	SkyDome* skydome;
	InputManager* input;
	Shield* shield;

public:
	//コンストラクタ
	GameScene();
	//デストラクタ
	~GameScene()override;
	//初期化
	void Initialize()override;
	//更新
	SceneBase* Update()override;
	//描画
	void Draw()override;
};