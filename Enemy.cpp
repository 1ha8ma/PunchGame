#include<math.h>
#include"DxLib.h"
#include"Enemy.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="modelhandle">���f���n���h���ԍ�</param>
/// <param name="modelsize">���f���T�C�Y</param>
/// <param name="position">�|�W�V����</param>
/// <param name="targetDirection">��������</param>
Enemy::Enemy(const TCHAR *modelhandle,float modelsize,VECTOR position,VECTOR targetDirection)
{
	model = MV1LoadModel(modelhandle);
	nowPlayAnim = MV1AttachAnim(model, static_cast<int>(AnimKind::Run));
	animtotaltime = MV1GetAttachAnimTotalTime(model, nowPlayAnim);

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
	//�A�j���[�V����������
	animplaytime = 0.0f;
	nowPlayAnimKind = static_cast<int>(AnimKind::Run);
	nowPlayAnim = static_cast<int>(AnimKind::Run);
	prevPlayAnim = -1;

	angle = 0.0f;
	this->position = position;
	this->targetLookDirection = targetDirection;

	targetdistance = 10000.0f;
	targetCharaAngle = 0.0f;

	MV1SetPosition(model, this->position);
}

/// <summary>
/// �߂��L�����N�^�[�̊m�F
/// </summary>
/// <param name="charapos">���ׂ�L�����N�^�[�̃|�W�V����</param>
void Enemy::CheckNearCharacter(VECTOR charapos)
{
	//2�L�����̋��������
	float calc = pow((position.x - charapos.x), 2.0f) + pow((position.y - charapos.y), 2.0f) + pow((position.z - charapos.z), 2.0f);
	float distance = sqrt(calc);

	//�������O������̂��Z����΃^�[�Q�b�g���X�V
	if (distance < targetdistance)
	{
		targetdistance = distance;
		targetCharaPos = charapos;
	}
}

/// <summary>
/// �ړ�����
/// </summary>
void Enemy::Move()
{
	//�p�x�ݒ�
	targetCharaAngle = atan2(targetCharaPos.z - position.z, targetCharaPos.x - position.x);
	vx = cos(targetCharaAngle) * Speed;
	vz = sin(targetCharaAngle) * Speed;

	//�i�܂���
	if (targetdistance > 1000)
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
void Enemy::Update()
{
	//����
	Move();

	//�A�j���[�V�����Đ�
	PlayAnimation();

	//�p�x�X�V
	UpdateAngle();

	//�|�W�V�������f
	MV1SetPosition(model, position);
}