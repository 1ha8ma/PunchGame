#include<math.h>
#include"DxLib.h"
#include"Utility.h"
#include"Shield.h"
#include"Fist.h"
#include"Effect.h"
#include"SEManager.h"
#include"Collision.h"
#include"CharacterBase.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CharacterBase::CharacterBase()
{
	//���N���X�C���X�^���X��
	shield = new Shield();
	fist = new Fist();
	semanager = new SEManager();
	effect = new Effect();
	collision = new Collision();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CharacterBase::~CharacterBase()
{
	//�A�j���[�V�������f�^�b�`
	MV1DetachAnim(model, nowPlayAnim);
	
	delete shield;
	delete fist;
	delete semanager;
	delete effect;
}

/// <summary>
/// �x�[�X������
/// </summary>
void CharacterBase::BaseInitialize()
{
	//�A�j���[�V�����֌W
	isanimflg = false;
	animplaytime = 0.0f;
	nowPlayAnimKind = static_cast<int>(AnimKind::Run);
	nowPlayAnim = MV1AttachAnim(model, static_cast<int>(AnimKind::Run));
	animtotaltime = MV1GetAttachAnimTotalTime(model, nowPlayAnim);
	prevPlayAnim = -1;

	//���f���֌W
	angle = 0.0f;
	outflg = false;

	//�U���֌W
	attackflg = false;
	attackOnCollision = false;

	//���֌W
	shieldhit = false;

	//�G�t�F�N�g�֌W
	Playplayerhiteffectflg = false;
	Playshieldhiteffectflg = false;

	shieldhitseflg = false;
}

/// <summary>
/// �p�x������
/// </summary>
void CharacterBase::InitializeAngle()
{
	float targetAngle;
	float difference;

	//�ڕW�̕����x�N�g��
	targetAngle = static_cast<float>(atan2(targetLookDirection.x, targetLookDirection.z));

	angle = targetAngle;

	MV1SetRotationXYZ(model, VGet(0.0f, angle + DX_PI_F, 0.0f));
}

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
		if (nowPlayAnimKind == static_cast<int>(AnimKind::Run))
		{
			animplaytime += 0.5f;
		}
		if (nowPlayAnimKind == static_cast<int>(AnimKind::Punch))
		{
			animplaytime += 0.7f;
		}
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
	if (!attackflg)
	{
		ChangeAnimation(AnimKind::Punch);
		attackflg = true;
	}
}

/// <summary>
///�@���N���X������
/// </summary>
void CharacterBase::OtherClassInitialize()
{
	if (!outflg)
	{
		fist->Initialize();
	}
	shield->Initialize(position, angle);
}

/// <summary>
/// �G�t�F�N�g�X�V
/// </summary>
void CharacterBase::UpdateEffect()
{
	effect->Update();

	//�G�t�F�N�g�t���O��߂�
	if (Playshieldhiteffectflg && !shieldhit)
	{
		Playshieldhiteffectflg = false;
	}
}

/// <summary>
/// ���N���X�̍X�V
/// </summary>
void CharacterBase::OtherClassUpdate()
{
	fist->Update(position, angle, attackflg,shieldhit);
	shield->Update(position, angle);
}

/// <summary>
/// �U���ɓ����蔻���t���邩���f
/// </summary>
void CharacterBase::CheckAttackOnCollision()
{
	if (attackflg && fist->GetSize() == 1.0f)
	{
		attackOnCollision = true;
	}
	else
	{
		attackOnCollision = false;
	}
}

/// <summary>
/// ���ƃL�����N�^�[�̓����蔻��
/// </summary>
/// <param name="charatop">����ΏۃL������</param>
/// <param name="charabottom">����ΏۃL������</param>
/// <param name="charaR">�L�������a</param>
bool CharacterBase::FistWithCharacter(VECTOR charatop, VECTOR charabottom, bool charaout)
{
	bool hit = false;//�U������������

	if (collision->CapsuleWithCapsule(fist->GetcapFront(), fist->GetcapBack(), charatop, charabottom, fist->FistCapsuleRadius, CharacterCapsuleRadius) && attackOnCollision)
	{
		hit = true;
	}

	return hit;
}

/// <summary>
/// ���Ə��̓����蔻��
/// </summary>
/// <param name="ShieldLeft">����ΏۃL�����̏���</param>
/// <param name="ShieldRight">����ΏۃL�����̏��E</param>
/// <param name="shieldR">�����a</param>
/// <returns>�������Ă��邩</returns>
bool CharacterBase::FistWithShield(VECTOR ShieldLeft, VECTOR ShieldRight)
{
	bool hit = false;//���ɓ�������

	//�����蔻��
	if (collision->CapsuleWithCapsule(fist->GetcapFront(), fist->GetcapBack(), ShieldLeft, ShieldRight, fist->FistCapsuleRadius, shield->ShieldCapsuleRadius) && attackOnCollision)
	{
		hit = true;

		//�G�t�F�N�g�Đ�
		if (!Playshieldhiteffectflg)
		{
			effect->PlayEffect(Effect::EffectKind::ShieldHit, fist->GetcapFront(), VGet(1.0f, 1.0f, 1.0f), angle, 0.7f);
			Playshieldhiteffectflg = true;
		}
	}

	return hit;
}

