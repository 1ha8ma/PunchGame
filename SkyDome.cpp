#include"DxLib.h"
#include"SkyDome.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SkyDome::SkyDome()
{
	model = MV1LoadModel("3D/Dome_X501.x");

	MV1SetScale(model, VGet(30, 30, 30));
	MV1SetRotationXYZ(model, VGet(0.0f, 0, 0));
	MV1SetPosition(model, VGet(0, 0, 0));
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