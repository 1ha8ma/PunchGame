#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Utility.h"
#include"Loader.h"
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
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	DxLib_Init();
	Effekseer_Init(8000);
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();
	SetUseZBuffer3D(TRUE);

	//�E�B���h�E���[�h�����ύX
	SetMainWindowText("�Ԃ���уp���`");
	//�_�u���o�b�t�@�����O��L��
	SetDrawScreen(DX_SCREEN_BACK);

	////////////////////////
	// �Q�[��������
	////////////////////////
	Loader* loader = Loader::GetInstance();
	loader->LoadModel();

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
	Effkseer_End();
	DxLib_End();

	return 0;
}