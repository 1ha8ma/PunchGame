#pragma once

class SceneBase;

class GameManager
{
private:
	//�V�[��
	SceneBase* nowscene;
	SceneBase* nextscene;

	//�V�[���؂�ւ�
	void ChangeScene();

public:
	//�R���X�g���N�^
	GameManager();
	//�X�V
	void Update();
	//�`��
	void Draw();
};