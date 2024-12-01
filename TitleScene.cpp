#include"DxLib.h"
#include"InputManager.h"
#include"Camera.h"
#include"SkyDome.h"
#include"Stage.h"
#include"UI.h"
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
	ui = new UI();

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

	delete input;
	delete camera;
	delete skydome;
	delete stage;
	delete bgmmanager;
	delete semanager;
	delete ui;
}

/// <summary>
/// ������
/// </summary>
void TitleScene::Initialize()
{
	camera->Initialize();
	
	blinkingflg = true;
	blinkingflame = 0;
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

	//�_��
	if (blinkingflame % 15 == 0 && blinkingflame != 0)
	{
		if (blinkingflg)
		{
			blinkingflg = false;
		}
		else
		{
			blinkingflg = true;
		}
		blinkingflame = 0;
	}
	blinkingflame++;

	//BGM�Đ�
	bgmmanager->PlayBGM(BGMManager::TitleBGM);

	//�J�����X�V
	camera->UpdateForTitle();

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
	if (blinkingflg)
	{
		SetFontSize(80);
		DrawString(580, 700, "B �X�^�[�g", GetColor(127, 255, 0));
	}

	//�������
	ui->DrawOperationExplanation();
}