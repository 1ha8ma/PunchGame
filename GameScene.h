#pragma once
#include<vector>
#include"SceneBase.h"

class Camera;
class Player;
class Stage;
class SkyDome;
class InputManager;
class EnemyManager;
class UI;
class Pause;
class ResultScene;
class StartScene;
class BGMManager;
class SEManager;

class GameScene :public SceneBase
{
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

private:
	Stage* stage;
	Camera* camera;
	Player* player;
	SkyDome* skydome;
	InputManager* input;
	EnemyManager* enemy;
	UI* ui;
	Pause* pausescene;
	ResultScene* resultscene;
	StartScene* startscene;
	BGMManager* bgmmanager;
	SEManager* semanager;

	//�Q�[���V�[�����̃X�e�[�g
	int nowstate;
	enum GameSceneState
	{
		start,//�X�^�[�g�V�[��
		game,//�Q�[���V�[��
		pause,//�ꎞ��~
		result,//���U���g�V�[��
	};

	bool pauseinputpossible;
	bool outpauseinputflg;//�ꎞ��~������̓��͂������Ȃ���
	
	bool playeroutcheck;//�v���C���[���U���ɓ�������
	std::vector<int> outchara;//�E�������L����

	VECTOR winnerpos;//���҃|�W�V����
	float winnerangle;//���Ҋp�x
	bool scenechange;//�V�[���؂�ւ��t���O
	int winnernumber;//���҂̃L�����i���o�[
};