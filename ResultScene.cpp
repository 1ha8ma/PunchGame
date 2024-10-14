#include<math.h>
#include"DxLib.h"
#include"Camera.h"
#include"InputManager.h"
#include"ResultScene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ResultScene::ResultScene()
{
	input = new InputManager();

	ribbonimage = LoadGraph("2D/ribbon.png");
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

	//�|�W�V���������
	VECTOR copypos = camera->GetPosition();

	//Lerp�v�Z
	copypos = VAdd(copypos, VScale((VSub(targetposition, copypos)), t));

	//�|�W�V�������Z�b�g
	camera->SetPosition(copypos);

	//Lerp�̕����̊�����ڕW�ɋ߂Â���
	t += 0.01;

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
	DrawString(130, 110, "WINNER", GetColor(255, 215, 0));
}