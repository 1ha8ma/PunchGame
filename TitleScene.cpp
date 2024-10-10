#include"DxLib.h"
#include"InputManager.h"
#include"GameScene.h"
#include"TitleScene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleScene::TitleScene()
{
	input = new InputManager();

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
	inputpossibleflg = false;
}

/// <summary>
/// �X�V
/// </summary>
/// <returns>���̃V�[��</returns>
SceneBase* TitleScene::Update()
{
	int inputstate = input->GetInputState();

	if (inputstate == 0)
	{
		inputpossibleflg = true;
	}

	if (inputpossibleflg && (16 & inputstate) == 16)//B�{�^��
	{
		return new GameScene();
	}

	return this;
}

/// <summary>
/// �`��
/// </summary>
void TitleScene::Draw()
{
	SetFontSize(64);
	DrawString(600, 500, "TITLE", GetColor(190, 155, 211));
}