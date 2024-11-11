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
	//��
	//const int FPS = 144;//�z��w���c
	//LONGLONG PrevTime = GetNowHiPerformanceCount();//���݂̎��Ԃ��擾
	//LONGLONG NextAddTime = 0;//���܂莞��
	//int NextUpdateLoopNum = 1;//���̍X�V���[�v�̌Ăяo����

	//�E�B���h�E���[�h
	SetGraphMode(SCREEN_W, SCREEN_H, 32);
	ChangeWindowMode(TRUE);//����ʁFTRUE �S��ʁFFALSE
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

		//�X�V
		//for (int i = 0; i < NextUpdateLoopNum; i++)
		//{
			game->Update();
		//}
		//�`��
		game->Draw();

		ScreenFlip();

		//if (!GetActiveFlag())
		//{
		//	//�\�t�g�̃E�B���h�E���A�N�e�B�u�ɂȂ�܂ő҂�
		//	while (ProcessMessage() == 0 && !GetActiveFlag())
		//	{
		//		Sleep(1);
		//	}

		//	//�A�N�e�B�u�ɂȂ����玞�Ԋ֌W�̃p�����[�^�����������Ď��̃��[�v�ɐi��
		//	PrevTime = GetNowHiPerformanceCount();
		//	NextAddTime = 0;
		//	NextUpdateLoopNum = 1;
		//}
		//else
		//{
		//	LONGLONG NowTime;
		//	LONGLONG LoopTime;

		//	//���݂̎��Ԃ��擾
		//	NowTime = GetNowHiPerformanceCount();

		//	//�O��̎��ԂƂ̍������v�Z
		//	LoopTime = NowTime - PrevTime;

		//	//�o�߂������Ԃ�1�t���[�����ɖ����Ȃ��ꍇ��1�t���[�����̎��Ԃ��o�߂���܂ő҂�
		//	if (LoopTime < 1000000 / FPS)
		//	{
		//		while (ProcessMessage() == 0 && LoopTime < 1000000 / FPS)
		//		{
		//			NowTime = GetNowHiPerformanceCount();
		//			LoopTime = NowTime - PrevTime;
		//		}
		//	}

		//	//���̃��[�v�Ŏ��s����Update�֐��̌Ăяo���񐔂��Z�o
		//	NextAddTime = (LoopTime + NextAddTime) - NextUpdateLoopNum * (1000000 / FPS);

		//	//���̃��[�v�ł̌v�Z�Ɏg�p���邽�߂̗]�莞��
		//	LoopTime - NextUpdateLoopNum * (1000000 / FPS);

		//	//����̎��Ԃ�ۑ����Ă���
		//	PrevTime = NowTime;
		//}

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