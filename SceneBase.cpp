#include"DxLib.h"
#include"GameScene.h"
#include"SceneBase.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneBase::SceneBase()
{

}

/// <summary>
/// �V�[�����ŏ��ɂ���
/// </summary>
/// <returns>�ŏ��ɂ������V�[��</returns>
SceneBase* SceneBase::InitializeBase()
{
	return new GameScene();
}