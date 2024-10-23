#pragma once
#include<vector>

class Enemy;

class EnemyManager
{
private:
	std::vector<Enemy*> enemy;
	const float ModelSize = 4.5f;
	const VECTOR InitialPosition0 = VGet(-1000.0f, 100.0f, 1000.0f);
	const VECTOR InitialTargetDir0 = VGet(1.0f, 0.0f, -1.0f);
	const VECTOR InitialPosition1 = VGet(1000.f, 100.0f, 1000.0f);
	const VECTOR InitialTargetDir1 = VGet(-1.0f, 0.0f, -1.0f);
	const VECTOR InitialPosition2 = VGet(1000.0f, 100.0f, -700.0f);
	const VECTOR InitialTargetDir2 = VGet(-1.0f, 0.0f, 1.0f);

	bool playerhit;//�v���C���[�ɍU�����������Ă��邩
	

public:
	//�R���X�g���N�^
	EnemyManager();
	//�f�X�g���N�^
	~EnemyManager();
	//������
	void Initialize();
	//�X�V
	void Update(VECTOR playerpos, VECTOR playerTop, VECTOR playerBottom, VECTOR playershieldLeft, VECTOR playershieldRight, bool playeroutflg, std::vector<int> outchara);
	//�I����A�E����������X�V
	void ForeverUpdate();
	//�`��
	void Draw();

	void CheckOut(int i, bool hit);

	//�G�̐�
	static const int NumberofEnemy;

	VECTOR GetPosition(int i);
	VECTOR GetCapsuleTop(int i);
	VECTOR GetCapsuleBottom(int i);
	VECTOR GetShieldLeft(int i);
	VECTOR GetShieldRight(int i);
	bool GetOutflg(int i);
	int GetTargetNumber(int i);
	void SetTargetPosition(int i, VECTOR targetpos);
	float GetAngle(int i);
	bool GetPlayerhit() { return playerhit; }
	int GetNowMoveKind(int i);
};