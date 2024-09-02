#include"DxLib.h"
#include"WoodBoard.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
WoodBoard::WoodBoard()
{
	model = MV1LoadModel("3D/woodboard.mv1");

	Initialize();
}

/// <summary>
/// ������
/// </summary>
void WoodBoard::Initialize()
{
	//�e���f���ݒ�
	for (int i = 0; i < BoardNum; i++)
	{
		eachmodel.push_back(MV1DuplicateModel(model));
	}

	//�e�|�W�V�����ݒ�
	//�^��
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
	//��
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
	//�E
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

	//�p�x�ݒ�
	//�^��
	for (int i = 0; i < 14; i++)
	{
		rotax.push_back(0.0f);
		rotay.push_back(1.55f);
		rotaz.push_back(0.0f);
	}
	//��
	for (int i = 0; i < 24; i++)
	{
		rotax.push_back(0.0f);
		rotay.push_back(0.0f);
		rotaz.push_back(0.0f);
	}
	//�E
	for (int i = 0; i < 24; i++)
	{
		rotax.push_back(0.0f);
		rotay.push_back(0.0f);
		rotaz.push_back(0.0f);
	}

	//�p�x�ݒ�
	for (int i = 0; i < BoardNum; i++)
	{
		MV1SetRotationXYZ(eachmodel[i], VGet(rotax[i], rotay[i], rotaz[i]));
	}

	//�e�R�Â�
	for (int i = 0; i < BoardNum; i++)
	{
		MV1SetPosition(eachmodel[i], pos[i]);
	}
}

/// <summary>
/// �X�V
/// </summary>
void WoodBoard::Update()
{

}

/// <summary>
/// �`��
/// </summary>
void WoodBoard::Draw()
{
	for (int i = 0; i < BoardNum; i++)
	{
		MV1DrawModel(eachmodel[i]);
	}
}