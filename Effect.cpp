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
	DrawEffekseer3D_End();
}

/// <summary>
/// 初期化
/// </summary>
void Effect::Initialize()
{
	PlayingEffectKind.clear();
	PlayingEffecthandle.clear();
	PlayingEffectSize.clear();
}

/// <summary>
/// エフェクト再生指示
/// </summary>
/// <param name="kind">エフェクトの種類</param>
/// <param name="playposition">再生位置</param>
/// <param name="initsize">最初のサイズ</param>
/// <param name="playangle">再生角度</param>
/// <param name="playspeed">再生速度</param>
void Effect::PlayEffect(EffectKind kind, VECTOR playposition,VECTOR initsize, float playangle,float playspeed)
{
	//再生しているエフェクトを追加
	PlayingEffectKind.push_back(Effecthandle[kind]);
	//ハンドル追加
	PlayingEffecthandle.push_back(PlayEffekseer3DEffect(Effecthandle[kind]));

	//サイズ設定
	PlayingEffectSize.push_back(initsize);
	SetScalePlayingEffekseer3DEffect(PlayingEffecthandle.back(), PlayingEffectSize.back().x, PlayingEffectSize.back().y, PlayingEffectSize.back().z);
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
			PlayingEffectSize[i] = VAdd(PlayingEffectSize[i], VGet(ExpansionSpeed, ExpansionSpeed, ExpansionSpeed));
		}

		//サイズ適用
		SetScalePlayingEffekseer3DEffect(PlayingEffecthandle[i], PlayingEffectSize[i].x, PlayingEffectSize[i].y, PlayingEffectSize[i].z);

		//再生終了していたら再生中から削除
		if (IsEffekseer3DEffectPlaying(PlayingEffecthandle[i]) == -1)
		{
			PlayingEffectKind.erase(PlayingEffectKind.begin() + i);
			PlayingEffecthandle.erase(PlayingEffecthandle.begin() + i);
			PlayingEffectSize.erase(PlayingEffectSize.begin() + i);
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