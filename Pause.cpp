#include"DxLib.h"
#include"Loader.h"
#include"InputManager.h"
#include"SEManager.h"
#include"Pause.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Pause::Pause()
{
	Loader* loader = loader->GetInstance();
	input = new InputManager();
	semanager = new SEManager();

	textboximage = loader->GetHandle(Loader::Kind::TextBoxImage);
	button = loader->GetHandle(Loader::Kind::ButtonImage);
	button_hover = loader->GetHandle(Loader::Kind::BUttonHoverImage);

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
int Pause::Update()
{
	int outcursor = CursorPoint::None;

	//�A�����͖h�~
	if (!((InputManager::InputNumber::Start & input->GetInputState()) == InputManager::InputNumber::Start))
	{
		inputpossibleflg = true;
	}

	//�J�[�\���ړ�
	if (cursor != CursorPoint::TitleReturn && (InputManager::InputNumber::Down & input->GetInputState()) == InputManager::InputNumber::Down)
	{
		cursor = CursorPoint::TitleReturn;
		semanager->PlaySE(SEManager::SEKind::CursorMoveSE);
	}
	if (cursor != CursorPoint::GameReturn && (InputManager::InputNumber::Up & input->GetInputState()) == InputManager::InputNumber::Up)
	{
		cursor = CursorPoint::GameReturn;
		semanager->PlaySE(SEManager::SEKind::CursorMoveSE);
	}

	//�ꎞ��~����
	if (cursor != CursorPoint::None && (InputManager::InputNumber::BButton & input->GetInputState()) == InputManager::InputNumber::BButton)
	{
		outcursor = cursor;
		semanager->PlaySE(SEManager::SEKind::CursorSelectSE);
	}

	return outcursor;
}

/// <summary>
/// �`��
/// </summary>
void Pause::Draw()
{
	//�w�i
	DrawExtendGraph(350, 100,1250,700, textboximage, TRUE);
	//�ꎞ��~����
	SetFontSize(100);
	DrawString(590, 270, "�ꎞ��~", GetColor(255, 20, 147));
	//�{�^��
	switch (cursor)
	{
	case(CursorPoint::GameReturn):
	{
		DrawExtendGraph(ButtonPos1.x, ButtonPos1.y, ButtonPos1.x + ButtonWidth, ButtonPos1.y + ButtonHeight, button_hover, TRUE);
		DrawExtendGraph(ButtonPos2.x, ButtonPos2.y, ButtonPos2.x + ButtonWidth, ButtonPos2.y + ButtonHeight, button, TRUE);
	}
	break;
	case(CursorPoint::TitleReturn):
	{
		DrawExtendGraph(ButtonPos1.x, ButtonPos1.y, ButtonPos1.x + ButtonWidth, ButtonPos1.y + ButtonHeight, button, TRUE);
		DrawExtendGraph(ButtonPos2.x, ButtonPos2.y, ButtonPos2.x + ButtonWidth, ButtonPos2.y + ButtonHeight, button_hover, TRUE);
	}
	break;
	}
	SetFontSize(40);
	DrawString(ButtonPos1.x + 220, ButtonPos1.y + 5, "�Q�[���ɖ߂�", GetColor(255, 51, 51));
	DrawString(ButtonPos2.x + 200, ButtonPos2.y + 5, "�^�C�g���ɖ߂�", GetColor(255, 51, 51));
}