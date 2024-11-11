#include"DxLib.h"
#include"Loader.h"
#include"Stage.h"

//ステージの各座標
const float Stage::StageRight = 1550.0f;//右
const float Stage::StageLeft = -1550.0f;//左
const float Stage::StageTop = 1650.0f;//上
const float Stage::StageBottom = -1400.0f;//下

/// <summary>
/// コンストラクタ
/// </summary>
Stage::Stage()
{
	Loader* loader = loader->GetInstance();
	model = loader->GetHandle(Loader::Kind::StageModel);

	Initialize();
}

/// <summary>
/// 初期化
/// </summary>
void Stage::Initialize()
{
	//回転
	MV1SetRotationXYZ(model, VGet(0.0f, DX_PI_F / 2, 0.0f));
	//ポジション設定
	MV1SetPosition(model, VGet(0, 0, 200));
}

/// <summary>
/// 描画
/// </summary>
void Stage::Draw()
{
	MV1DrawModel(model);
}