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

	//Lerp�v�Z
	copypos = VAdd(copypos, VScale((VSub(targetposition, copypos)), t));

	//�|�W�V�������Z�b�g
	camera->SetPosition(copypos);

	//Lerp�̕����̊�����ڕW�ɋ߂Â���
	t += 0.005;

	if (t >= 1 && inputpossibleflg && inputstate && (16 & inputstate) == 16)
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
}