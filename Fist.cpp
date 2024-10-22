#include<math.h>
#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Utility.h"
#include"Loader.h"
#include"SEManager.h"
#include"Fist.h"

const float Fist::FistCapsuleRadius = 120.0f;

/// <summary>
/// コンストラクタ
/// </summary>
Fist::Fist()
{
	//他クラスインスタンス化
	semanager = new SEManager();

	//モデルロード
	Loader* loader = loader->GetInstance();
	model = MV1DuplicateModel(loader->GetHandle(Loader::Kind::FistModel));

	//エフェクトロード
	firingeffecthandle = loader->GetHandle(Loader::Kind::PunchfiringEffect);

	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
Fist::~Fist()
{

}
	
/// <summary>
/// 初期化
/// </summary>
void Fist::Initialize()
{
	//モデル関係
	modelangle = 0.0f;
	//position = VGet(0, 400, 0);
	punchingflg = false;

	//エフェクト関係
	PlayingEffect = -1;
	playfiringefectflg = false;
}

/// <summary>
/// 更新
/// </summary>
void Fist::Update(VECTOR charapos,float charaangle,bool punchflg,bool shieldhit)
{
	//エフェクトカメラ同期
	Effekseer_Sync3DSetting();
	//エフェクト速度設定
	SetSpeedPlayingEffekseer3DEffect(PlayingEffect, 0.05f);

	PunchMove(punchflg, charaangle, charapos,shieldhit);

	UpdateAngle(charaangle);

	//エフェクト更新
	UpdateEffekseer3D();

	MV1SetPosition(model, position);
}

/// <summary>
/// 描画
/// </summary>
void Fist::Draw()
{
	if (punchingflg)
	{
		//DrawCapsule3D(capFront, capBack, FistCapsuleRadius, 8, GetColor(127, 255, 0), GetColor(0, 255, 255), FALSE);
		MV1DrawModel(model);
		DrawEffekseer3D();
	}
}

/// <summary>
/// パンチの動き
/// </summary>
void Fist::PunchMove(bool punchflg,float charaangle,VECTOR charapos,bool shieldhit)
{
	//パンチしたとき
	if (punchflg && punchingflg == false)
	{
		//プレイヤーからポジション等のコピー
		position = charapos;
		position.y = 400.0f;
		punchangle = charaangle;
		//パンチの角度設定
		vx = sin(punchangle) * PunchSpeed;
		vz = cos(punchangle) * PunchSpeed;
		position.x += sin(punchangle) * 250.0f;
		position.z += cos(punchangle) * 250.0f;
		//エフェクト設定
		firingefectposition = charapos;
		firingefectposition.x += sin(punchangle) * 250.0f;
		firingefectposition.y = 400.0f;
		firingefectposition.z += cos(punchangle) * 250.0f;
		//SE再生
		semanager->PlaySE(SEManager::SEKind::AttackSE);

		//フラグ変更
		punchingflg = true;
		playfiringefectflg = true;
	}

	//パンチ中
	if (punchingflg)
	{
		//当たり判定カプセルの角度設定
		capFront = VAdd(position, VGet(sin(punchangle) * 200, 0, cos(punchangle) * 200));
		capBack = VAdd(position, VGet(-sin(punchangle) * 100, 0, -cos(punchangle) * 100));

		//進ませる
		if (shieldhit==false)
		{
			position.x += vx;
			position.z += vz;
		}

		//モーションが終わるとフラグ変更
		if (punchflg == false)
		{
			punchingflg = false;
		}
	}
	//パンチ中でないとき
	else
	{
		//ポジションをキャラと同じにしてサイズを0にする
		position = charapos;
		capFront = VAdd(position, VGet(0, 0, 0));
		capBack = VAdd(position, VGet(0, 0, 0));
		playfiringefectflg = false;
	}

	//エフェクト再生
	if (playfiringefectflg)
	{
		PlayingEffect = PlayEffekseer3DEffect(firingeffecthandle);
		SetPosPlayingEffekseer3DEffect(PlayingEffect, firingefectposition.x, firingefectposition.y, firingefectposition.z);
		SetRotationPlayingEffekseer3DEffect(PlayingEffect, firingefectangle.x, firingefectangle.y, firingefectangle.z);
		playfiringefectflg = false;
	}
}

/// <summary>
/// 角度更新
/// </summary>
/// <param name="charaangle"></param>
void Fist::UpdateAngle(float charaangle)
{
	float difference;//目標角度と現在の角度の差

	//差を出す
	difference = charaangle - modelangle;

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
	modelangle = charaangle - difference;

	MV1SetRotationXYZ(model, VGet(0.0f, modelangle + DX_PI_F, 0.0f));
	firingefectangle = VGet(0.0f, modelangle + DX_PI_F, 0.0f);
}