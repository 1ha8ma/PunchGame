#include<math.h>
#include<stdlib.h>
#include<time.h>
#include"DxLib.h"
#include"Enemy.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="modelhandle">���f���n���h���ԍ�</param>
/// <param name="modelsize">���f���T�C�Y</param>
/// <param name="position">�|�W�V����</param>
/// <param name="targetDirection">��������</param>
Enemy::Enemy(const TCHAR *modelhandle,float modelsize,VECTOR position,VECTOR targetDirection,int cpunumber)
{
	model = MV1LoadModel(modelhandle);
	mynumber = cpunumber;

	MV1SetScale(model, VGet(modelsize, modelsize, modelsize));

	Initialize(position, targetDirection);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Enemy::~Enemy()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="position">�|�W�V����</param>
/// <param name="targetDirection">��������</param>
void Enemy::Initialize(VECTOR position, VECTOR targetDirection)
{
	OtherClassInitialize();

	srand((unsigned int)time(NULL));

	//�A�j���[�V����������
	animplaytime = 0.0f;
	nowPlayAnimKind = static_cast<int>(AnimKind::Run);
	nowPlayAnim = MV1AttachAnim(model, static_cast<int>(AnimKind::Run));
	animtotaltime = MV1GetAttachAnimTotalTime(model, nowPlayAnim);
	prevPlayAnim = -1;

	//�|�W�V�����A�����֌W������
	isanimflg = false;
	attackflg = false;
	angle = 0.0f;
	this->position = position;
	this->targetLookDirection = targetDirection;

	//����t���O������
	in = false;
	shieldhit = false;
	outflg = false;
	attackaftercharachange = false;

	//�U���N�[���^�C��
	cooltimeflg = false;
	cooltimeflame = 0;

	//�ǂ������֌W������
	targetCharaAngle = 0.0f;
	chaseflame = 0;
	moveangle = 0;

	//�^�[�Q�b�g�ݒ�
	while (1)
	{
		target = rand() % 4;
		if (target != mynumber)
		{
			break;
		}
	}

	MV1SetPosition(model, this->position);
}

/// <summary>
/// �^�[�Q�b�g�ݒ�
/// </summary>
void Enemy::SetTarget(std::vector<int> outchara)
{
	//�����_���Œǂ��L���������߂�
	while (1)
	{
		bool ok = true;//�L��������t���O
		bool charachange = false;//�ǂ��Ώۂ��E�������ꍇ
		for (int i = 0; i < outchara.size(); i++)
		{
			if (target == outchara[i] || target == mynumber || attackaftercharachange)
			{
				charachange = true;
			}
		}

		//�E����������莞�Ԍo���Ă���΃^�[�Q�b�g�ύX
		if (chaseflame >= 500 || charachange)
		{
			target = rand() % 4;
			chaseflame = 0;

			//�����E�����Ă����������x���߂�
			for (int i = 0; i < outchara.size(); i++)
			{
				if (target == outchara[i] || target == mynumber)
				{
					ok = false;
				}
			}
		}

		//���܂�����
		if (ok)
		{
			break;
		}
	}
}

/// <summary>
/// �ړ�����
/// </summary>
void Enemy::Move(std::vector<int> outchara)
{
	//�^�[�Q�b�g�ݒ�
	SetTarget(outchara);

	//�p�x�ݒ�
	moveangle = atan2(targetPosition.z - position.z, targetPosition.x - position.x);

	//�^�[�Q�b�g�Ƃ̋��������
	float calc = pow(targetPosition.x - position.x, 2) + pow(targetPosition.y - position.y, 2) + pow(targetPosition.z - position.z, 2);
	targetdistance = sqrt(calc);

	//���x�ݒ�
	vx = cos(moveangle) * Speed;
	vz = sin(moveangle) * Speed;

	//�p�x�ݒ�
	if (attackflg == false)
	{
		targetLookDirection.x = targetPosition.x;
		targetLookDirection.z = targetPosition.z;
	}

	//�ڕW�Ƃ̊p�x�̍������
	float targetAngle = static_cast<float>(atan2(targetLookDirection.x, targetLookDirection.z));
	float angledif = abs(targetAngle - angle);

	if (angledif > 10)
	{
		int a = 0;
	}

	//�˒��ɓ���A�������ȉ��Ńt���O���ǂ���΍U��
	if (targetdistance < 1000 && angledif ==0 && attackflg == false && cooltimeflg == false)
	{
		cooltimeflg = true;
		cooltimeflame = 0;
		Attack();
	}

	//�i�܂���
	if (targetdistance > 1000 && attackflg == false)
	{
		isanimflg = true;
		position.x += vx;
		position.z += vz;
	}
	else
	{
		isanimflg = false;
	}
}

/// <summary>
/// �X�V
/// </summary>
void Enemy::Update(std::vector<int> outchara)
{
	//����
	Move(outchara);

	//�A�j���[�V�����Đ�
	PlayAnimation();

	//�p�x�X�V
	UpdateAngle();

	//�J�v�Z���X�V
	UpdateCapsule();

	//�|�W�V�������f
	MV1SetPosition(model, position);

	//�t���[�����Z
	if (cooltimeflg)
	{
		cooltimeflame++;
		if (cooltimeflame == 100)
		{
			cooltimeflg = false;
			attackaftercharachange = true;
		}
		else
		{
			attackaftercharachange = false;
		}
	}
	else
	{
		attackaftercharachange = false;
	}
	chaseflame++;
}