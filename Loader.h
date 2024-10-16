#pragma once
#include<map>

class Loader
{
public:
	static Loader* GetInstance();//�C���X�^���X�Q�b�g

	enum Kind
	{
		//3D
		PlayerModel,//�v���C���[���f��
		Enemy1Model,//�G1���f��
		Enemy2Model,//2
		Enemy3Model,//3
		ShieldModel,//�����f��
		FistModel,//�����f��
		WoodBoardModel,//�؂̔��f��
		DomeModel,//�X�J�C�h�[�����f��

		//2D
		TitleLogo,//�^�C�g�����S
		RibbonImage,//���{���摜
		GamePadImage,//�Q�[���p�b�h�摜
		StartImage,//�X�^�[�g�摜
		NumImage1,//1�摜
		NumImage2,//2
		NumImage3,//3

		//�G�t�F�N�g
		PlayerhitEffect,//�v���C���[�Փ˃G�t�F�N�g
		PunchfiringEffect,//�p���`�����Ƃ��̃G�t�F�N�g
		ShieldhitEffect,//���Փˎ��̃G�t�F�N�g
	};

	//�n���h���}�b�v�Q�b�g
	int GetHandle(Kind kind) { return handle[kind]; }
	void LoadModel();


private:
	static Loader* loader_;//���[�_�[�N���X�C���X�^���X
	//�n���h�������}�b�v
	std::map<Kind, int> handle;

	//3D
	//static int PlayerModel;//�v���C���[���f��
	//static int Enemy1Model;//�G1���f��
	//static int Enemy2Model;//2
	//static int Enemy3Model;//3
	//static int ShieldModel;//�����f��
	//static int FistModel;//�����f��
	//static int WoodBoardModel;//�؂̔��f��
	//static int DomeModel;//�X�J�C�h�[�����f��

	//2D
	/*static int TitleLogo;
	static int RibbonImage;
	static int GamePadImage;
	static int StartImage;
	static int NumImage1;
	static int NumImage2;
	static int NumImage3;*/

	//�G�t�F�N�g
	/*static int PlayerhitEffect;
	static int PunchfiringEffect;
	static int ShieldhitEffect;*/

};