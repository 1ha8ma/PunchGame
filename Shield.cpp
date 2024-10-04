#include<math.h>
#include"DxLib.h"
#include"Utility.h"
#include"Shield.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Shield::Shield()
{
	model = MV1LoadModel("3D/Shield.mv1");

	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Shield::~Shield()
{

}

/// <summary>
/// ������
/// </summary>
void Shield::Initialize()
{
	position = VGet(0.0f, 100.0f, 0.0f);
	angle = 0.0f;

	//capTop = VAdd(position, VGet(0, 50, 0));
	//capBottom = VAdd(position, VGet(0, -50, 0));

	MV1SetPosition(model, position);
}

/// <summary>
/// �X�V
/// </summary>
void Shield::Update(VECTOR characterPosition,float characterangle)
{
	VECTOR tentativepos = characterPosition;//���̃|�W�V����

	//�����ɒǏ]
	tentativepos.x += sin(characterangle) * DistanceWithCharacter;
	tentativepos.z += cos(characterangle) * DistanceWithCharacter;

	//���f���p�x�X�V
	UpdateAngle(characterangle);

	//�J�v�Z���p�x�X�V
	capRight = VAdd(position, VGet(-sin(characterangle - 1.5f) * 150, 200, -cos(characterangle - 1.5f) * 150));
	capLeft = VAdd(position, VGet(sin(characterangle - 1.5f) * 150, 200, cos(characterangle - 1.5f) * 150));

	//�|�W�V�����ɔ��f
	position = tentativepos;
	MV1SetPosition(model, position);
}

/// <summary>
/// �`��
/// </summary>
void Shield::Draw()
{
	//�����蔻��J�v�Z��
	//DrawCapsule3D(capLeft, capRight, CapsuleRadius, 20, GetColor(127, 255, 0), GetColor(0, 255, 255), FALSE);
	MV1DrawModel(model);

}

/// <summary>
/// �p�x�X�V
/// </summary>
void Shield::UpdateAngle(float characterangle)
{
	float difference;//�ڕW�p�x�ƌ��݂̊p�x�̍�

	//�����o��
	difference = characterangle - angle;

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
	angle = characterangle - difference;

	MV1SetRotationXYZ(model, VGet(0.0f, angle - 1.5f + DX_PI_F, 0.0f));
}