#pragma once

class SceneBase;

class GameManager
{
public:
	//�R���X�g���N�^
	GameManager();
	//�X�V
	void Update();
	//�`��
	void Draw();

private:
	//�V�[��
	SceneBase* nowscene;
	SceneBase* nextscene;

	//�V�[���؂�ւ�
	void ChangeScene();
};