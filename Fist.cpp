#include<math.h>
#include"DxLib.h"
#include"Utility.h"
#include"Loader.h"
#include"Effect.h"
#include"SEManager.h"
#include"Fist.h"

/// <summary>
/// コンストラクタ
/// </summary>
Fist::Fist()
{
	//他クラスインスタンス化
	semanager = new SEManager();
	effect = new Effect();

	//モデルロード
	Loader* loader = loader->GetInstance();
	model = MV1DuplicateModel(loader->GetHandle(Loader::Kind::FistModel));

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
	punchingflg = false;
	size = 1.0f;

	//エフェクト関係
	playfiringefectflg = false;
}

/// <summary>
/// 更新
/// </summary>
void Fist::Update(VECTOR charapos,float charaangle,bool attackflg,bool shieldhit)
{
	//パンチの動き
	PunchMove(attackflg, charaangle, charapos,shieldhit);

	//ポジション反映
	MV1SetPosition(model, position);
}

/// <summary>
/// 描画
/// </summary>
void Fist::Draw()
{
	if (punchingflg)
	{
		DrawCapsule3D(capFront, capBack, FistCapsuleRadius, 8, GetColor(127, 255, 0), GetColor(0, 255, 255), FALSE);
		MV1DrawModel(model);
		effect->Draw();
	}
}

/// <summary>
/// パンチの動き
/// </summary>
void Fist::PunchMove(bool attackflg,float charaangle,VECTOR charapos,bool shieldhit)
{
	//パンチしたとき
	if (attackflg && punchingflg == false)
	{
		//プレイヤーからポジション等のコピー
		position = charapos;
		position.y = 400.0f;
		punchangle = charaangle;
		//パンチの角度設定
		velocity.x = sin(punchangle) * PunchSpeed;
		velocity.y = 0.0f;
		velocity.z = cos(punchangle) * PunchSpeed;
		position.x += sin(punchangle) * 250.0f;
		position.z += cos(punchangle) * 250.0f;
		modelangle = charaangle;
		MV1SetRotationXYZ(model, VGet(0.0f, modelangle + DX_PI_F, 0.0f));
		//サイズ設定
		size = 0.1f;
		//エフェクト設定
		effect->PlayEffect(Effect::EffectKind::Attack, VGet(charapos.x + sin(punchangle) * 250.0f, 400.0f, charapos.z + cos(punchangle) * 250.0f), VGet(1, 1, 1), modelangle, 0.5f);
		//SE再生
		semanager->PlaySE(SEManager::SEKind::AttackSE);

		shieldhitflg = false;

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
		if (shieldhitflg == false)
		{
			position = VAdd(position, velocity);
		}

		//だんだんサイズを大きくする
		if (shieldhitflg == false && size < 1.0f)
		{
			size += 0.07f;
			if (size > 1.0f)
			{
				size = 1.0f;
			}
		}
		MV1SetScale(model, VGet(size, size, size));

		//もし盾に当たったらだんだん小さくして消す
		if (shieldhit)
		{
			shieldhitflg = true;
		}
		if (shieldhitflg)
		{
			if (size > 0.0f)
			{
				size -= 0.07;
			}
			if (size < 0.0f)
			{
				size = 0.0f;
			}
		}

		//モーションが終わるとフラグ変更
		if (attackflg == false)
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
		effect->Update();
	}
}