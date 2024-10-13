#include<math.h>
#include"DxLib.h"
#include"Camera.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Camera::Camera()
{
	Initialize();
}

/// <summary>
/// ������
/// </summary>
void Camera::Initialize()
{
	SetCameraNearFar(10.0f, 6000.0f);

	pos = VGet(0, 2000, -1500);
	lookpos = VGet(0, 0, 0);

	angle = initangle;
	SetCameraPositionAndTarget_UpVecY(pos, lookpos);
}

/// <summary>
/// �Q�[�����X�V
/// </summary>
void Camera::UpdateForGame()
{
	SetCameraPositionAndTarget_UpVecY(pos, lookpos);
}

/// <summary>
/// �^�C�g�����X�V
/// </summary>
void Camera::UpdateForTitle()
{
	pos.x = cos(angle) * 1500;
	pos.z = sin(angle) * 1500;

	angle += 0.001;
	if (angle > initangle + (DX_PI_F * 2))//���������p�x���ŏ��ɖ߂�
	{
		angle = initangle;
	}

	SetCameraPositionAndTarget_UpVecY(pos, lookpos);
}