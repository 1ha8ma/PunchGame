#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Utility.h"
#include"Loader.h"
#include"FPS.h"
#include"GameManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/////////////////////////
	// ��{�ݒ�
	/////////////////////////
	//�E�B���h�E���[�h
	SetGraphMode(SCREEN_W, SCREEN_H, 32);
	SetWaitVSyncFlag(FALSE);//���������ݒ� TRUE : ���� FALSE : �Ȃ�
	ChangeWindowMode(FALSE);//����ʁFTRUE �S��ʁFFALSE
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
	//�t�H���g�ݒ�
	ChangeFont("851�e�K�L�J�N�b�g", DX_CHARSET_DEFAULT);

	//���f�������[�h
	Loader* loader = Loader::GetInstance();
	loader->LoadModel();

	//�C���X�^���X��
	FPS* fps = new FPS();
	GameManager* game = new GameManager();

	////////////////////////
	// �Q�[�����[�v
	////////////////////////
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//��ʃN���A
		ClearDrawScreen();

		//FPS�X�V
		fps->Update();

		//�X�V
		game->Update();
		//�`�揈��
		game->Draw();
		
		//�`��
		ScreenFlip();

		//FPS�ҋ@
		fps->Wait();
	}

	//�Q�[���I��
	Effkseer_End();
	DxLib_End();

	return 0;
}