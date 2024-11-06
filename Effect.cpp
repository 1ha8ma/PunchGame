#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Loader.h"
#include"Effect.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Effect::Effect()
{
	Loader* loader = loader->GetInstance();

	Effecthandle[EffectKind::Attack] = loader->GetHandle(Loader::Kind::PunchfiringEffect);
	Effecthandle[EffectKind::CharacterHit] = loader->GetHandle(Loader::Kind::PlayerhitEffect);
	Effecthandle[EffectKind::ShieldHit] = loader->GetHandle(Loader::Kind::ShieldhitEffect);

	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Effect::~Effect()
{
	//�G�t�F�N�g�I��
	DrawEffekseer3D_End();
}

/// <summary>
/// ������
/// </summary>
void Effect::Initialize()
{
	PlayingEffectKind.clear();
	PlayingEffecthandle.clear();
	PlayingEffectSize.clear();
}

/// <summary>
/// �G�t�F�N�g�Đ��w��
/// </summary>
/// <param name="kind">�G�t�F�N�g�̎��</param>
/// <param name="playposition">�Đ��ʒu</param>
/// <param name="initsize">�ŏ��̃T�C�Y</param>
/// <param name="playangle">�Đ��p�x</param>
/// <param name="playspeed">�Đ����x</param>
void Effect::PlayEffect(EffectKind kind, VECTOR playposition,VECTOR initsize, float playangle,float playspeed)
{
	//�Đ����Ă���G�t�F�N�g��ǉ�
	PlayingEffectKind.push_back(Effecthandle[kind]);
	//�n���h���ǉ�
	PlayingEffecthandle.push_back(PlayEffekseer3DEffect(Effecthandle[kind]));

	//�T�C�Y�ݒ�
	PlayingEffectSize.push_back(initsize);
	SetScalePlayingEffekseer3DEffect(PlayingEffecthandle.back(), PlayingEffectSize.back().x, PlayingEffectSize.back().y, PlayingEffectSize.back().z);
	//�G�t�F�N�g���x�ݒ�
	SetSpeedPlayingEffekseer3DEffect(PlayingEffecthandle.back(), playspeed);
	//�\���p�x�ݒ�
	SetRotationPlayingEffekseer3DEffect(PlayingEffecthandle.back(), 0.0f, playangle, 0.0f);
	//�|�W�V�������f
	SetPosPlayingEffekseer3DEffect(PlayingEffecthandle.back(), playposition.x, playposition.y, playposition.z);
}

/// <summary>
/// �X�V
/// </summary>
void Effect::Update()
{
	for (int i = 0; i < PlayingEffecthandle.size(); i++)
	{
		//�Đ����̃G�t�F�N�g�����Փ˂�������T�C�Y��傫������
		if (PlayingEffectKind[i] == Effecthandle[EffectKind::ShieldHit])
		{
			PlayingEffectSize[i] = VAdd(PlayingEffectSize[i], VGet(ExpansionSpeed, ExpansionSpeed, ExpansionSpeed));
		}

		//�T�C�Y�K�p
		SetScalePlayingEffekseer3DEffect(PlayingEffecthandle[i], PlayingEffectSize[i].x, PlayingEffectSize[i].y, PlayingEffectSize[i].z);

		//�Đ��I�����Ă�����Đ�������폜
		if (IsEffekseer3DEffectPlaying(PlayingEffecthandle[i]) == -1)
		{
			PlayingEffectKind.erase(PlayingEffectKind.begin() + i);
			PlayingEffecthandle.erase(PlayingEffecthandle.begin() + i);
			PlayingEffectSize.erase(PlayingEffectSize.begin() + i);
		}
	}
}

/// <summary>
/// �`��
/// </summary>
void Effect::Draw()
{
	DrawEffekseer3D();
}