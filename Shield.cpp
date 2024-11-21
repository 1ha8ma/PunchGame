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

	//�p�x�ݒ�
	angle = characterangle;

	//�|�W�V�����ݒ�
	position.x += sin(angle) * DistanceWithCharacter;
	position.z += cos(angle) * DistanceWithCharacter;

	capRight = VAdd(position, VGet(-sin(angle + AngleCorrection) * HalfWidthSize, DistanceWithCharacter, -cos(angle + AngleCorrection) * HalfWidthSize));
	capLeft = VAdd(position, VGet(sin(angle + AngleCorrection) * HalfWidthSize, DistanceWithCharacter, cos(angle + AngleCorrection) * HalfWidthSize));

	//�p�x�A�|�W�V�������f
	MV1SetRotationXYZ(model, VGet(0.0f, angle + AngleCorrection, 0.0f));
	MV1SetPosition(model, position);
}

/// <summary>
/// �X�V
/// </summary>
void Shield::Update(VECTOR characterPosition,float characterangle)
{
	VECTOR tentativepos = characterPosition;

	//���f���p�x�X�V
	UpdateAngle(characterangle);

	//�����ɒǏ]
	tentativepos.x += sin(angle) * DistanceWithCharacter;
	tentativepos.z += cos(angle) * DistanceWithCharacter;

	//�J�v�Z���p�x�X�V
	capRight = VAdd(position, VGet(-sin(angle  + AngleCorrection) * HalfWidthSize, DisttanceWithGround, -cos(angle + AngleCorrection) * HalfWidthSize));
	capLeft = VAdd(position, VGet(sin(angle + AngleCorrection) * HalfWidthSize, DisttanceWithGround, cos(angle + AngleCorrection) * HalfWidthSize));

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
	//DrawCapsule3D(capLeft, capRight, ShieldCapsuleRadius, 20, GetColor(127, 255, 0), GetColor(0, 255, 255), FALSE);
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

	MV1SetRotationXYZ(model, VGet(0.0f, angle + AngleCorrection, 0.0f));
}