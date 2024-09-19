#include<math.h>
#include"DxLib.h"
#include"Utility.h"
#include"Player.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player()
{
	//���f�����[�h�E�A�j���[�V�����ݒ�
	model = MV1LoadModel("3D/player.mv1");
	nowPlayAnim = MV1AttachAnim(model, static_cast<int>(AnimKind::Run));
	animtotaltime = MV1GetAttachAnimTotalTime(model, nowPlayAnim);

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
	targetDirection = VGet(1.0f, 0.0f, 1.0f);
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
	//���͏���
	InputProcess(inputstate);
	
	//�A�j���[�V����
	PlayAnimation();
	
	//�����ݒ�
	UpdateAngle();

	//���f���|�W�V�����X�V
	MV1SetPosition(model, position);
}

/// <summary>
/// ���͂���Ă���̏���
/// </summary>
/// <param name="inputstate">���͏��</param>
/// <param name="wallhit">�ǂ����̕ǂɓ������Ă��邩</param>
void Player::InputProcess(const int inputstate)
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
		targetDirection = moveVec;

		//���K�������x�N�g���ɃX�s�[�h�{�������̂��ړ��x�N�g���Ƃ���
		moveVec = VScale(targetDirection, Speed);
	}

	//�|�W�V�����ɓK�p
	position = VAdd(position, moveVec);
}