#include"DxLib.h"
#include"Loader.h"
#include"SkyDome.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SkyDome::SkyDome()
{
	Loader* loader = loader->GetInstance();
	model = loader->GetHandle(Loader::Kind::DomeModel);

	MV1SetScale(model, VGet(32, 32, 32));
	MV1SetRotationXYZ(model, VGet(0.0f, 0.0f, 0.0f));
	MV1SetPosition(model, VGet(0.0f, 0.0f, 0.0f));
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SkyDome::~SkyDome()
{
	
}

void SkyDome::Draw()
{
	MV1DrawModel(model);
}