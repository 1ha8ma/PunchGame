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
	SetCameraNearFar(1.0f, 6000.0f);

	pos = VGet(0, 2000, -1500);
	//pos = VGet(0, 1000, -1000);
	lookpos = VGet(0, 0, 0);

	SetCameraPositionAndTarget_UpVecY(pos, lookpos);
}

/// <summary>
/// �X�V
/// </summary>
void Camera::Update()
{
	/*pos.x += 1;
	pos.z += 1;*/

	SetCameraPositionAndTarget_UpVecY(pos, lookpos);
}