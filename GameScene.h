#pragma once
#include<vector>
#include"SceneBase.h"

class Camera;
class Player;
class Stage;
class SkyDome;
class InputManager;
class EnemyManager;
class UI;
class Pause;
class ResultScene;
class StartScene;
class BGMManager;
class SEManager;

class GameScene :public SceneBase
{
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

private:
	Stage* stage;
	Camera* camera;
	Player* player;
	SkyDome* skydome;
	InputManager* input;
	EnemyManager* enemy;
	UI* ui;
	Pause* pausescene;
	ResultScene* resultscene;
	StartScene* startscene;
	BGMManager* bgmmanager;
	SEManager* semanager;

	//ゲームシーン内のステート
	int nowstate;
	enum GameSceneState
	{
		start,//スタートシーン
		game,//ゲームシーン
		pause,//一時停止
		result,//リザルトシーン
	};

	bool pauseinputpossible;
	bool outpauseinputflg;//一時停止解除後の入力が無くなった
	
	bool playeroutcheck;//プレイヤーが攻撃に当たった
	std::vector<int> outchara;//脱落したキャラ

	VECTOR winnerpos;//勝者ポジション
	float winnerangle;//勝者角度
	bool scenechange;//シーン切り替えフラグ
	int winnernumber;//勝者のキャラナンバー
};