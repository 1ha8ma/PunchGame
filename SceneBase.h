#pragma once

class SceneBase
{
public:
	//�R���X�g���N�^
	SceneBase();
	//�f�X�g���N�^
	virtual ~SceneBase() {};
	//������
	static SceneBase* InitializeBase();
	//�V�[�����Ƃ̏�����
	virtual void Initialize() abstract;
	//�V�[�����Ƃ̍X�V
	virtual SceneBase* Update() abstract;
	//�V�[�����Ƃ̕`��
	virtual void Draw() abstract;
};