#include"DxLib.h"
#include"WoodBoard.h"

/// <summary>
/// コンストラクタ
/// </summary>
WoodBoard::WoodBoard()
{
	model = MV1LoadModel("3D/woodboard.mv1");

	Initialize();
}

/// <summary>
/// 初期化
/// </summary>
void WoodBoard::Initialize()
{
	//各モデル設定
	for (int i = 0; i < BoardNum; i++)
	{
		eachmodel.push_back(MV1DuplicateModel(model));
	}

	//各ポジション設定
	//真ん中
	pos.push_back(VGet(0, 0, 1800));
	pos.push_back(VGet(0, 0, 1600));
	pos.push_back(VGet(0, 0, 1400));
	pos.push_back(VGet(0, 0, 1200));
	pos.push_back(VGet(0, 0, 1000));
	pos.push_back(VGet(0, 0, 800));
	pos.push_back(VGet(0, 0, 600));
	pos.push_back(VGet(0, 0, 400));
	pos.push_back(VGet(0, 0, 200));
	pos.push_back(VGet(0, 0, 0));
	pos.push_back(VGet(0, 0, -200));
	pos.push_back(VGet(0, 0, -400));
	pos.push_back(VGet(0, 0, -600));
	pos.push_back(VGet(0, 0, -800));
	//左
	for (int i = 0; i < 6; i++)
	{
		pos.push_back(VGet(-630 - (i * 200), 0, -580));
	}
	for (int i = 0; i < 6; i++)
	{
		pos.push_back(VGet(-630 - (i * 200), 0, 0));
	}
	for (int i = 0; i < 6; i++)
	{
		pos.push_back(VGet(-630 - (i * 200), 0, 580));
	}
	for (int i = 0; i < 6; i++)
	{
		pos.push_back(VGet(-630 - (i * 200), 0, 1160));
	}
	//右
	for (int i = 0; i < 6; i++)
	{
		pos.push_back(VGet(580 + (i * 200), 0, -530));
	}
	for (int i = 0; i < 6; i++)
	{
		pos.push_back(VGet(580 + (i * 200), 0, 0));
	}
	for (int i = 0; i < 6; i++)
	{
		pos.push_back(VGet(580 + (i * 200), 0, 530));
	}
	for (int i = 0; i < 6; i++)
	{
		pos.push_back(VGet(580 + (i * 200), 0, 1160));
	}

	//角度設定
	//真ん中
	for (int i = 0; i < 14; i++)
	{
		rotax.push_back(0.0f);
		rotay.push_back(1.55f);
		rotaz.push_back(0.0f);
	}
	//左
	for (int i = 0; i < 24; i++)
	{
		rotax.push_back(0.0f);
		rotay.push_back(0.0f);
		rotaz.push_back(0.0f);
	}
	//右
	for (int i = 0; i < 24; i++)
	{
		rotax.push_back(0.0f);
		rotay.push_back(0.0f);
		rotaz.push_back(0.0f);
	}

	//角度設定
	for (int i = 0; i < BoardNum; i++)
	{
		MV1SetRotationXYZ(eachmodel[i], VGet(rotax[i], rotay[i], rotaz[i]));
	}

	//各紐づけ
	for (int i = 0; i < BoardNum; i++)
	{
		MV1SetPosition(eachmodel[i], pos[i]);
	}
}

/// <summary>
/// 更新
/// </summary>
void WoodBoard::Update()
{

}

/// <summary>
/// 描画
/// </summary>
void WoodBoard::Draw()
{
	for (int i = 0; i < BoardNum; i++)
	{
		MV1DrawModel(eachmodel[i]);
	}
}