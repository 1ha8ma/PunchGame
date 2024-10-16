#include"DxLib.h"
#include"InputManager.h"
#include"Camera.h"
#include"SkyDome.h"
#include"WoodBoard.h"
#include"GameScene.h"
#include"Loader.h"
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
	woodboard = new WoodBoard();

	Loader* loader = loader->GetInstance();
	titlelogo = loader->GetHandle(Loader::Kind::TitleLogo);
	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene()
{

}

/// <summary>
/// 初期化
/// </summary>
void TitleScene::Initialize()
{
	camera->Initialize();

	inputpossibleflg = false;
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

	if (inputpossibleflg && (16 & inputstate) == 16)//Bボタン
	{
		return new GameScene();
	}

	//クラス更新

	camera->UpdateForTitle();

	return this;
}

/// <summary>
/// 描画
/// </summary>
void TitleScene::Draw()
{
	skydome->Draw();
	woodboard->Draw();

	DrawExtendGraph(470, 0,1100,600, titlelogo, TRUE);

	SetFontSize(80);
	ChangeFont("851テガキカクット",DX_CHARSET_DEFAULT);
	DrawString(600, 700, "スタート", GetColor(127, 255, 0));
}