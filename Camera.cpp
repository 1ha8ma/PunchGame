#include<math.h>
#include"DxLib.h"
#include"Camera.h"

/// <summary>
/// コンストラクタ
/// </summary>
Camera::Camera()
{
	Initialize();
}

/// <summary>
/// 初期化
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
/// ゲーム中更新
/// </summary>
void Camera::UpdateForGame()
{
	SetCameraPositionAndTarget_UpVecY(pos, lookpos);
}

/// <summary>
/// タイトル時更新
/// </summary>
void Camera::UpdateForTitle()
{
	pos.x = cos(angle) * 1500;
	pos.z = sin(angle) * 1500;

	angle += 0.001;
	if (angle > initangle + (DX_PI_F * 2))//一周したら角度を最初に戻す
	{
		angle = initangle;
	}

	SetCameraPositionAndTarget_UpVecY(pos, lookpos);
}