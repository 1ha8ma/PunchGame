#pragma once
#include<vector>

class Enemy;

class EnemyManager
{
private:
	std::vector<Enemy*> enemy;

public:
	//�R���X�g���N�^
	EnemyManager();
	//�f�X�g���N�^
	~EnemyManager();
	//������
	void Initialize();
	//�X�V
	void Update();
	//�`��
	void Draw();

	//�G�̐�
	static const int NumberofEnemy;
};