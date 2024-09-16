#include<math.h>
#include"DxLib.h"
#include"Shield.h"

/// <summary>
/// コンストラクタ
/// </summary>
Shield::Shield()
{
	model = MV1LoadModel("3D/Shield.mv1");

	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
Shield::~Shield()
{

}

/// <summary>
/// 初期化
/// </summary>
void Shield::Initialize()
{
	position = VGet(0.0f, 100.0f, 0.0f);
	angle = 0.0f;

	o = false;

	MV1SetPosition(model, position);
}

/// <summary>
/// 更新
/// </summary>
void Shield::Update(VECTOR characterPosition,float characterangle)
{
	VECTOR tentativepos = characterPosition;//仮のポジション

	//向きに追従
	tentativepos.x += sin(characterangle) * DistanceWithCharacter;
	tentativepos.z += cos(characterangle) * DistanceWithCharacter;

	//角度更新
	UpdateAngle(characterangle);

	//ポジションに反映
	position = tentativepos;
	MV1SetPosition(model, position);
}

/// <summary>
/// 描画
/// </summary>
void Shield::Draw()
{
	MV1DrawModel(model);
}

/// <summary>
/// 角度更新
/// </summary>
void Shield::UpdateAngle(float characterangle)
{
	float difference;//目標角度と現在の角度の差

	//差を出す
	difference = characterangle - angle;

	//ある方向からある方向の差が180度以上になることはないので差が180度以上になっていたら修正する
	if (difference < -DX_PI_F)
	{
		difference += DX_TWO_PI_F;
	}
	else if (difference > DX_PI_F)
	{
		difference -= DX_TWO_PI_F;
	}

	//角度の差を0に近づける
	if (difference > 0.0f)//差がマイナスの場合
	{
		difference -= AngleSpeed;
		if (difference < 0.0f)
		{
			difference = 0.0f;
		}
	}
	else//差がプラスの場合
	{
		difference += AngleSpeed;
		if (difference > 0.0f)
		{
			difference = 0.0f;
		}
	}

	//モデルの角度を更新
	angle = characterangle - difference;

	MV1SetRotationXYZ(model, VGet(0.0f, angle - 1.5f + DX_PI_F, 0.0f));
}