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
	angle = 0.0f;
	this->position = position;
	this->targetDirection = targetDirection;

	targetdistance = 0.0f;

	MV1SetPosition(model, this->position);
}

/// <summary>
/// �߂��L�����N�^�[�̊m�F
/// </summary>
/// <param name="charapos">���ׂ�L�����N�^�[�̃|�W�V����</param>
void Enemy::CheckNearCharacter(VECTOR charapos)
{
	//2�L�����̋��������
	float calc = pow((position.x - charapos.x), 2.0f) + pow((position.y - charapos.y), 2.0f) + pow((position.z - position.z), 2.0f);
	float distance = sqrt(calc);

	//�������O������̂��Z����΃^�[�Q�b�g���X�V
	if (distance < targetdistance)
	{
		targetCharaPos = charapos;
	}
}

/// <summary>
/// �X�V
/// </summary>
void Enemy::Update()
{
	//����

	//�p�x�X�V
	UpdateAngle();

	//�|�W�V�������f
	MV1SetPosition(model, position);
}