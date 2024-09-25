#include<math.h>
#include"DxLib.h"
#include"Utility.h"
#include"CharacterBase.h"

/// <summary>
/// 角度更新
/// </summary>
void CharacterBase::UpdateAngle()
{
	//移動方向にモデルの方向を近づける
	float targetAngle;//目標の角度
	float difference;//目標角度と現在の角度の差

	//目標の方向ベクトルから角度値を算出する
	targetAngle = static_cast<float>(atan2(targetLookDirection.x, targetLookDirection.z));

	//目標の角度と現在の角度との差を割り出す
	//最初は引き算
	difference = targetAngle - angle;

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
	angle = targetAngle - difference;

	MV1SetRotationXYZ(model, VGet(0.0f, angle + DX_PI_F, 0.0f));
}

/// <summary>
/// アニメーション切り替え
/// </summary>
/// <param name="nextkind">次のアニメーション</param>
void CharacterBase::ChangeAnimation(AnimKind nextkind)
{
	//入れ替え時に前のモーションが有効だったらデタッチする
	if (nowPlayAnim != -1)
	{
		MV1DetachAnim(model, nowPlayAnim);
		nowPlayAnim = -1;
	}

	//新しくアニメーションをアタッチ
	nowPlayAnimKind = static_cast<int>(nextkind);
	nowPlayAnim = MV1AttachAnim(model, static_cast<int>(nextkind));
	animtotaltime = MV1GetAttachAnimTotalTime(model, nowPlayAnim);
	animplaytime = 0.0f;
}

/// <summary>
/// アニメーション再生
/// </summary>
void CharacterBase::PlayAnimation()
{
	//攻撃中の場合
	if (attackflg)
	{
		isanimflg = true;
	}

	//アニメーション再生
	if (isanimflg)
	{
		animplaytime += 0.5f;
	}

	//アニメーションが総再生時間に達したら
	if (animplaytime >= animtotaltime)
	{
		if (nowPlayAnimKind == static_cast<int>(AnimKind::Punch))//攻撃モーションが終わった場合
		{
			attackflg = false;
			ChangeAnimation(AnimKind::Run);
		}
		if (nowPlayAnimKind == static_cast<int>(AnimKind::Run))//走るモーションが終わった場合
		{
			animplaytime = 0.0f;
		}
	}

	//再生時間をセット
	MV1SetAttachAnimTime(model, nowPlayAnim, animplaytime);
}

/// <summary>
/// 攻撃処理
/// </summary>
void CharacterBase::Attack()
{
	//攻撃モーションに変更
	if (attackflg == false)
	{
		ChangeAnimation(AnimKind::Punch);
		attackflg = true;
	}
}

/// <summary>
/// 描画
/// </summary>
void CharacterBase::Draw()
{
	MV1DrawModel(model);
}