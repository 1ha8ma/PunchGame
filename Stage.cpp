#include"DxLib.h"
#include"Loader.h"
#include"Stage.h"

//�X�e�[�W�̊e���W
const float Stage::StageRight = 1550.0f;//�E
const float Stage::StageLeft = -1550.0f;//��
const float Stage::StageTop = 1650.0f;//��
const float Stage::StageBottom = -1400.0f;//��

/// <summary>
/// �R���X�g���N�^
/// </summary>
Stage::Stage()
{
	Loader* loader = loader->GetInstance();
	model = loader->GetHandle(Loader::Kind::StageModel);

	Initialize();
}

/// <summary>
/// ������
/// </summary>
void Stage::Initialize()
{
	//��]
	MV1SetRotationXYZ(model, VGet(0.0f, DX_PI_F / 2, 0.0f));
	//�|�W�V�����ݒ�
	MV1SetPosition(model, VGet(0, 0, 200));
}

/// <summary>
/// �`��
/// </summary>
void Stage::Draw()
{
	MV1DrawModel(model);
}