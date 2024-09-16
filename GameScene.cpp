#include"DxLib.h"
#include"Camera.h"
#include"Player.h"
#include"WoodBoard.h"
#include"SkyDome.h"
#include"Shield.h"
#include"InputManager.h"
#include"GameScene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameScene::GameScene()
{
	//�C���X�^���X��
	wood = new WoodBoard();
	camera = new Camera();
	player = new Player();
	skydome = new SkyDome();
	input = new InputManager();
	shield = new Shield();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameScene::~GameScene()
{

}

/// <summary>
/// ������
/// </summary>
void GameScene::Initialize()
{
	camera->Initialize();
	player->Initialize();
	shield->Initialize();
}

/// <summary>
/// �X�V
/// </summary>
/// <returns>���̃V�[��</returns>
SceneBase* GameScene::Update()
{
	camera->Update();
	player->Update(input->GetInputState());
	shield->Update(player->GetPos(), player->GetAngle());

	//�����I�������𖞂����Ă��Ȃ�������
	return this;
}

/// <summary>
/// �`��
/// </summary>
void GameScene::Draw()
{
	skydome->Draw();
	wood->Draw();
	player->Draw();
	shield->Draw();
}