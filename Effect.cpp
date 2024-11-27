#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Loader.h"
#include"Effect.h"

/// <summary>
/// コンストラクタ
/// </summary>
Effect::Effect()
{
	Loader* loader = loader->GetInstance();

	Effecthandle[EffectKind::Attack] = loader->GetHandle(Loader::Kind::PunchfiringEffect);
	Effecthandle[EffectKind::CharacterHit] = loader->GetHandle(Loader::Kind::PlayerhitEffect);
	Effecthandle[EffectKind::ShieldHit] = loader->GetHandle(Loader::Kind::ShieldhitEffect);

	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
Effect::~Effect()
{
	//エフェクト終了
	for (int i = 0; i < PlayingEffecthandle.size(); i++)
	{
		SetPosPlayingEffekseer3DEffect(PlayingEffecthandle[i], 0, -5000, 0);
		StopEffekseer3DEffect(PlayingEffecthandle[i]);
	}
	DrawEffekseer3D();

	//情報削除
	PlayingEffecthandle.clear();
	PlayingEffectKind.clear();
	PlayingEffectScale.clear();
	for (int i = 0; i < PlayingEffecthandle.size(); i++)
	{
		PlayingEffectKind.erase(PlayingEffectKind.begin() + i);
		PlayingEffecthandle.erase(PlayingEffecthandle.begin() + i);
		PlayingEffectScale.erase(PlayingEffectScale.begin() + i);
	}

	DrawEffekseer3D_End();
}

/// <summary>
/// 初期化
/// </summary>
void Effect::Initialize()
{
	PlayingEffectKind.clear();
	PlayingEffecthandle.clear();
	PlayingEffectScale.clear();
}

/// <summary>
/// エフェクト再生指示
/// </summary>
/// <param name="kind">エフェクトの種類</param>
/// <param name="playposition">初期再生位置</param>
/// <param name="initsize">初期サイズ</param>
/// <param name="playangle">再生角度</param>
/// <param name="playspeed">再生速度</param>
void Effect::PlayEffect(EffectKind kind, VECTOR playposition,VECTOR initsize, float playangle,float playspeed)
{
	//再生しているエフェクトを追加
	PlayingEffectKind.push_back(Effecthandle[kind]);
	//ハンドル追加
	PlayingEffecthandle.push_back(PlayEffekseer3DEffect(Effecthandle[kind]));

	//サイズ設定
	PlayingEffectScale.push_back(initsize);
	SetScalePlayingEffekseer3DEffect(PlayingEffecthandle.back(), PlayingEffectScale.back().x, PlayingEffectScale.back().y, PlayingEffectScale.back().z);
	//エフェクト速度設定
	SetSpeedPlayingEffekseer3DEffect(PlayingEffecthandle.back(), playspeed);
	//表示角度設定
	SetRotationPlayingEffekseer3DEffect(PlayingEffecthandle.back(), 0.0f, playangle, 0.0f);
	//ポジション反映
	SetPosPlayingEffekseer3DEffect(PlayingEffecthandle.back(), playposition.x, playposition.y, playposition.z);
}

/// <summary>
/// 更新
/// </summary>
void Effect::Update()
{
	for (int i = 0; i < PlayingEffecthandle.size(); i++)
	{
		//再生中のエフェクトが盾衝突だったらサイズを大きくする
		if (PlayingEffectKind[i] == Effecthandle[EffectKind::ShieldHit])
		{
			PlayingEffectScale[i] = VAdd(PlayingEffectScale[i], VGet(ExpansionSpeed, ExpansionSpeed, ExpansionSpeed));
		}

		//サイズ適用
		SetScalePlayingEffekseer3DEffect(PlayingEffecthandle[i], PlayingEffectScale[i].x, PlayingEffectScale[i].y, PlayingEffectScale[i].z);

		//再生終了していたら再生中から削除
		if (IsEffekseer3DEffectPlaying(PlayingEffecthandle[i]) == -1)
		{
			PlayingEffectKind.erase(PlayingEffectKind.begin() + i);
			PlayingEffecthandle.erase(PlayingEffecthandle.begin() + i);
			PlayingEffectScale.erase(PlayingEffectScale.begin() + i);
		}
	}
}

/// <summary>
/// 描画
/// </summary>
void Effect::Draw()
{
	DrawEffekseer3D();
}