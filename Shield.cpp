#include<math.h>
#include"DxLib.h"
#include"Utility.h"
#include"Loader.h"
#include"Shield.h"

/// <summary>
/// コンストラクタ
/// </summary>
Shield::Shield()
{
	Loader* loader = loader->GetInstance();
	model = MV1DuplicateModel(loader->GetHandle(Loader::Kind::ShieldModel));
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
void Shield::Initialize(VECTOR charaposition,float characterangle)
{
	//ポジションコピー
	position = charaposition;

	//ポジション設定
	position.x += sin(characterangle) * DistanceWithCharacter;
	position.z += cos(characterangle) * DistanceWithCharacter;

	capRight = VAdd(position, VGet(-sin(characterangle - 1.5f) * 150, 200, -cos(characterangle - 1.5f) * 150));
	capLeft = VAdd(position, VGet(sin(characterangle - 1.5f) * 150, 200, cos(characterangle - 1.5f) * 150));

	//角度設定
	angle = characterangle;

	//角度、ポジション反映
	MV1SetRotationXYZ(model, VGet(0.0f, angle - 1.5f + DX_PI_F, 0.0f));
	MV1SetPosition(model, position);
}

/// <summary>
/// 更新
/// </summary>
void Shield::Update(VECTOR characterPosition,float characterangle)
{
	VECTOR tentativepos = characterPosition;

	//向きに追従
	tentativepos.x += sin(characterangle) * DistanceWithCharacter;
	tentativepos.z += cos(characterangle) * DistanceWithCharacter;

	//モデル角度更新
	UpdateAngle(characterangle);

	//カプセル角度更新
	capRight = VAdd(position, VGet(-sin(characterangle - 1.5f) * 150, 200, -cos(characterangle - 1.5f) * 150));
	capLeft = VAdd(position, VGet(sin(characterangle - 1.5f) * 150, 200, cos(characterangle - 1.5f) * 150));

	//ポジションに反映
	position = tentativepos;
	MV1SetPosition(model, position);
}

void Shield::ReflectPosition(VECTOR newposition)
{
	MV1SetPosition(model, newposition);
}

/// <summary>
/// 描画
/// </summary>
void Shield::Draw()
{
	//当たり判定カプセル
	//DrawCapsule3D(capLeft, capRight, CapsuleRadius, 20, GetColor(127, 255, 0), GetColor(0, 255, 255), FALSE);
	MV1DrawModel(model);
}

void Shield::InitializeAngle(float charaangle)
{
	
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