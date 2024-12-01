#include"DxLib.h"
#include"InputManager.h"
#include"Camera.h"
#include"SkyDome.h"
#include"Stage.h"
#include"UI.h"
#include"GameScene.h"
#include"Loader.h"
#include"BGMManager.h"
#include"SEManager.h"
#include"TitleScene.h"

/// <summary>
/// コンストラクタ
/// </summary>
TitleScene::TitleScene()
{
	//インスタンス化
	input = new InputManager();
	camera = new Camera();
	skydome = new SkyDome();
	stage = new Stage();
	bgmmanager = new BGMManager();
	semanager = new SEManager();
	ui = new UI();

	Loader* loader = loader->GetInstance();
	titlelogo = loader->GetHandle(Loader::Kind::TitleLogo);
	
	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene()
{
	bgmmanager->StopBGM();

	delete input;
	delete camera;
	delete skydome;
	delete stage;
	delete bgmmanager;
	delete semanager;
	delete ui;
}

/// <summary>
/// 初期化
/// </summary>
void TitleScene::Initialize()
{
	camera->Initialize();
	
	blinkingflg = true;
	blinkingflame = 0;
}

/// <summary>
/// 更新
/// </summary>
/// <returns>次のシーン</returns>
SceneBase* TitleScene::Update()
{
	int inputstate = input->GetInputState();//入力状態

	if (inputstate == 0)//入力が無ければ入力可能に変更
	{
		inputpossibleflg = true;
	}

	if (inputpossibleflg && (InputManager::InputNumber::BButton & inputstate) == InputManager::InputNumber::BButton)//Bボタン
	{
		semanager->PlaySE(SEManager::SEKind::CrickSE);
		return new GameScene();
	}

	//点滅
	if (blinkingflame % 15 == 0 && blinkingflame != 0)
	{
		if (blinkingflg)
		{
			blinkingflg = false;
		}
		else
		{
			blinkingflg = true;
		}
		blinkingflame = 0;
	}
	blinkingflame++;

	//BGM再生
	bgmmanager->PlayBGM(BGMManager::TitleBGM);

	//カメラ更新
	camera->UpdateForTitle();

	return this;
}

/// <summary>
/// 描画
/// </summary>
void TitleScene::Draw()
{
	//モデル
	skydome->Draw();
	stage->Draw();

	//タイトルロゴ
	DrawExtendGraph(470, 0, 1100, 600, titlelogo, TRUE);

	//スタート
	if (blinkingflg)
	{
		SetFontSize(80);
		DrawString(580, 700, "B スタート", GetColor(127, 255, 0));
	}

	//操作説明
	ui->DrawOperationExplanation();
}