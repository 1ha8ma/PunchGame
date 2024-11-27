#include<math.h>
#include"DxLib.h"
#include"Stage.h"
#include"InputManager.h"
#include"Loader.h"
#include"Player.h"

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

	attackinputpossible = false;

	InitializeAngle();
	OtherClassInitialize();

	MV1SetPosition(model, position);
}

/// <summary>
/// �X�V
/// </summary>
void Player::Update(int inputstate,bool outpauseinputflg)
{
	//���͏���
	InputProcess(inputstate, outpauseinputflg);
	
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
/// ���͂���Ă���̏���
/// </summary>
/// <param name="inputstate">���͏��</param>
/// <param name="wallhit">�ǂ����̕ǂɓ������Ă��邩</param>
void Player::InputProcess(const int inputstate,bool outpauseinputflg)
{
	//moveVec������
	moveVec = VGet(0, 0, 0);
	isanimflg = false;

	//�ړ�
	if (attackflg == false)
	{
		if (position.x <= Stage::StageRight && (InputManager::InputNumber::Right & inputstate) == InputManager::InputNumber::Right)//�E
		{
			moveVec = VAdd(moveVec, VGet(1.0f, 0.0f, 0.0f));
			isanimflg = true;
		}
		if (position.x >= Stage::StageLeft && (InputManager::InputNumber::Left & inputstate) == InputManager::InputNumber::Left)//��
		{
			moveVec = VAdd(moveVec, VGet(-1.0f, 0.0f, 0.0f));
			isanimflg = true;
		}
		if (position.z <= Stage::StageTop && (InputManager::InputNumber::Up & inputstate) == InputManager::InputNumber::Up)//��
		{
			moveVec = VAdd(moveVec, VGet(0.0f, 0.0f, 1.0f));
			isanimflg = true;
		}
		if (position.z >= Stage::StageBottom && (InputManager::InputNumber::Down & inputstate) == InputManager::InputNumber::Down)//��
		{
			moveVec = VAdd(moveVec, VGet(0.0f, 0.0f, -1.0f));
			isanimflg = true;
		}
	}

	//�U��
	if ((InputManager::InputNumber::BButton & inputstate) == InputManager::InputNumber::BButton)//B�{�^��
	{
		if (attackinputpossible && !outpauseinputflg)
		{
			Attack();
		}

		attackinputpossible = false;
	}
	else
	{
		attackinputpossible = true;
	}

	if (inputstate != 0 && attackflg == false)
	{
		//�ړ��x�N�g�����v���C���[�������ׂ������Ƃ��ĕۑ�
		targetLookDirection = moveVec;

		//���K�������x�N�g���ɃX�s�[�h�{�������̂��ړ��x�N�g���Ƃ���
		if (VSize(moveVec) > 0)
		{
			moveVec = VNorm(moveVec);
		}
		moveVec = VScale(targetLookDirection, Speed);
	}
}