#pragma once
#include<map>

class Loader
{
public:
	static Loader* GetInstance();//�C���X�^���X�Q�b�g

	/// <summary>
	/// ���f�����̃f�[�^�̎��
	/// </summary>
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

		//BGM
		TitleBGM,//�^�C�g��BGM
		GameBGM,//�Q�[����BGM
		ResultBGM,//���U���gBGM

		//SE
		StartSceneSE,//�X�^�[�g���oSE
		StartSE,//�X�^�[�g�\����SE
		CountSE,//�J�E���gSE
		ShieldHitSE,//���Փ�SE
		CharacterHitSE,//�L�����N�^�[�ɓ�����������SE
		AttackSE,//�U����SE
		CrickSE,//����SE
	};

	//�n���h���}�b�v�Q�b�g
	int GetHandle(Kind kind) { return handle[kind]; }
	//���f���������[�h
	void LoadModel();

private:
	static Loader* loader_;//���[�_�[�N���X�C���X�^���X
	//�n���h�������}�b�v
	std::map<Kind, int> handle;

};