#include"DxLib.h"
#include"Loader.h"
#include"InputManager.h"
#include"Pause.h"

/// <summary>
/// コンストラクタ
/// </summary>
Pause::Pause()
{
	Loader* loader = loader->GetInstance();
	input = new InputManager();

	textboximage = loader->GetHandle(Loader::Kind::TextBoxImage);

	Initialize();
}

/// <summary>
/// 初期化
/// </summary>
void Pause::Initialize()
{
	inputpossibleflg = false;
}

/// <summary>
/// 更新
/// </summary>
/// <returns>一時停止終了</returns>
bool Pause::Update()
{
	bool out = false;

	if (input->GetInputState() == 0)
	{
		inputpossibleflg = true;
	}

	if (inputpossibleflg && (32 & input->GetInputState()) == 32)
	{
		out = true;
	}

	return out;
}

/// <summary>
/// 描画
/// </summary>
void Pause::Draw()
{
	DrawExtendGraph(400, 100,1200,600, textboximage, TRUE);
}