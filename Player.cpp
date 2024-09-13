#include<math.h>
#include"DxLib.h"
#include"Player.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player()
{
	//���f�����[�h�E�A�j���[�V�����ݒ�
	model = MV1LoadModel("3D/player.mv1");
	runanim = MV1AttachAnim(model, static_cast<int>(AnimKind::Run));
	animtotaltime = MV1GetAttachAnimTotalTime(model, runanim);

	//����������
	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{

}

/// <summary>
/// ������
/// </summary>
void Player::Initialize()
{
	//�A�j���[�V����������
	animplaytime = 0.0f;
	nowPlayAnimKind = static_cast<int>(AnimKind::Run);
	nowPlayAnim = static_cast<int>(AnimKind::Run);
	prevPlayAnim = -1;

	isanimflg = false;
	angle = 0.0f;
	moveVec = VGet(0, 0, 0);
	targetMoveDirection = VGet(1.0f, 0.0f, 1.0f);
	attackflg = false;

	//�|�W�V����������
	position = VGet(-1000.0f, 100.0f, -700.0f);
	MV1SetPosition(model, position);
}

/// <summary>
/// �X�V
/// </summary>
void Player::Update(int inputstate)
{
	//�ړ�
	InputMoveProcess(inputstate);

	//�U��
	
	//�A�j���[�V����
	PlayAnimation();
	
	//�����ݒ�
	UpdateAngle();

	//���f���|�W�V�����X�V
	MV1SetPosition(model, position);
}

/// <summary>
/// �`��
/// </summary>
void Player::Draw()
{
	MV1DrawModel(model);
}


/// <summary>
/// �ړ�����
/// </summary>
/// <param name="inputstate">���͏��</param>
/// <param name="wallhit">�ǂ����̕ǂɓ������Ă��邩</param>
void Player::InputMoveProcess(const int inputstate)
{
	//moveVec������
	moveVec = VGet(0, 0, 0);

	//�ړ�
	if (attackflg == false)
	{
		if ((4 & inputstate) == 4)//�E
		{
			moveVec = VAdd(moveVec, VGet(1.0f, 0.0f, 0.0f));
		}
		if ((2 & inputstate) == 2)//��
		{
			moveVec = VAdd(moveVec, VGet(-1.0f, 0.0f, 0.0f));
		}
		if ((8 & inputstate) == 8)//��
		{
			moveVec = VAdd(moveVec, VGet(0.0f, 0.0f, 1.0f));
		}
		if ((1 & inputstate) == 1)//��
		{
			moveVec = VAdd(moveVec, VGet(0.0f, 0.0f, -1.0f));
		}
	}


	//�A�j���[�V�����t���O�ύX
	if (inputstate != 0)
	{
		isanimflg = true;
	}
	else
	{
		isanimflg = false;
	}

	//�U��
	if ((16 & inputstate) == 16)//B�{�^��
	{
		Attack();
	}

	if (inputstate != 0 && attackflg == false)
	{
		//�ړ��x�N�g���𐳋K���������̂��v���C���[�������ׂ������Ƃ��ĕۑ�
		//targetMoveDirection = VNorm(moveVec);
		targetMoveDirection = moveVec;

		//���K�������x�N�g���ɃX�s�[�h�{�������̂��ړ��x�N�g���Ƃ���
		moveVec = VScale(targetMoveDirection, Speed);
	}

	//�|�W�V�����ɓK�p
	position = VAdd(position, moveVec);
}

/// <summary>
/// ������ݒ�
/// </summary>
void Player::UpdateAngle()
{
	//�v���C���[�̈ړ������Ƀ��f���̕������߂Â���
	float targetAngle;//�ڕW�̊p�x
	float difference;//�ڕW�p�x�ƌ��݂̊p�x�̍�

	//�ڕW�̕����x�N�g������p�x�l���Z�o����
	targetAngle = static_cast<float>(atan2(targetMoveDirection.x, targetMoveDirection.z));

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
void Player::ChangeAnimation(AnimKind nextkind)
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
void Player::PlayAnimation()
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

	//�A�j���[�V�������g�[�^�����ԂɒB������
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
void Player::Attack()
{
	//�U�����[�V�����ɕύX
	if (attackflg == false)
	{
		ChangeAnimation(AnimKind::Punch);
		attackflg = true;
	}

}