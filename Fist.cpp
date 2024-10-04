#include<math.h>
#include"DxLib.h"
#include"Utility.h"
#include"Fist.h"

const float Fist::FistCapsuleRadius = 120.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Fist::Fist()
{
	//���f�����[�h
	model = MV1LoadModel("3D/fist.mv1");

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
	modelangle = 0.0f;
	position = VGet(0, 400, 0);
	punchingflg = false;

	//�����蔻��J�v�Z��
	//capFront = VAdd(position, VGet(0, 0, 0));
	//capBack = VAdd(position, VGet(0, 0, 0));
}

/// <summary>
/// �X�V
/// </summary>
void Fist::Update(VECTOR charapos,float charaangle,bool punchflg,bool shieldhit)
{
	PunchMove(punchflg, charaangle, charapos,shieldhit);

	UpdateAngle(charaangle);

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
		//�t���O�ύX
		punchingflg = true;
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
	//�p���`���łȂ���΃|�W�V����������
	else
	{
		position = VGet(NULL, NULL, NULL);
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
}