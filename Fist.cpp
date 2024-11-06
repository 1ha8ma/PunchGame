#include<math.h>
#include"DxLib.h"
#include"Utility.h"
#include"Loader.h"
#include"Effect.h"
#include"SEManager.h"
#include"Fist.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Fist::Fist()
{
	//���N���X�C���X�^���X��
	semanager = new SEManager();
	effect = new Effect();

	//���f�����[�h
	Loader* loader = loader->GetInstance();
	model = MV1DuplicateModel(loader->GetHandle(Loader::Kind::FistModel));

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
	punchingflg = false;
	size = 1.0f;

	//�G�t�F�N�g�֌W
	playfiringefectflg = false;
}

/// <summary>
/// �X�V
/// </summary>
void Fist::Update(VECTOR charapos,float charaangle,bool attackflg,bool shieldhit)
{
	//�p���`�̓���
	PunchMove(attackflg, charaangle, charapos,shieldhit);

	//�|�W�V�������f
	MV1SetPosition(model, position);
}

/// <summary>
/// �`��
/// </summary>
void Fist::Draw()
{
	if (punchingflg)
	{
		DrawCapsule3D(capFront, capBack, FistCapsuleRadius, 8, GetColor(127, 255, 0), GetColor(0, 255, 255), FALSE);
		MV1DrawModel(model);
		effect->Draw();
	}
}

/// <summary>
/// �p���`�̓���
/// </summary>
void Fist::PunchMove(bool attackflg,float charaangle,VECTOR charapos,bool shieldhit)
{
	//�p���`�����Ƃ�
	if (attackflg && punchingflg == false)
	{
		//�v���C���[����|�W�V�������̃R�s�[
		position = charapos;
		position.y = 400.0f;
		punchangle = charaangle;
		//�p���`�̊p�x�ݒ�
		velocity.x = sin(punchangle) * PunchSpeed;
		velocity.y = 0.0f;
		velocity.z = cos(punchangle) * PunchSpeed;
		position.x += sin(punchangle) * 250.0f;
		position.z += cos(punchangle) * 250.0f;
		modelangle = charaangle;
		MV1SetRotationXYZ(model, VGet(0.0f, modelangle + DX_PI_F, 0.0f));
		//�T�C�Y�ݒ�
		size = 0.1f;
		//�G�t�F�N�g�ݒ�
		effect->PlayEffect(Effect::EffectKind::Attack, VGet(charapos.x + sin(punchangle) * 250.0f, 400.0f, charapos.z + cos(punchangle) * 250.0f), VGet(1, 1, 1), modelangle, 0.5f);
		//SE�Đ�
		semanager->PlaySE(SEManager::SEKind::AttackSE);

		shieldhitflg = false;

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
		if (shieldhitflg == false)
		{
			position = VAdd(position, velocity);
		}

		//���񂾂�T�C�Y��傫������
		if (shieldhitflg == false && size < 1.0f)
		{
			size += 0.07f;
			if (size > 1.0f)
			{
				size = 1.0f;
			}
		}
		MV1SetScale(model, VGet(size, size, size));

		//�������ɓ��������炾�񂾂񏬂������ď���
		if (shieldhit)
		{
			shieldhitflg = true;
		}
		if (shieldhitflg)
		{
			if (size > 0.0f)
			{
				size -= 0.07;
			}
			if (size < 0.0f)
			{
				size = 0.0f;
			}
		}

		//���[�V�������I���ƃt���O�ύX
		if (attackflg == false)
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
		effect->Update();
	}
}