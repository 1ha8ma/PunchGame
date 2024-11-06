#include<math.h>
#include"DxLib.h"
#include"Utility.h"
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
/// ゲーム開始時初期化
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
/// ゲーム中での更新
/// </summary>
void Camera::UpdateForGame()
{
	SetCameraPositionAndTarget_UpVecY(pos, lookpos);
}

/// <summary>
/// スタート演出での更新
/// </summary>
/// <param name="position">ポジション</param>
/// <param name="lookpos">注視点</param>
void Camera::UpdateForStart(VECTOR position,VECTOR lookpos)
{
	SetCameraPositionAndTarget_UpVecY(position, lookpos);
}

/// <summary>
/// タイトルでの更新
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

/// <summary>
/// リザルトでの更新
/// </summary>
/// <param name="winnerpos">勝者ポジション</param>
/// <param name="winnernumber">勝者のキャラナンバー</param>
void Camera::UpdateForResult(VECTOR winnerpos,int winnernumber)
{
	lookpos = winnerpos;

	//身長が違うから高さを変更
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