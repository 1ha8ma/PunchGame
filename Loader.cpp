#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Loader.h"

Loader* Loader::loader_ = nullptr;

/// <summary>
/// インスタンスゲット
/// </summary>
/// <returns>ローダークラスゲット</returns>
Loader* Loader::GetInstance()
{
	//インスタンスが無ければ生成
	if (loader_ == nullptr)
	{
		loader_ = new Loader();
	}

	return loader_;
}

/// <summary>
/// モデル等ロード
/// </summary>
void Loader::LoadModel()
{
	//3Dロード
	handle[PlayerModel] = MV1LoadModel("3D/player.mv1");
	handle[Enemy1Model] = MV1LoadModel("3D/Enemy1.mv1");
	handle[Enemy2Model] = MV1LoadModel("3D/Enemy2.mv1");
	handle[Enemy3Model] = MV1LoadModel("3D/Enemy3.mv1");
	handle[ShieldModel] = MV1LoadModel("3D/Shield.mv1");
	handle[FistModel] = MV1LoadModel("3D/fist.mv1");
	handle[DomeModel] = MV1LoadModel("3D/Dome_X501.x");
	handle[WoodBoardModel] = MV1LoadModel("3D/woodboard.mv1");

	////2D
	handle[TitleLogo] = LoadGraph("2D/titlelogo.png");
	handle[NumImage1] = LoadGraph("2D/1image.png");
	handle[NumImage2] = LoadGraph("2D/2image.png");
	handle[NumImage3] = LoadGraph("2D/3image.png");
	handle[RibbonImage] = LoadGraph("2D/ribbon.png");
	handle[StartImage] = LoadGraph("2D/startimage.png");

	////エフェクトロード
	handle[PlayerhitEffect] = LoadEffekseerEffect("Effect/playerhit.efkefc", 30.0f);
	handle[ShieldhitEffect] = LoadEffekseerEffect("Effect/shieldhit.efkefc", 30.0f);
	handle[PunchfiringEffect] = LoadEffekseerEffect("Effect/punchfiring.efkefc", 20.0f);
}