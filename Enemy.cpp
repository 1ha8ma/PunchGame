#include<math.h>
#include<stdlib.h>
#include<time.h>
#include"DxLib.h"
#include"Utility.h"
#include"Enemy.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="handle">���f���n���h��</param>
/// <param name="modelsize">���f���T�C�Y</param>
/// <param name="position">�|�W�V����</param>
/// <param name="targetDirection">��������</param>
Enemy::Enemy(int handle,float modelsize,VECTOR position,VECTOR targetDirection,int cpunumber)
{
	model = handle;
	mynumber = cpunumber;

	MV1SetScale(model, VGet(modelsize, modelsize, modelsize));

	Initialize(position, targetDirection);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Enemy::~Enemy()
{
	MV1DetachAnim(model, nowPlayAnim);
}

/// <summary>
/// ������
/// </summary>
/// <param name="position">�|�W�V����</param>
/// <param name="targetDirection">��������</param>
void Enemy::Initialize(VECTOR position, VECTOR targetDirection)
{
	BaseInitialize();

	//����������
	srand((unsigned int)time(NULL));

	//�|�W�V����������
	this->position = position;
	capsuleTop = VAdd(this->position, VGet(0, 600, 0));
	capsuleBottom = VAdd(this->position, VGet(0, 0, 0));
	this->targetLookDirection = targetDirection;

	//�U���N�[���^�C��
	cooltimeflg = false;
	cooltimeflame = 0;

	//�ړ��֌W
	NowMoveKind = MoveKind::charachase;
	moveflame = 0;
	moveangle = 0;
	moveonflg = true;

	//�����_�������֌W
	SetWalkTargetPositionflg = false;

	//�ǂ������֌W������
	//�^�[�Q�b�g�ݒ�
	while (1)
	{
		target = rand() % OllCharaNum;
		if (target != mynumber)
		{
			break;
		}
	}

	InitializeAngle();
	OtherClassInitialize();
	MV1SetPosition(model, this->position);
}

/// <summary>
/// �^�[�Q�b�g�ݒ�
/// </summary>
void Enemy::SetTargetChara(std::vector<int> outchara)
{
	//�����_���Œǂ��L���������߂�
	while (1)
	{
		bool ok = true;//�L��������t���O
		bool charachange = false;//�L�������t���O

		for (int i = 0; i < outchara.size(); i++)
		{
			if (target == outchara[i] || target == mynumber)
			{
				charachange = true;
			}
		}

		//�E����������莞�Ԍo���Ă���΃^�[�Q�b�g�ύX
		if (charachange)
		{
			target = rand() % OllCharaNum;

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
	switch (NowMoveKind)
	{
	case(MoveKind::charachase):
	{
		//�^�[�Q�b�g�ݒ�
		SetTargetChara(outchara);

		//�^�[�Q�b�g�Ƃ̋��������
		float calc = pow(targetPosition.x - position.x, 2) + pow(targetPosition.z - position.z, 2);
		targetdistance = sqrt(calc);

		//�p�x�ݒ�
		if (attackflg == false)
		{
			targetLookDirection.x = targetPosition.x;
			targetLookDirection.z = targetPosition.z;
		}

		//�˒��ɓ���A�������ȉ��Ńt���O���ǂ���΍U��
		if (targetdistance < 1000 && attackflg == false && cooltimeflg == false)
		{
			cooltimeflg = true;
			cooltimeflame = 0;
			Attack();
		}
		//�˒��͈͊O�ł���ΐi�߂�
		if (targetdistance > 1000)
		{
			moveonflg = true;
		}
		else
		{
			moveonflg = false;
		}

		//�t���[�����Z
		if (cooltimeflg)
		{
			cooltimeflame++;
			if (cooltimeflame == 100)
			{
				cooltimeflg = false;
			}
		}

		//��莞�ԂŒǂ����̍Ē��I
		if (moveflame >= 150)
		{
			int random = rand() % 3;
			if (random == MoveKind::charachase)
			{
				NowMoveKind = MoveKind::charachase;
			}
			else
			{
				NowMoveKind = MoveKind::randomwalk;
			}

			moveflame = 0;
		}
	}
	break;
	case(MoveKind::randomwalk):
	{
		//�ړI�n�ݒ�
		if (SetWalkTargetPositionflg == false)
		{
			targetPosition.x = (rand() % static_cast<int>((StageRight - StageLeft))) + StageLeft;
			targetPosition.z = (rand() % static_cast<int>((StageTop - StageBottom)))+ StageBottom;

			targetLookDirection.x = targetPosition.x;
			targetLookDirection.z = targetPosition.z;

			SetWalkTargetPositionflg = true;
		}

		//�^�[�Q�b�g�Ƃ̋��������
		float calc = pow(targetPosition.x - position.x, 2) + pow(targetPosition.z - position.z, 2);
		targetdistance = sqrt(calc);

		//���ߋ����ɂȂ�����ړI�n�Ƀ|�W�V�������ڂ�
		if (targetdistance <= Speed)
		{
			position.x = targetPosition.x;
			position.z = targetPosition.z;
			moveonflg = false;
		}
		else
		{
			moveonflg = true;
		}

		//��莞�ԂŒǂ����̍Ē��I
		if (moveflame >= 70)
		{
			int random = rand() % 3;
			if (random == MoveKind::charachase)
			{
				NowMoveKind = MoveKind::charachase;
			}
			else
			{
				NowMoveKind = MoveKind::randomwalk;
			}

			SetWalkTargetPositionflg = false;
			moveflame = 0;
		}
	}
	break;

	}

	//�p�x�ݒ�
	moveangle = atan2(targetPosition.z - position.z, targetPosition.x - position.x);

	//���x�ݒ�
	vx = cos(moveangle) * Speed;
	vz = sin(moveangle) * Speed;

	//�i�܂���
	if (moveonflg && attackflg == false)
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

	moveflame++;
}