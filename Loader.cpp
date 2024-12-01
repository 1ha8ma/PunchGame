#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Loader.h"

//唯一のインスタンスを最初にnullptrにする
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
	handle[StageModel] = MV1LoadModel("3D/stage.mv1");

	//2D
	handle[TitleLogo] = LoadGraph("2D/titlelogo.png");
	handle[NumImage1] = LoadGraph("2D/1image.png");
	handle[NumImage2] = LoadGraph("2D/2image.png");
	handle[NumImage3] = LoadGraph("2D/3image.png");
	handle[RibbonImage] = LoadGraph("2D/ribbon.png");
	handle[StartImage] = LoadGraph("2D/startimage.png");
	handle[GamePadImage] = LoadGraph("2D/gamepadimage.png");
	handle[TextBoxImage] = LoadGraph("2D/textbox.png");
	handle[PlayerArrowImage] = LoadGraph("2D/PlayerArrow.png");
	handle[ButtonImage] = LoadGraph("2D/button.png");
	handle[BUttonHoverImage] = LoadGraph("2D/button_hover.png");

	//エフェクト
	handle[LasthitEffect] = LoadEffekseerEffect("Effect/playerhit.efkefc", 30.0f);
	handle[ShieldhitEffect] = LoadEffekseerEffect("Effect/shieldhit.efkefc", 30.0f);
	handle[PunchfiringEffect] = LoadEffekseerEffect("Effect/punchfiring.efkefc", 20.0f);
	handle[BlowEffect] = LoadEffekseerEffect("Effect/bloweffect.efkefc", 20.0f);

	//BGM
	handle[TitleBGM] = LoadSoundMem("sound/TitleBGM.mp3");
	handle[GameBGM] = LoadSoundMem("sound/GameBGM.mp3");
	handle[ResultBGM] = LoadSoundMem("sound/ResultBGM.mp3");

	//SE
	handle[StartSceneSE] = LoadSoundMem("sound/StartSceneSE.mp3");
	handle[StartSE] = LoadSoundMem("sound/startSE.mp3");
	handle[CountSE] = LoadSoundMem("sound/countSE.mp3");
	handle[CrickSE] = LoadSoundMem("sound/CrickSE.mp3");
	handle[ShieldHitSE] = LoadSoundMem("sound/ShieldHitSE.mp3");
	handle[CharacterHitSE] = LoadSoundMem("sound/CharacterHitSE.mp3");
	handle[AttackSE] = LoadSoundMem("sound/AttackSE.mp3");
	handle[CursorMoveSE] = LoadSoundMem("sound/cursormoveSE.mp3");
	handle[CursorSelectSE] = LoadSoundMem("sound/cursorselectSE.mp3");
	handle[OpenPauseSE] = LoadSoundMem("sound/OpenPauseSE.mp3");
}