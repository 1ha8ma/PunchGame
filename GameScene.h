#pragma once
#include<vector>
#include"SceneBase.h"

class Camera;
class Player;
class WoodBoard;
class SkyDome;
class InputManager;
class EnemyManager;

class GameScene :public SceneBase
{
private:
	WoodBoard* wood;
	Camera* camera;
	Player* player;
	SkyDome* skydome;
	InputManager* input;
	EnemyManager* enemy;

	bool shieldhit;//���ɓ������Ă��邩
	std::vector<int> outchara;//�E�������L����

public:
	//�R���X�g���N�^
	GameScene();
	//�f�X�g���N�^
	~GameScene()override;
	//������
	void Initialize()override;
	//�X�V
	SceneBase* Update()override;
	//�`��
	void Draw()override;
};