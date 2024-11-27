#include"DxLib.h"
#include"InputManager.h"
#include"Camera.h"
#include"SkyDome.h"
#include"Stage.h"
#include"GameScene.h"
#include"Loader.h"
#include"BGMManager.h"
#include"SEManager.h"
#include"TitleScene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleScene::TitleScene()
{
	//�C���X�^���X��
	input = new InputManager();
	camera = new Camera();
	skydome = new SkyDome();
	stage = new Stage();
	bgmmanager = new BGMManager();
	semanager = new SEManager();

	Loader* loader = loader->GetInstance();
	titlelogo = loader->GetHandle(Loader::Kind::TitleLogo);
	
	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleScene::~TitleScene()
{
	bgmmanager->StopBGM();
}

/// <summary>
/// ������
/// </summary>
void TitleScene::Initialize()
{
	camera->Initialize();

	fontsize = 80;
	fontsizechangeflame = 0;
	fontsizechangeflg = false;
	inputpossibleflg = false;

	startpos = VGet(580.0f, 700.0f, 0.0f);
}

/// <summary>
/// �X�V
/// </summary>
/// <returns>���̃V�[��</returns>
SceneBase* TitleScene::Update()
{
	int inputstate = input->GetInputState();//���͏��

	if (inputstate == 0)//���͂�������Γ��͉\�ɕύX
	{
		inputpossibleflg = true;
	}

	if (inputpossibleflg && (InputManager::InputNumber::BButton & inputstate) == InputManager::InputNumber::BButton)//B�{�^��
	{
		semanager->PlaySE(SEManager::SEKind::CrickSE);
		return new GameScene();
	}

	//BGM�Đ�
	bgmmanager->PlayBGM(BGMManager::TitleBGM);

	//�J�����X�V
	camera->UpdateForTitle();

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
		startpos.x += FontScalingSpeed;
		startpos.y += FontScalingSpeed;
	}
	else//�g��
	{
		fontsize += FontScalingSpeed;
		startpos.x -= FontScalingSpeed;
		startpos.y -= FontScalingSpeed;
	}

	return this;
}

/// <summary>
/// �`��
/// </summary>
void TitleScene::Draw()
{
	//���f��
	skydome->Draw();
	stage->Draw();

	//�^�C�g�����S
	DrawExtendGraph(470, 0, 1100, 600, titlelogo, TRUE);

	//�X�^�[�g
	SetFontSize(fontsize);
	DrawString(startpos.x, startpos.y, "B �X�^�[�g", GetColor(127, 255, 0));
}