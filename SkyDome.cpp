#include"DxLib.h"
#include"Loader.h"
#include"SkyDome.h"

/// <summary>
/// コンストラクタ
/// </summary>
SkyDome::SkyDome()
{
	Loader* loader = loader->GetInstance();
	model = loader->GetHandle(Loader::Kind::DomeModel);

	MV1SetScale(model, VGet(30, 30, 30));
	MV1SetRotationXYZ(model, VGet(0.0f, 0, 0));
	MV1SetPosition(model, VGet(0, 0, 0));
}

/// <summary>
/// デストラクタ
/// </summary>
SkyDome::~SkyDome()
{
	
}

void SkyDome::Draw()
{
	MV1DrawModel(model);
}