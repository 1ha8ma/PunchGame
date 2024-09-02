#include"DxLib.h"
#include"SceneBase.h"
#include"GameManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameManager::GameManager()
{
	//�V�[����������
	nowscene = SceneBase::InitializeBase();
}

/// <summary>
/// �X�V
/// </summary>
void GameManager::Update()
{
	//�V�[���X�V
	nextscene = nowscene->Update();

	//nextscene��nowscene�ƈႦ�΃V�[���ύX
	if (nextscene != nowscene)
	{
		ChangeScene();
	}
}

/// <summary>
/// �`��
/// </summary>
void GameManager::Draw()
{
	nowscene->Draw();
}

/// <summary>
/// �X�e�[�W�ύX
/// </summary>
void GameManager::ChangeScene()
{
	//���݂̃V�[�����폜
	delete(nowscene);

	//�V�[���؂�ւ�
	nowscene = nextscene;

	//�V�[��������
	nowscene->Initialize();

	//nextscene������
	nextscene = NULL;
}