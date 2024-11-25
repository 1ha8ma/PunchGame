#include<math.h>
#include"DxLib.h"
#include"Camera.h"
#include"InputManager.h"
#include"Loader.h"
#include"BGMManager.h"
#include"ResultScene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ResultScene::ResultScene()
{
	input = new InputManager();
	bgmmanager = new BGMManager();
	Loader* loader = loader->GetInstance();

	ribbonimage = loader->GetHandle(Loader::Kind::RibbonImage);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ResultScene::~ResultScene()
{
	bgmmanager->StopBGM();
}

/// <summary>
/// ������
/// </summary>
/// <param name="position">���҃|�W�V����</param>
/// <param name="angle">���Ҋp�x</param>
void ResultScene::Initialize(VECTOR position, float angle)
{
	inputpossibleflg = false;
	t = 0;

	winnerposition = position;
	winnerangle = angle;

	targetposition.x = winnerposition.x + sin(winnerangle) * 1000;
	targetposition.z = winnerposition.z + cos(winnerangle) * 1000;
	targetposition.y = winnerposition.y + 500;

	flame = 0;

	fontsize = 64;
	fontsizechangeflame = 0;
	fontsizechangeflg = false;
	explanationpos = VGet(1100, 750, 0);
}

/// <summary>
/// �X�V
/// </summary>
bool ResultScene::Update(Camera*& camera)
{
	int inputstate = input->GetInputState();
	bool scenechange = false;

	if (inputstate == 0)
	{
		inputpossibleflg = true;
	}

	//BGM�Đ�
	bgmmanager->PlayBGM(BGMManager::BGMKind::ResultBGM);

	//�|�W�V���������
	VECTOR copypos = camera->GetPosition();
	if (flame < 130)
	{
		copypos.x = winnerposition.x + sin(winnerangle + DX_PI_F / 2) * 1400;
		copypos.z = winnerposition.z + cos(winnerangle + DX_PI_F / 2) * 1400;
		copypos.y = winnerposition.y + 1200;
	}
	else if (130 <= flame && flame <= 260)
	{
		copypos.x = winnerposition.x + sin(winnerangle - DX_PI_F / 2) * 1400;
		copypos.z = winnerposition.z + cos(winnerangle - DX_PI_F / 2) * 1400;
		copypos.y = winnerposition.y + 1200;
	}
	else
	{
		//Lerp�v�Z
		copypos = VAdd(copypos, VScale((VSub(targetposition, copypos)), t));
		//Lerp�̕����̊�����ڕW�ɋ߂Â���
		t += 0.005;
	}

	//�|�W�V�������Z�b�g
	camera->SetPosition(copypos);

	//�t���[�����Z
	flame++;

	//�ړI�n�ɃJ����������������
	if (t >= 1)
	{
		//�t�H���g�T�C�Y�X�V
		fontsizechangeflame++;

		if (fontsizechangeflame != 0 && fontsizechangeflame % 30 == 0)
		{
			//�g��k�����
			if (fontsizechangeflg)
			{
				fontsizechangeflg = false;
			}
			else
			{
				fontsizechangeflg = true;
			}

			fontsizechangeflame = 0;
		}

		if (fontsizechangeflg)//�k��
		{
			fontsize -= FontScalingSpeed;
			explanationpos.x += FontScalingSpeed;
			explanationpos.y += FontScalingSpeed;
		}
		else//�g��
		{
			fontsize += FontScalingSpeed;
			explanationpos.x -= FontScalingSpeed;
			explanationpos.y -= FontScalingSpeed;
		}
	}

	//����ŃV�[���ύX
	if (t >= 1 && inputpossibleflg && inputstate && (InputManager::InputNumber::Decision & inputstate) == InputManager::InputNumber::Decision)
	{
		scenechange = true;
	}

	return scenechange;
}

/// <summary>
/// �`��
/// </summary>
void ResultScene::Draw()
{
	DrawGraph(0, -100, ribbonimage, TRUE);
	SetFontSize(64);
	DrawString(150, 110, "WINNER", GetColor(255, 215, 0));

	if (t >= 1)
	{
		SetFontSize(fontsize);
		DrawString(explanationpos.x, explanationpos.y, "A �^�C�g��", GetColor(127, 255, 0));
	}
}