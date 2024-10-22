#include<math.h>
#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Utility.h"
#include"Loader.h"
#include"SEManager.h"
#include"Fist.h"

const float Fist::FistCapsuleRadius = 120.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Fist::Fist()
{
	//���N���X�C���X�^���X��
	semanager = new SEManager();

	//���f�����[�h
	Loader* loader = loader->GetInstance();
	model = MV1DuplicateModel(loader->GetHandle(Loader::Kind::FistModel));

	//�G�t�F�N�g���[�h
	firingeffecthandle = loader->GetHandle(Loader::Kind::PunchfiringEffect);

	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Fist::~Fist()
{

}
	
/// <summary>
/// ������
/// </summary>
void Fist::Initialize()
{
	//���f���֌W
	modelangle = 0.0f;
	//position = VGet(0, 400, 0);
	punchingflg = false;

	//�G�t�F�N�g�֌W
	PlayingEffect = -1;
	playfiringefectflg = false;
}

/// <summary>
/// �X�V
/// </summary>
void Fist::Update(VECTOR charapos,float charaangle,bool punchflg,bool shieldhit)
{
	//�G�t�F�N�g�J��������
	Effekseer_Sync3DSetting();
	//�G�t�F�N�g���x�ݒ�
	SetSpeedPlayingEffekseer3DEffect(PlayingEffect, 0.05f);

	PunchMove(punchflg, charaangle, charapos,shieldhit);

	UpdateAngle(charaangle);

	//�G�t�F�N�g�X�V
	UpdateEffekseer3D();

	MV1SetPosition(model, position);
}

/// <summary>
/// �`��
/// </summary>
void Fist::Draw()
{
	if (punchingflg)
	{
		//DrawCapsule3D(capFront, capBack, FistCapsuleRadius, 8, GetColor(127, 255, 0), GetColor(0, 255, 255), FALSE);
		MV1DrawModel(model);
		DrawEffekseer3D();
	}
}

/// <summary>
/// �p���`�̓���
/// </summary>
void Fist::PunchMove(bool punchflg,float charaangle,VECTOR charapos,bool shieldhit)
{
	//�p���`�����Ƃ�
	if (punchflg && punchingflg == false)
	{
		//�v���C���[����|�W�V�������̃R�s�[
		position = charapos;
		position.y = 400.0f;
		punchangle = charaangle;
		//�p���`�̊p�x�ݒ�
		vx = sin(punchangle) * PunchSpeed;
		vz = cos(punchangle) * PunchSpeed;
		position.x += sin(punchangle) * 250.0f;
		position.z += cos(punchangle) * 250.0f;
		//�G�t�F�N�g�ݒ�
		firingefectposition = charapos;
		firingefectposition.x += sin(punchangle) * 250.0f;
		firingefectposition.y = 400.0f;
		firingefectposition.z += cos(punchangle) * 250.0f;
		//SE�Đ�
		semanager->PlaySE(SEManager::SEKind::AttackSE);

		//�t���O�ύX
		punchingflg = true;
		playfiringefectflg = true;
	}

	//�p���`��
	if (punchingflg)
	{
		//�����蔻��J�v�Z���̊p�x�ݒ�
		capFront = VAdd(position, VGet(sin(punchangle) * 200, 0, cos(punchangle) * 200));
		capBack = VAdd(position, VGet(-sin(punchangle) * 100, 0, -cos(punchangle) * 100));

		//�i�܂���
		if (shieldhit==false)
		{
			position.x += vx;
			position.z += vz;
		}

		//���[�V�������I���ƃt���O�ύX
		if (punchflg == false)
		{
			punchingflg = false;
		}
	}
	//�p���`���łȂ��Ƃ�
	else
	{
		//�|�W�V�������L�����Ɠ����ɂ��ăT�C�Y��0�ɂ���
		position = charapos;
		capFront = VAdd(position, VGet(0, 0, 0));
		capBack = VAdd(position, VGet(0, 0, 0));
		playfiringefectflg = false;
	}

	//�G�t�F�N�g�Đ�
	if (playfiringefectflg)
	{
		PlayingEffect = PlayEffekseer3DEffect(firingeffecthandle);
		SetPosPlayingEffekseer3DEffect(PlayingEffect, firingefectposition.x, firingefectposition.y, firingefectposition.z);
		SetRotationPlayingEffekseer3DEffect(PlayingEffect, firingefectangle.x, firingefectangle.y, firingefectangle.z);
		playfiringefectflg = false;
	}
}

/// <summary>
/// �p�x�X�V
/// </summary>
/// <param name="charaangle"></param>
void Fist::UpdateAngle(float charaangle)
{
	float difference;//�ڕW�p�x�ƌ��݂̊p�x�̍�

	//�����o��
	difference = charaangle - modelangle;

	//����������炠������̍���180�x�ȏ�ɂȂ邱�Ƃ͂Ȃ��̂ō���180�x�ȏ�ɂȂ��Ă�����C������
	if (difference < -DX_PI_F)
	{
		difference += DX_TWO_PI_F;
	}
	else if (difference > DX_PI_F)
	{
		difference -= DX_TWO_PI_F;
	}

	//�p�x�̍���0�ɋ߂Â���
	if (difference > 0.0f)//�����}�C�i�X�̏ꍇ
	{
		difference -= AngleSpeed;
		if (difference < 0.0f)
		{
			difference = 0.0f;
		}
	}
	else//�����v���X�̏ꍇ
	{
		difference += AngleSpeed;
		if (difference > 0.0f)
		{
			difference = 0.0f;
		}
	}

	//���f���̊p�x���X�V
	modelangle = charaangle - difference;

	MV1SetRotationXYZ(model, VGet(0.0f, modelangle + DX_PI_F, 0.0f));
	firingefectangle = VGet(0.0f, modelangle + DX_PI_F, 0.0f);
}