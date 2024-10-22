#pragma once
#include<vector>
#include"SceneBase.h"

class Camera;
class Player;
class WoodBoard;
class SkyDome;
class InputManager;
class EnemyManager;
class GameUI;
class ResultScene;
class StartScene;
class BGMManager;
class SEManager;

class GameScene :public SceneBase
{
private:
	WoodBoard* wood;
	Camera* camera;
	Player* player;
	SkyDome* skydome;
	InputManager* input;
	EnemyManager* enemy;
	GameUI* gameui;
	ResultScene* resultscene;
	StartScene* startscene;
	BGMManager* bgmmanager;
	SEManager* semanager;

	bool gamestartflg;//ゲーム開始フラグ
	bool gameendflg;//ゲーム決着フラグ
	bool playeroutcheck;//プレイヤーが攻撃に当たった
	bool playerattackshieldhit;//盾に当たっているか
	std::vector<int> outchara;//脱落したキャラ

	VECTOR winnerpos;//勝者ポジション
	float winnerangle;//勝者角度
	bool scenechange;//シーン切り替えフラグ
	int winnernumber;//勝者のキャラナンバー

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