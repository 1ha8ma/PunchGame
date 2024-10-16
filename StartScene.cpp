#include<math.h>
#include"DxLib.h"
#include"Utility.h"
#include"Loader.h"
#include"StartScene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
StartScene::StartScene()
{
	Loader* loader = loader->GetInstance();

	image.clear();
	image.push_back(loader->GetHandle(Loader::Kind::NumImage1));
	image.push_back(loader->GetHandle(Loader::Kind::NumImage2));
	image.push_back(loader->GetHandle(Loader::Kind::NumImage3));
	startimage = loader->GetHandle(Loader::Kind::StartImage);

	Initialize();
}

/// <summary>
/// ������
/// </summary>
void StartScene::Initialize()
{
	countflg = false;
	countflame = 0;
	cameraangle = 0.0f;
	lookpos = VGet(0, 600, 0);
	count = 3;
	sizechangeflg = false;
	sizechangeflame = 0;

	//�|�W�V����
	numberlx = 800;
	numberly = 400;
	numberrx = 859;
	numberry = 480;
}

/// <summary>
/// �X�V
/// </summary>
bool StartScene::Update()
{
	bool scenechange = false;

	if (countflg == false)
	{
		cameraangle += 0.008f;
		camerapos = VGet(0, 600, 0);
		lookpos.x = sin(cameraangle);
		lookpos.z = cos(cameraangle);
	}



	if (cameraangle >= DX_PI_F * 2)
	{
		countflg = true;
	}

	if (countflg)
	{
		cameraangle = 0.0f;
		camerapos = VGet(0, 2000, -1500);
		lookpos = VGet(0, 0, 0);

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
			count--;
		}

		if (sizechangeflame % 50 == 0 && sizechangeflame % 100 != 0)
		{
			sizechangeflg = true;
		}

		if (sizechangeflg == false)
		{
			numberlx -= 1;
			numberly -= 1;
			numberrx += 1;
			numberry += 1;
		}
		else
		{
			numberlx += 1;
			numberly += 1;
			numberrx -= 1;
			numberry -= 1;
		}	

		if (count >= 1)
		{
			DrawExtendGraph(numberlx, numberly, numberrx, numberry, image[count - 1], TRUE);
		}

		if (300 < countflame && countflame <= 350)
		{
			DrawGraph(650, 370, startimage, TRUE);
		}

		sizechangeflame++;
	}
}