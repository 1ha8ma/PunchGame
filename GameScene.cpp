#include"DxLib.h"
#include"Camera.h"
#include"Player.h"
#include"WoodBoard.h"
#include"SkyDome.h"
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
}

/// <summary>
/// �X�V
/// </summary>
/// <returns>���̃V�[��</returns>
SceneBase* GameScene::Update()
{
	camera->Update();
	player->Update(input->GetInputState());

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
}