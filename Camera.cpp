#include<math.h>
#include"DxLib.h"
#include"Utility.h"
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
/// �Q�[���J�n��������
/// </summary>
void Camera::GamestartInitialize()
{
	SetCameraNearFar(10.0f, 6000.0f);

	pos = VGet(0, 600, 0);
	lookpos = VGet(0, 0, 0);

	angle = initangle;
	SetCameraPositionAndTarget_UpVecY(pos, lookpos);
}

/// <summary>
/// �Q�[�����ł̍X�V
/// </summary>
void Camera::UpdateForGame()
{
	SetCameraPositionAndTarget_UpVecY(pos, lookpos);
}

/// <summary>
/// �X�^�[�g���o�ł̍X�V
/// </summary>
/// <param name="position">�|�W�V����</param>
/// <param name="lookpos">�����_</param>
void Camera::UpdateForStart(VECTOR position,VECTOR lookpos)
{
	SetCameraPositionAndTarget_UpVecY(position, lookpos);
}

/// <summary>
/// �^�C�g���ł̍X�V
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

/// <summary>
/// ���U���g�ł̍X�V
/// </summary>
/// <param name="winnerpos">���҃|�W�V����</param>
/// <param name="winnernumber">���҂̃L�����i���o�[</param>
void Camera::UpdateForResult(VECTOR winnerpos,int winnernumber)
{
	lookpos = winnerpos;

	//�g�����Ⴄ���獂����ύX
	if (winnernumber == static_cast<int>(CharaNumber::CPU0))
	{
		lookpos.y = winnerpos.y + 350;
	}
	else if (winnernumber == static_cast<int>(CharaNumber::CPU1))
	{
		lookpos.y = winnerpos.y + 200;
	}
	else
	{
		lookpos.y = winnerpos.y + 100;
	}

	SetCameraPositionAndTarget_UpVecY(pos, lookpos);
}