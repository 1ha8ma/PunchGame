#include"DxLib.h"
#include"Loader.h"
#include"InputManager.h"
#include"Pause.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Pause::Pause()
{
	Loader* loader = loader->GetInstance();
	input = new InputManager();

	textboximage = loader->GetHandle(Loader::Kind::TextBoxImage);

	Initialize();
}

/// <summary>
/// ������
/// </summary>
void Pause::Initialize()
{
	inputpossibleflg = false;
}

/// <summary>
/// �X�V
/// </summary>
/// <returns>�ꎞ��~�I��</returns>
bool Pause::Update()
{
	bool out = false;

	if (input->GetInputState() == 0)
	{
		inputpossibleflg = true;
	}

	if (inputpossibleflg && (32 & input->GetInputState()) == 32)
	{
		out = true;
	}

	return out;
}

/// <summary>
/// �`��
/// </summary>
void Pause::Draw()
{
	DrawExtendGraph(400, 100,1200,600, textboximage, TRUE);
}