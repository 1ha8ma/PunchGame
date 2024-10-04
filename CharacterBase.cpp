#include<math.h>
#include"DxLib.h"
#include"Utility.h"
#include"Shield.h"
#include"Fist.h"
#include"CharacterBase.h"

/// <summary>
/// コンストラクタ
/// </summary>
CharacterBase::CharacterBase()
{
	shield = new Shield();
	fist = new Fist();
}

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
///　他クラス初期化
/// </summary>
void CharacterBase::OtherClassInitialize()
{
	if (outflg == false)
	{
		fist->Initialize();
	}
	shield->Initialize();
}

/// <summary>
/// 他クラスの更新
/// </summary>
void CharacterBase::OtherClassUpdate(bool shieldhit)
{
	fist->Update(position, angle, attackflg,shieldhit);
	shield->Update(position, angle);
}

/// <summary>
/// 拳とキャラクターの当たり判定
/// </summary>
/// <param name="charatop">キャラ上</param>
/// <param name="charabottom">キャラ下</param>
/// <param name="charaR">キャラ半径</param>
bool CharacterBase::FistWithCharacter(VECTOR charatop, VECTOR charabottom, float charaR,bool charaout)
{
	float len;
	bool hit = false;//攻撃が当たった

	//2つの線分の最短距離を求める
	len = Segment_Segment_MinLength(fist->GetcapFront(), fist->GetcapBack(), charatop, charabottom);

  	if (len < Fist::FistCapsuleRadius + charaR)
	{
		hit = true;
	}
	else
	{
		hit = false;
	}

	//if (hit && charaout == false)
	//{
	//	//printfDx("hit");
	//}

	return hit;
}

/// <summary>
/// 拳と盾の当たり判定
/// </summary>
/// <param name="ShieldLeft">盾左</param>
/// <param name="ShieldRight">盾右</param>
/// <param name="shieldR">盾半径</param>
/// <returns>当たっているか</returns>
bool CharacterBase::FistWithShield(VECTOR ShieldLeft, VECTOR ShieldRight, float shieldR)
{
	float len;
	bool hit = false;//盾に当たった

	//2つの線分の最短距離を求める
	len = Segment_Segment_MinLength(fist->GetcapFront(), fist->GetcapBack(), ShieldLeft, ShieldRight);

	if (len < Fist::FistCapsuleRadius + shieldR)
	{
		hit = true;
	}
	else
	{
		hit = false;
	}

	if (hit)
	{
		//printfDx("shieldhit");
	}

	return hit;
}

/// <summary>
/// 攻撃に当たったか
/// </summary>
/// <param name="hit">当たったか</param>
void CharacterBase::CheckOut(bool hit)
{
	if (outflg == false && hit)
	{
 		outflg = true;
	}
}

/// <summary>
/// キャラの吹っ飛び動作
/// </summary>
void CharacterBase::Blow()
{
	if (outflg && position.y < 2000)
	{
		position = VAdd(position, VGet(0, 100, 0));
		//ポジション反映
		MV1SetPosition(model, position);
	}
}

/// <summary>
/// カプセル更新
/// </summary>
void CharacterBase::UpdateCapsule()
{
	//当たり判定カプセル
	capsuleTop = VAdd(position, VGet(0, 600, 0));
	capsuleBottom = VAdd(position, VGet(0, 0, 0));
}

VECTOR CharacterBase::GetShieldLeft()
{
	return shield->GetcapLeft();
}

VECTOR CharacterBase::GetShieldRight()
{
	return shield->GetcapRight();
}

/// <summary>
/// 描画
/// </summary>
void CharacterBase::Draw()
{
	//DrawCapsule3D(capsuleTop, capsuleBottom, CharacterR, 8, GetColor(127, 255, 0), GetColor(0, 255, 255), FALSE);
	MV1DrawModel(model);
	shield->Draw();
	if (outflg == false)
	{
		fist->Draw();
	}
}