#pragma once
#include"SceneBase.h"

class Camera;
class Player;
class WoodBoard;
class SkyDome;
class InputManager;
class Shield;
class Fist;
class EnemyManager;

class GameScene :public SceneBase
{
private:
	WoodBoard* wood;
	Camera* camera;
	Player* player;
	SkyDome* skydome;
	InputManager* input;
	Shield* shield;
	Fist* fist;
	EnemyManager* enemy;

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