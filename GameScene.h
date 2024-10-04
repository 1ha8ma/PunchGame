#pragma once
#include<vector>
#include"SceneBase.h"

class Camera;
class Player;
class WoodBoard;
class SkyDome;
class InputManager;
class EnemyManager;

class GameScene :public SceneBase
{
private:
	WoodBoard* wood;
	Camera* camera;
	Player* player;
	SkyDome* skydome;
	InputManager* input;
	EnemyManager* enemy;

	bool shieldhit;//盾に当たっているか
	std::vector<int> outchara;//脱落したキャラ

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