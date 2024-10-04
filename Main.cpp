#include"DxLib.h"
#include"Utility.h"
#include"GameManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/////////////////////////
	// ��{�ݒ�
	/////////////////////////
	//�E�B���h�E���[�h
	SetGraphMode(SCREEN_W, SCREEN_H, 32);
	ChangeWindowMode(TRUE);//���쎞�FTRUE �{�ԁFFALSE
	//���C�u����������
	DxLib_Init();
	//�E�B���h�E���[�h�����ύX
	SetMainWindowText("�Ԃ���уp���`");
	//�_�u���o�b�t�@�����O��L��
	SetDrawScreen(DX_SCREEN_BACK);

	////////////////////////
	// �Q�[��������
	////////////////////////
	ClearDrawScreen();
	SetFontSize(64);
	//DrawString(600, SCREEN_H / 2, "NowLoading�E�E�E", GetColor(0, 124, 98), TRUE);
	ScreenFlip();
	//�Q�[���}�l�[�W���[�C���X�^���X��
	GameManager* game = new GameManager();

	////////////////////////
	// �Q�[�����[�v
	////////////////////////
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{
		ClearDrawScreen();

		game->Update();
		game->Draw();

		ScreenFlip();

		//�E�B���h�E���b�Z�[�W����
		if (ProcessMessage() < 0)
		{
			break;
		}
		//ESC�I��
		else if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}
	}

	//�Q�[���I��
	DxLib_End();

	return 0;
}