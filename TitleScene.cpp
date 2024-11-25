#include"DxLib.h"
#include"InputManager.h"
#include"Camera.h"
#include"SkyDome.h"
#include"Stage.h"
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
}

/// <summary>
/// 初期化
/// </summary>
void TitleScene::Initialize()
{
	camera->Initialize();

	fontsize = 80;
	fontsizechangeflame = 0;
	fontsizechangeflg = false;
	inputpossibleflg = false;

	startpos = VGet(550.0f, 700.0f, 0.0f);
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

	if (inputpossibleflg && (InputManager::InputNumber::Decision & inputstate) == InputManager::InputNumber::Decision)//Bボタン
	{
		semanager->PlaySE(SEManager::SEKind::CrickSE);
		return new GameScene();
	}

	//BGM再生
	bgmmanager->PlayBGM(BGMManager::TitleBGM);

	//カメラ更新
	camera->UpdateForTitle();

	//フォントサイズ更新
	fontsizechangeflame++;

	if (fontsizechangeflame != 0 && fontsizechangeflame % 30 == 0)
	{
		//拡大縮小交代
		if (fontsizechangeflg)
		{
			fontsizechangeflg = false;
		}
		else
		{
			fontsizechangeflg = true;
		}

		fontsizechangeflame = 0;
	}

	if (fontsizechangeflg)//縮小
	{
		fontsize -= FontScalingSpeed;
		startpos.x += FontScalingSpeed;
		startpos.y += FontScalingSpeed;
	}
	else//拡大
	{
		fontsize += FontScalingSpeed;
		startpos.x -= FontScalingSpeed;
		startpos.y -= FontScalingSpeed;
	}

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
	SetFontSize(fontsize);
	DrawString(startpos.x, startpos.y, "A スタート", GetColor(127, 255, 0));
}