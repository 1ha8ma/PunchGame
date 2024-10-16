#include<math.h>
#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Utility.h"
#include"Shield.h"
#include"Fist.h"
#include"Loader.h"
#include"CharacterBase.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CharacterBase::CharacterBase()
{
	//���N���X�C���X�^���X��
	shield = new Shield();
	fist = new Fist();
	Loader* loader = loader->GetInstance();

	//�G�t�F�N�g���[�h
	playerhiteffecthandle = loader->GetHandle(Loader::Kind::PlayerhitEffect);
	shieldhiteffecthandle = loader->GetHandle(Loader::Kind::ShieldhitEffect);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CharacterBase::~CharacterBase()
{
	//�G�t�F�N�g�I��
	StopEffekseer3DEffect(PlayingEffecthandle);

	delete shield;
	delete fist;
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

	//���֌W
	shieldhit = false;

	//�G�t�F�N�g�֌W
	PlayingEffectKind = static_cast<int>(EffectKind::None);
	PlayingEffecthandle = -1;
	Playplayerhiteffectflg = false;
	Playshieldhiteffectflg = false;
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
	shieldhiteffectangle = VGet(0.0f, angle + DX_PI_F, 0.0f);
	playerhiteffectangle = VGet(0.0f, angle + DX_PI_F, 0.0f);
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
///�@���N���X������
/// </summary>
void CharacterBase::OtherClassInitialize()
{
	if (outflg == false)
	{
		fist->Initialize();
	}
	shield->Initialize(position, angle);
}

/// <summary>
/// �G�t�F�N�g�X�V
/// </summary>
void CharacterBase::UpdateEffect(bool shieldhit)
{
	//�G�t�F�N�g�J��������
	Effekseer_Sync3DSetting();
	//�G�t�F�N�g���x�ݒ�
	SetSpeedPlayingEffekseer3DEffect(PlayingEffecthandle, 0.1f);
	//�G�t�F�N�g�X�V
	UpdateEffekseer3D();

	if (Playshieldhiteffectflg && shieldhit == false)
	{
		Playshieldhiteffectflg = false;
	}
}

/// <summary>
/// ���N���X�̍X�V
/// </summary>
void CharacterBase::OtherClassUpdate(bool shieldhit)
{
	fist->Update(position, angle, attackflg,shieldhit);
	shield->Update(position, angle);
}

/// <summary>
/// ���ƃL�����N�^�[�̓����蔻��
/// </summary>
/// <param name="charatop">�L������</param>
/// <param name="charabottom">�L������</param>
/// <param name="charaR">�L�������a</param>
bool CharacterBase::FistWithCharacter(VECTOR charatop, VECTOR charabottom, float charaR,bool charaout)
{
	float len;
	bool hit = false;//�U������������

	//2�̐����̍ŒZ���������߂�
	len = Segment_Segment_MinLength(fist->GetcapFront(), fist->GetcapBack(), charatop, charabottom);

  	if (len < Fist::FistCapsuleRadius + charaR)
	{
		hit = true;
	}
	else
	{
		hit = false;
	}

	return hit;
}

/// <summary>
/// ���Ə��̓����蔻��
/// </summary>
/// <param name="ShieldLeft">����</param>
/// <param name="ShieldRight">���E</param>
/// <param name="shieldR">�����a</param>
/// <returns>�������Ă��邩</returns>
bool CharacterBase::FistWithShield(VECTOR ShieldLeft, VECTOR ShieldRight, float shieldR)
{
	float len;
	bool hit = false;//���ɓ�������

	//2�̐����̍ŒZ���������߂�
	len = Segment_Segment_MinLength(fist->GetcapFront(), fist->GetcapBack(), ShieldLeft, ShieldRight);

	if (len < Fist::FistCapsuleRadius + shieldR && attackflg)
	{
		hit = true;

		if (Playshieldhiteffectflg == false)
		{
			//�|�W�V�����ݒ�
			shieldhiteffectposition = fist->GetcapFront();

			//�Đ�����
			PlayingEffectKind = static_cast<int>(EffectKind::HitShield);
			PlayingEffecthandle = PlayEffekseer3DEffect(shieldhiteffecthandle);
			SetPosPlayingEffekseer3DEffect(PlayingEffecthandle, shieldhiteffectposition.x, shieldhiteffectposition.y, shieldhiteffectposition.z);
			SetRotationPlayingEffekseer3DEffect(PlayingEffecthandle, shieldhiteffectangle.x, shieldhiteffectangle.y, shieldhiteffectangle.z);
			Playshieldhiteffectflg = true;
		}
	}
	else
	{
		hit = false;
	}

	return hit;
}

/// <summary>
/// �E���ɂȂ�����
/// </summary>
/// <param name="hit">����������</param>
void CharacterBase::CheckOut(bool hit)
{
	//�E����
	if (outflg == false && hit)
	{
		//�G�t�F�N�g�Đ�
		//�|�W�V�����ݒ�
		playerhiteffectposition = position;

		//�Đ�����
		PlayingEffectKind = static_cast<int>(EffectKind::HitPlayer);
		PlayingEffecthandle = PlayEffekseer3DEffect(playerhiteffecthandle);
		SetPosPlayingEffekseer3DEffect(PlayingEffecthandle, playerhiteffectposition.x, playerhiteffectposition.y, playerhiteffectposition.z);
		SetRotationPlayingEffekseer3DEffect(PlayingEffecthandle, playerhiteffectangle.x, playerhiteffectangle.y, playerhiteffectangle.z);
		Playplayerhiteffectflg = true;

		//�t���O�ύX
 		outflg = true;
	}
}

/// <summary>
/// �L�����̐�����ѓ���
/// </summary>
void CharacterBase::Blow()
{
	if (outflg && position.y < 2000)
	{
		position = VAdd(position, VGet(0, 100, 0));
		//�|�W�V�������f
		MV1SetPosition(model, position);
	}
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

VECTOR CharacterBase::GetShieldLeft()
{
	return shield->GetcapLeft();
}

VECTOR CharacterBase::GetShieldRight()
{
	return shield->GetcapRight();
}

/// <summary>
/// �`��
/// </summary>
void CharacterBase::Draw()
{
	//DrawCapsule3D(capsuleTop, capsuleBottom, CharacterR, 8, GetColor(127, 255, 0), GetColor(0, 255, 255), FALSE);
	MV1DrawModel(model);
	shield->Draw();
	if (outflg == false)
	{
		fist->Draw();
	}
	DrawEffekseer3D();
}