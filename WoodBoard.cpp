#include"DxLib.h"
#include"Loader.h"
#include"WoodBoard.h"

/// <summary>
/// コンストラクタ
/// </summary>
WoodBoard::WoodBoard()
{
	Loader* loader = loader->GetInstance();
	model = loader->GetHandle(Loader::Kind::WoodBoardModel);

	Initialize();
}

/// <summary>
/// 初期化
/// </summary>
void WoodBoard::Initialize()
{
	//各モデル設定
	for (int i = 0; i < AllBoardNum; i++)
	{
		eachmodel.push_back(MV1DuplicateModel(model));
	}

	//各ポジション設定
	//真ん中
	for (int i = 0; i < MiddleBoardNum; i++)
	{
		pos.push_back(VGet(0.0f, 0.0f, -800 + i * 200));
	}

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
	for (int i = 0; i < MiddleBoardNum; i++)
	{
		rotax.push_back(0.0f);
		rotay.push_back(1.55f);
		rotaz.push_back(0.0f);
	}
	//左
	for (int i = 0; i < LeftBoardNum; i++)
	{
		rotax.push_back(0.0f);
		rotay.push_back(0.0f);
		rotaz.push_back(0.0f);
	}
	//右
	for (int i = 0; i < RightBoardNum; i++)
	{
		rotax.push_back(0.0f);
		rotay.push_back(0.0f);
		rotaz.push_back(0.0f);
	}

	//角度設定
	for (int i = 0; i < AllBoardNum; i++)
	{
		MV1SetRotationXYZ(eachmodel[i], VGet(rotax[i], rotay[i], rotaz[i]));
	}

	//各紐づけ
	for (int i = 0; i < AllBoardNum; i++)
	{
		MV1SetPosition(eachmodel[i], pos[i]);
	}
}

/// <summary>
/// 描画
/// </summary>
void WoodBoard::Draw()
{
	for (int i = 0; i < AllBoardNum; i++)
	{
		MV1DrawModel(eachmodel[i]);
	}
}