/// <summary>
/// ���ǂ����̓����蔻��
/// </summary>
/// <param name="shieldleft">�ΏۃL�����̏�</param>
/// <param name="shieldright">�ΏۃL�����̏�</param>
/// <param name="shieldR">�����a</param>
/// <returns>�������Ă��邩</returns>
bool CharacterBase::ShieldWithShield(VECTOR myshieldleft,VECTOR myshieldright,VECTOR shieldleft, VECTOR shieldright)
{
	bool hit = false;//���ɓ�������

	//�����蔻��
	if (collision->CapsuleWithCapsule(myshieldleft, myshieldright, shieldleft, shieldright, shield->ShieldCapsuleRadius, shield->ShieldCapsuleRadius))
	{
		hit = true;
	}

	return hit;
}

/// <summary>
/// ���Ə��̓�����Ȃ��ʒu�܂�movevec��߂�/
/// </summary>
/// <param name="shieldleft">�ΏۃL�����̏�</param>
/// <param name="shieldright">�ΏۃL�����̏�</param>
void CharacterBase::RemoveShield(VECTOR shieldleft, VECTOR shieldright)
{
	//�����|�W�V����
	VECTOR tentativeshieldposition = shield->GetPosition();
	VECTOR tentativeshieldleft;
	VECTOR tentativeshieldright;

	//������Ȃ��Ȃ�܂�moveVec�𒲐����ĊO��
	while (1)
	{
		moveVec = VSub(moveVec, VGet(1.0f, 0.0f, 1.0f));
		tentativeshieldposition = VAdd(tentativeshieldposition, moveVec);
		tentativeshieldleft = VAdd(tentativeshieldposition, VGet(-sin(angle - 1.5f) * 150, 200, -cos(angle - 1.5f) * 150));
		tentativeshieldright = VAdd(tentativeshieldposition, VGet(sin(angle - 1.5f) * 150, 200, cos(angle - 1.5f) * 150));

		//�O�ꂽ��I��
		if (!ShieldWithShield(tentativeshieldleft, tentativeshieldright, shieldleft, shieldright) || (moveVec.x <= 0.0f && moveVec.z <= 0.0f))
		{
			break;
		}
	}
}

/// <summary>
/// �E���ɂȂ�����
/// </summary>
/// <param name="hit">����������</param>
void CharacterBase::CheckOut(bool hit)
{
	//�E����
	if (!outflg && hit)
	{
		//�G�t�F�N�g�Đ�
		effect->PlayEffect(Effect::EffectKind::CharacterHit, position, VGet(3.0f, 3.0f, 3.0f), angle, 0.7f);
		Playplayerhiteffectflg = true;

		//se�Đ�
		semanager->PlaySE(SEManager::SEKind::CharahitSE);

		//�t���O�ύX
 		outflg = true;
	}
}

/// <summary>
/// �L�����̐�����ѓ���
/// </summary>
void CharacterBase::Blow()
{
	if (outflg && position.y < 3000)
	{
		position = VAdd(position, VGet(0, 100, 0));
		//�|�W�V�������f
		MV1SetPosition(model, position);
	}
}

/// <summary>
/// ���Փ�SE�Đ�
/// </summary>
/// <param name="hit">�Փ˂�����</param>
void CharacterBase::PlayShieldHitSE(bool hit)
{
	if (hit && !shieldhitseflg)
	{
		semanager->PlaySE(SEManager::SEKind::ShieldhitSE);
		shieldhitseflg = true;
	}
	if (!hit && shieldhitseflg)
	{
		shieldhitseflg = false;
	}
}

/// <summary>
/// �|�W�V�������f
/// </summary>
void CharacterBase::ReflectPosition()
{
	//�|�W�V������moveVec�����Z
	position = VAdd(position, moveVec);
	//�J�v�Z���X�V
	UpdateCapsule();
	//���N���X�X�V
	OtherClassUpdate();
}

/// <summary>
/// �J�v�Z���X�V
/// </summary>
void CharacterBase::UpdateCapsule()
{
	//�����蔻��J�v�Z��
	capsuleTop = VAdd(position, VGet(0, 600, 0));
	capsuleBottom = VAdd(position, VGet(0, 0, 0));
}

VECTOR CharacterBase::GetShieldPosition()
{
	return shield->GetPosition();
}

VECTOR CharacterBase::GetShieldLeft()
{
	return shield->GetcapLeft();
}

VECTOR CharacterBase::GetShieldRight()
{
	return shield->GetcapRight();
}

void CharacterBase::SetShieldHit(bool hit)
{
	shieldhit = hit;
}

/// <summary>
/// �`��
/// </summary>
void CharacterBase::Draw()
{
	//DrawCapsule3D(capsuleTop, capsuleBottom, CharacterCapsuleRadius, 8, GetColor(127, 255, 0), GetColor(0, 255, 255), FALSE);
	MV1DrawModel(model);
	if (!outflg)
	{
		fist->Draw();
	}
	shield->Draw();
	effect->Draw();
}