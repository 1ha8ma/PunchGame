#pragma once
#include<vector>
#include"SceneBase.h"

class Camera;
class Player;
class WoodBoard;
class SkyDome;
class InputManager;
class EnemyManager;
class GameUI;
class ResultScene;
class StartScene;
class BGMManager;
class SEManager;

class GameScene :public SceneBase
{
private:
	WoodBoard* wood;
	Camera* camera;
	Player* player;
	SkyDome* skydome;
	InputManager* input;
	EnemyManager* enemy;
	GameUI* gameui;
	ResultScene* resultscene;
	StartScene* startscene;
	BGMManager* bgmmanager;
	SEManager* semanager;

	bool gamestartflg;//�Q�[���J�n�t���O
	bool gameendflg;//�Q�[�������t���O
	bool playeroutcheck;//�v���C���[���U���ɓ�������
	bool playerattackshieldhit;//���ɓ������Ă��邩
	std::vector<int> outchara;//�E�������L����

	VECTOR winnerpos;//���҃|�W�V����
	float winnerangle;//���Ҋp�x
	bool scenechange;//�V�[���؂�ւ��t���O
	int winnernumber;//���҂̃L�����i���o�[

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