#include<math.h>
#include"DxLib.h"
#include"Utility.h"
#include"CharacterBase.h"

/// <summary>
/// �p�x�X�V
/// </summary>
void CharacterBase::UpdateAngle()
{
	//�ړ������Ƀ��f���̕������߂Â���
	float targetAngle;//�ڕW�̊p�x
	float difference;//�ڕW�p�x�ƌ��݂̊p�x�̍�

	//�ڕW�̕����x�N�g������p�x�l���Z�o����
	targetAngle = static_cast<float>(atan2(targetLookDirection.x, targetLookDirection.z));

	//�ڕW�̊p�x�ƌ��݂̊p�x�Ƃ̍�������o��
	//�ŏ��͈����Z
	difference = targetAngle - angle;

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
	angle = targetAngle - difference;

	MV1SetRotationXYZ(model, VGet(0.0f, angle + DX_PI_F, 0.0f));
}

/// <summary>
/// �A�j���[�V�����؂�ւ�
/// </summary>
/// <param name="nextkind">���̃A�j���[�V����</param>
void CharacterBase::ChangeAnimation(AnimKind nextkind)
{
	//����ւ����ɑO�̃��[�V�������L����������f�^�b�`����
	if (nowPlayAnim != -1)
	{
		MV1DetachAnim(model, nowPlayAnim);
		nowPlayAnim = -1;
	}

	//�V�����A�j���[�V�������A�^�b�`
	nowPlayAnimKind = static_cast<int>(nextkind);
	nowPlayAnim = MV1AttachAnim(model, static_cast<int>(nextkind));
	animtotaltime = MV1GetAttachAnimTotalTime(model, nowPlayAnim);
	animplaytime = 0.0f;
}

/// <summary>
/// �A�j���[�V�����Đ�
/// </summary>
void CharacterBase::PlayAnimation()
{
	//�U�����̏ꍇ
	if (attackflg)
	{
		isanimflg = true;
	}

	//�A�j���[�V�����Đ�
	if (isanimflg)
	{
		animplaytime += 0.5f;
	}

	//�A�j���[�V���������Đ����ԂɒB������
	if (animplaytime >= animtotaltime)
	{
		if (nowPlayAnimKind == static_cast<int>(AnimKind::Punch))//�U�����[�V�������I������ꍇ
		{
			attackflg = false;
			ChangeAnimation(AnimKind::Run);
		}
		if (nowPlayAnimKind == static_cast<int>(AnimKind::Run))//���郂�[�V�������I������ꍇ
		{
			animplaytime = 0.0f;
		}
	}

	//�Đ����Ԃ��Z�b�g
	MV1SetAttachAnimTime(model, nowPlayAnim, animplaytime);
}

/// <summary>
/// �U������
/// </summary>
void CharacterBase::Attack()
{
	//�U�����[�V�����ɕύX
	if (attackflg == false)
	{
		ChangeAnimation(AnimKind::Punch);
		attackflg = true;
	}
}

/// <summary>
/// �`��
/// </summary>
void CharacterBase::Draw()
{
	MV1DrawModel(model);
}