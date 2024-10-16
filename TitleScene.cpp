#include"DxLib.h"
#include"InputManager.h"
#include"Camera.h"
#include"SkyDome.h"
#include"WoodBoard.h"
#include"GameScene.h"
#include"Loader.h"
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
	woodboard = new WoodBoard();

	Loader* loader = loader->GetInstance();
	titlelogo = loader->GetHandle(Loader::Kind::TitleLogo);
	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleScene::~TitleScene()
{

}

/// <summary>
/// ������
/// </summary>
void TitleScene::Initialize()
{
	camera->Initialize();

	inputpossibleflg = false;
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

	if (inputpossibleflg && (16 & inputstate) == 16)//B�{�^��
	{
		return new GameScene();
	}

	//�N���X�X�V

	camera->UpdateForTitle();

	return this;
}

/// <summary>
/// �`��
/// </summary>
void TitleScene::Draw()
{
	skydome->Draw();
	woodboard->Draw();

	DrawExtendGraph(470, 0,1100,600, titlelogo, TRUE);

	SetFontSize(80);
	ChangeFont("851�e�K�L�J�N�b�g",DX_CHARSET_DEFAULT);
	DrawString(600, 700, "�X�^�[�g", GetColor(127, 255, 0));
}