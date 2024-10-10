#include"DxLib.h"
#include"InputManager.h"
#include"TitleScene.h"
#include"ResultScene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ResultScene::ResultScene()
{
	input = new InputManager();

	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ResultScene::~ResultScene()
{

}

/// <summary>
/// ������
/// </summary>
void ResultScene::Initialize()
{
	inputpossibleflg = false;
}

/// <summary>
/// �X�V
/// </summary>
/// <returns>���̃V�[��</returns>
SceneBase* ResultScene::Update()
{
	int inputstate = input->GetInputState();

	if (inputstate == 0)
	{
		inputpossibleflg = true;
	}

	if (inputpossibleflg && (16 & inputstate) == 16)//B�{�^��
	{
		return new TitleScene();
	}

	//�����𖞂����Ă��Ȃ����
	return this;
}

/// <summary>
/// �`��
/// </summary>
void ResultScene::Draw()
{
	SetFontSize(64);
	DrawString(600, 500, "RESULT", GetColor(130, 155, 211));
}