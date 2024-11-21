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

	//角度設定
	angle = characterangle;

	//ポジション設定
	position.x += sin(angle) * DistanceWithCharacter;
	position.z += cos(angle) * DistanceWithCharacter;

	capRight = VAdd(position, VGet(-sin(angle + AngleCorrection) * HalfWidthSize, DistanceWithCharacter, -cos(angle + AngleCorrection) * HalfWidthSize));
	capLeft = VAdd(position, VGet(sin(angle + AngleCorrection) * HalfWidthSize, DistanceWithCharacter, cos(angle + AngleCorrection) * HalfWidthSize));

	//角度、ポジション反映
	MV1SetRotationXYZ(model, VGet(0.0f, angle + AngleCorrection, 0.0f));
	MV1SetPosition(model, position);
}

/// <summary>
/// 更新
/// </summary>
void Shield::Update(VECTOR characterPosition,float characterangle)
{
	VECTOR tentativepos = characterPosition;

	//モデル角度更新
	UpdateAngle(characterangle);

	//向きに追従
	tentativepos.x += sin(angle) * DistanceWithCharacter;
	tentativepos.z += cos(angle) * DistanceWithCharacter;

	//カプセル角度更新
	capRight = VAdd(position, VGet(-sin(angle  + AngleCorrection) * HalfWidthSize, DisttanceWithGround, -cos(angle + AngleCorrection) * HalfWidthSize));
	capLeft = VAdd(position, VGet(sin(angle + AngleCorrection) * HalfWidthSize, DisttanceWithGround, cos(angle + AngleCorrection) * HalfWidthSize));

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
	//DrawCapsule3D(capLeft, capRight, ShieldCapsuleRadius, 20, GetColor(127, 255, 0), GetColor(0, 255, 255), FALSE);
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

	MV1SetRotationXYZ(model, VGet(0.0f, angle + AngleCorrection, 0.0f));
}