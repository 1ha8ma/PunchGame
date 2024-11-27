#include<math.h>
#include"DxLib.h"
#include"Utility.h"
#include"Loader.h"
#include"InputManager.h"
#include"SEManager.h"
#include"StartScene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
StartScene::StartScene(VECTOR playerpos)
{
	Loader* loader = loader->GetInstance();

	image.clear();
	image.push_back(loader->GetHandle(Loader::Kind::NumImage1));
	image.push_back(loader->GetHandle(Loader::Kind::NumImage2));
	image.push_back(loader->GetHandle(Loader::Kind::NumImage3));
	startimage = loader->GetHandle(Loader::Kind::StartImage);
	playerarrow = loader->GetHandle(Loader::Kind::PlayerArrowImage);

	semanager = new SEManager();
	semanager->PlaySE(SEManager::SEKind::StartSceneSE);
	input = new InputManager();

	Initialize(playerpos);
}

/// <summary>
/// ������
/// </summary>
void StartScene::Initialize(VECTOR playerpos)
{
	countflg = false;
	countflame = 0;
	cameraangle = 0.0f;
	lookpos = VGet(0, 600, 0);
	count = 3;
	sizechangeflg = false;
	sizechangeflame = 0;
	startseflg = false;

	//�|�W�V����
	numberlx = 800;
	numberly = 400;
	numberrx = 859;
	numberry = 480;

	//���|�W�V����
	playerarrowpos = VAdd(playerpos, VGet(0.0f, 900.0f, 0.0f));
}

/// <summary>
/// �X�V
/// </summary>
bool StartScene::Update()
{
	bool scenechange = false;

	//����
	if (!countflg)
	{
		cameraangle += 0.009f;
		camerapos = VGet(0, 600, 0);
		lookpos.x = sin(cameraangle);
		lookpos.z = cos(cameraangle);
	}

	//���������
	if ((cameraangle >= DX_PI_F * 2 && !countflg) || !countflg && (InputManager::InputNumber::AButton & input->GetInputState()) == InputManager::InputNumber::AButton)
	{
		semanager->PlaySE(SEManager::SEKind::StartCountSE);

		//�J����
		cameraangle = 0.0f;
		camerapos = VGet(0, 2500, -2000);
		lookpos = VGet(0, 0, 0);

		playerarrowpos = VAdd(playerarrowpos, VGet(210, 200, 0));

		countflg = true;
	}

	//�J�E���g�ɓ�������
	if (countflg)
	{
		countflame++;
	}

	if (countflg && countflame == 350)
	{
		scenechange = true;
	}

	return scenechange;
}

/// <summary>
/// �`��
/// </summary>
void StartScene::Draw()
{
	if (countflg)
	{
		//100�t���[�����ɉ摜�؂�ւ�
		if (countflame != 0 && countflame % 100 == 0)
		{
			sizechangeflame = 0;
			sizechangeflg = false;
			numberlx = 800;
			numberly = 400;
			numberrx = 859;
			numberry = 480;
			if (count >= 2)
			{
				semanager->PlaySE(SEManager::SEKind::StartCountSE);
			}
			count--;
		}

		//�T�C�Y�̕ύX�t���O
		if (sizechangeflame % 50 == 0 && sizechangeflame % 100 != 0)
		{
			sizechangeflg = true;
		}

		//�����̃T�C�Y�ύX
		if (!sizechangeflg)
		{
			numberlx -= ScalingSpeed;
			numberly -= ScalingSpeed;
			numberrx += ScalingSpeed;
			numberry += ScalingSpeed;
		}
		else
		{
			numberlx += ScalingSpeed;
			numberly += ScalingSpeed;
			numberrx -= ScalingSpeed;
			numberry -= ScalingSpeed;
		}	

		//�����J�E���g
		if (count >= 1)
		{
			DrawExtendGraph(numberlx, numberly, numberrx, numberry, image[count - 1], TRUE);
		}

		//�X�^�[�g
		if (300 < countflame && countflame <= 350)
		{
			if (!startseflg)
			{
				semanager->PlaySE(SEManager::SEKind::StartSE);
				startseflg = true;
			}
			DrawGraph(650, 370, startimage, TRUE);
		}

		sizechangeflame++;
	}
	else
	{
		SetFontSize(50);
		DrawString(1300, 800, "A �X�L�b�v", GetColor(127, 255, 0));
	}

	DrawBillboard3D(playerarrowpos, 0.5f, 0.5f, 500.0f, 0.0f, playerarrow, TRUE);
}