#include<math.h>
#include"DxLib.h"
#include"Utility.h"
#include"Loader.h"
#include"Shield.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Shield::Shield()
{
	Loader* loader = loader->GetInstance();
	model = MV1DuplicateModel(loader->GetHandle(Loader::Kind::ShieldModel));
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
void Shield::Initialize(VECTOR charaposition,float characterangle)
{
	//�|�W�V�����R�s�[
	position = charaposition;

	//�|�W�V�����ݒ�
	position.x += sin(characterangle) * DistanceWithCharacter;
	position.z += cos(characterangle) * DistanceWithCharacter;

	capRight = VAdd(position, VGet(-sin(characterangle - 1.5f) * 150, 200, -cos(characterangle - 1.5f) * 150));
	capLeft = VAdd(position, VGet(sin(characterangle - 1.5f) * 150, 200, cos(characterangle - 1.5f) * 150));

	//�p�x�ݒ�
	angle = characterangle;

	//�p�x�A�|�W�V�������f
	MV1SetRotationXYZ(model, VGet(0.0f, angle - 1.5f + DX_PI_F, 0.0f));
	MV1SetPosition(model, position);
}

/// <summary>
/// �X�V
/// </summary>
void Shield::Update(VECTOR characterPosition,float characterangle)
{
	VECTOR tentativepos = characterPosition;

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

void Shield::ReflectPosition(VECTOR newposition)
{
	MV1SetPosition(model, newposition);
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

void Shield::InitializeAngle(float charaangle)
{
	
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