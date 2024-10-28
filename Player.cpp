#include<math.h>
#include"DxLib.h"
#include"Utility.h"
#include"Player.h"
#include"Loader.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player()
{
	//���f�����[�h�E�A�j���[�V�����ݒ�
	Loader* loader = Loader::GetInstance();
	model = loader->GetHandle(Loader::Kind::PlayerModel);

	//����������
	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{
	MV1DetachAnim(model, nowPlayAnim);
}

/// <summary>
/// ������
/// </summary>
void Player::Initialize()
{
	BaseInitialize();

	//�|�W�V����������
	position = VGet(-1000.0f, 100.0f, -700.0f);
	capsuleTop = VAdd(position, VGet(0, 600, 0));
	capsuleBottom = VAdd(position, VGet(0, 0, 0));

	//�ړ��p�x�ݒ�
	moveVec = VGet(0, 0, 0);
	targetLookDirection = VGet(1.0f, 0.0f, 1.0f);

	InitializeAngle();
	OtherClassInitialize();

	MV1SetPosition(model, position);
}

/// <summary>
/// �X�V
/// </summary>
void Player::Update(int inputstate)
{
	//���͏���
	InputProcess(inputstate);
	
	//�����蔻���t���邩���f
	CheckAttackOnCollision();

	//�A�j���[�V����
	PlayAnimation();
	
	//�����ݒ�
	UpdateAngle();


	//���f���|�W�V�����X�V
	MV1SetPosition(model, position);
}

/// <summary>
/// �I���A�E����������X�V
/// </summary>
void Player::ForeverUpdate()
{
	//���N���X�̏���
	OtherClassUpdate();

	//�J�v�Z���X�V
	UpdateCapsule();

	//�G�t�F�N�g�X�V
	UpdateEffect();

	//�������
	Blow();
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
		if (position.x <= StageRight && (4 & inputstate) == 4)//�E
		{
			moveVec = VAdd(moveVec, VGet(1.0f, 0.0f, 0.0f));
		}
		if (position.x >= StageLeft && (2 & inputstate) == 2)//��
		{
			moveVec = VAdd(moveVec, VGet(-1.0f, 0.0f, 0.0f));
		}
		if (position.z <= StageTop && (8 & inputstate) == 8)//��
		{
			moveVec = VAdd(moveVec, VGet(0.0f, 0.0f, 1.0f));
		}
		if (position.z >= StageBottom && (1 & inputstate) == 1)//��
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
		targetLookDirection = moveVec;

		//���K�������x�N�g���ɃX�s�[�h�{�������̂��ړ��x�N�g���Ƃ���
		moveVec = VNorm(moveVec);
		moveVec = VScale(targetLookDirection, Speed);
	}

	//�|�W�V�����ɓK�p
	position = VAdd(position, moveVec);
}