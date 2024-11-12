#include<math.h>
#include"DxLib.h"
#include"Utility.h"
#include"Shield.h"
#include"Fist.h"
#include"Effect.h"
#include"SEManager.h"
#include"Collision.h"
#include"CharacterBase.h"

/// <summary>
/// コンストラクタ
/// </summary>
CharacterBase::CharacterBase()
{
	//他クラスインスタンス化
	shield = new Shield();
	fist = new Fist();
	semanager = new SEManager();
	effect = new Effect();
	collision = new Collision();
}

/// <summary>
/// デストラクタ
/// </summary>
CharacterBase::~CharacterBase()
{
	//アニメーションをデタッチ
	MV1DetachAnim(model, nowPlayAnim);
	
	delete shield;
	delete fist;
	delete semanager;
	delete effect;
}

/// <summary>
/// ベース初期化
/// </summary>
void CharacterBase::BaseInitialize()
{
	//アニメーション関係
	isanimflg = false;
	animplaytime = 0.0f;
	nowPlayAnimKind = static_cast<int>(AnimKind::Run);
	nowPlayAnim = MV1AttachAnim(model, static_cast<int>(AnimKind::Run));
	animtotaltime = MV1GetAttachAnimTotalTime(model, nowPlayAnim);
	prevPlayAnim = -1;

	//モデル関係
	angle = 0.0f;
	outflg = false;

	//攻撃関係
	attackflg = false;
	attackOnCollision = false;

	//盾関係
	shieldhit = false;

	//エフェクト関係
	Playplayerhiteffectflg = false;
	Playshieldhiteffectflg = false;

	shieldhitseflg = false;
}

/// <summary>
/// 角度初期化
/// </summary>
void CharacterBase::InitializeAngle()
{
	float targetAngle;
	float difference;

	//目標の方向ベクトル
	targetAngle = static_cast<float>(atan2(targetLookDirection.x, targetLookDirection.z));

	angle = targetAngle;

	MV1SetRotationXYZ(model, VGet(0.0f, angle + DX_PI_F, 0.0f));
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
		if (nowPlayAnimKind == static_cast<int>(AnimKind::Run))
		{
			animplaytime += 0.5f;
		}
		if (nowPlayAnimKind == static_cast<int>(AnimKind::Punch))
		{
			animplaytime += 0.7f;
		}
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
	if (!attackflg)
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
	if (!outflg)
	{
		fist->Initialize();
	}
	shield->Initialize(position, angle);
}

/// <summary>
/// エフェクト更新
/// </summary>
void CharacterBase::UpdateEffect()
{
	effect->Update();

	//エフェクトフラグを戻す
	if (Playshieldhiteffectflg && !shieldhit)
	{
		Playshieldhiteffectflg = false;
	}
}

/// <summary>
/// 他クラスの更新
/// </summary>
void CharacterBase::OtherClassUpdate()
{
	fist->Update(position, angle, attackflg,shieldhit);
	shield->Update(position, angle);
}

/// <summary>
/// 攻撃に当たり判定を付けるか判断
/// </summary>
void CharacterBase::CheckAttackOnCollision()
{
	if (attackflg && fist->GetSize() == 1.0f)
	{
		attackOnCollision = true;
	}
	else
	{
		attackOnCollision = false;
	}
}

/// <summary>
/// 拳とキャラクターの当たり判定
/// </summary>
/// <param name="charatop">判定対象キャラ上</param>
/// <param name="charabottom">判定対象キャラ下</param>
/// <param name="charaR">キャラ半径</param>
bool CharacterBase::FistWithCharacter(VECTOR charatop, VECTOR charabottom, bool charaout)
{
	bool hit = false;//攻撃が当たった

	if (collision->CapsuleWithCapsule(fist->GetcapFront(), fist->GetcapBack(), charatop, charabottom, fist->FistCapsuleRadius, CharacterCapsuleRadius) && attackOnCollision)
	{
		hit = true;
	}

	return hit;
}

/// <summary>
/// 拳と盾の当たり判定
/// </summary>
/// <param name="ShieldLeft">判定対象キャラの盾左</param>
/// <param name="ShieldRight">判定対象キャラの盾右</param>
/// <param name="shieldR">盾半径</param>
/// <returns>当たっているか</returns>
bool CharacterBase::FistWithShield(VECTOR ShieldLeft, VECTOR ShieldRight)
{
	bool hit = false;//盾に当たった

	//当たり判定
	if (collision->CapsuleWithCapsule(fist->GetcapFront(), fist->GetcapBack(), ShieldLeft, ShieldRight, fist->FistCapsuleRadius, shield->ShieldCapsuleRadius) && attackOnCollision)
	{
		hit = true;

		//エフェクト再生
		if (!Playshieldhiteffectflg)
		{
			effect->PlayEffect(Effect::EffectKind::ShieldHit, fist->GetcapFront(), VGet(1.0f, 1.0f, 1.0f), angle, 0.7f);
			Playshieldhiteffectflg = true;
		}
	}

	return hit;
}

/// <summary>
/// 盾どうしの当たり判定
/// </summary>
/// <param name="shieldleft">対象キャラの盾</param>
/// <param name="shieldright">対象キャラの盾</param>
/// <param name="shieldR">盾半径</param>
/// <returns>当たっているか</returns>
bool CharacterBase::ShieldWithShield(VECTOR myshieldleft,VECTOR myshieldright,VECTOR shieldleft, VECTOR shieldright)
{
	bool hit = false;//盾に当たった

	//当たり判定
	if (collision->CapsuleWithCapsule(myshieldleft, myshieldright, shieldleft, shieldright, shield->ShieldCapsuleRadius, shield->ShieldCapsuleRadius))
	{
		hit = true;
	}

	return hit;
}

/// <summary>
/// 盾と盾の当たらない位置までmovevecを戻す/
/// </summary>
/// <param name="shieldleft">対象キャラの盾</param>
/// <param name="shieldright">対象キャラの盾</param>
void CharacterBase::RemoveShield(VECTOR shieldleft, VECTOR shieldright)
{
	//仮盾ポジション
	VECTOR tentativeshieldposition = shield->GetPosition();
	VECTOR tentativeshieldleft;
	VECTOR tentativeshieldright;

	//当たらなくなるまでmoveVecを調整して外す
	while (1)
	{
		moveVec = VSub(moveVec, VGet(1.0f, 0.0f, 1.0f));
		tentativeshieldposition = VAdd(tentativeshieldposition, moveVec);
		tentativeshieldleft = VAdd(tentativeshieldposition, VGet(-sin(angle - 1.5f) * 150, 200, -cos(angle - 1.5f) * 150));
		tentativeshieldright = VAdd(tentativeshieldposition, VGet(sin(angle - 1.5f) * 150, 200, cos(angle - 1.5f) * 150));

		//外れたら終了
		if (!ShieldWithShield(tentativeshieldleft, tentativeshieldright, shieldleft, shieldright) || (moveVec.x <= 0.0f && moveVec.z <= 0.0f))
		{
			break;
		}
	}
}

/// <summary>
/// 脱落になったか
/// </summary>
/// <param name="hit">当たったか</param>
void CharacterBase::CheckOut(bool hit)
{
	//脱落時
	if (!outflg && hit)
	{
		//エフェクト再生
		effect->PlayEffect(Effect::EffectKind::CharacterHit, position, VGet(3.0f, 3.0f, 3.0f), angle, 0.7f);
		Playplayerhiteffectflg = true;

		//se再生
		semanager->PlaySE(SEManager::SEKind::CharahitSE);

		//フラグ変更
 		outflg = true;
	}
}

/// <summary>
/// キャラの吹っ飛び動作
/// </summary>
void CharacterBase::Blow()
{
	if (outflg && position.y < 3000)
	{
		position = VAdd(position, VGet(0, 100, 0));
		//ポジション反映
		MV1SetPosition(model, position);
	}
}

/// <summary>
/// 盾衝突SE再生
/// </summary>
/// <param name="hit">衝突したか</param>
void CharacterBase::PlayShieldHitSE(bool hit)
{
	if (hit && !shieldhitseflg)
	{
		semanager->PlaySE(SEManager::SEKind::ShieldhitSE);
		shieldhitseflg = true;
	}
	if (!hit && shieldhitseflg)
	{
		shieldhitseflg = false;
	}
}

/// <summary>
/// ポジション反映
/// </summary>
void CharacterBase::ReflectPosition()
{
	//ポジションにmoveVecを加算
	position = VAdd(position, moveVec);
	//カプセル更新
	UpdateCapsule();
	//他クラス更新
	OtherClassUpdate();
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

VECTOR CharacterBase::GetShieldPosition()
{
	return shield->GetPosition();
}

VECTOR CharacterBase::GetShieldLeft()
{
	return shield->GetcapLeft();
}

VECTOR CharacterBase::GetShieldRight()
{
	return shield->GetcapRight();
}

void CharacterBase::SetShieldHit(bool hit)
{
	shieldhit = hit;
}

/// <summary>
/// 描画
/// </summary>
void CharacterBase::Draw()
{
	//DrawCapsule3D(capsuleTop, capsuleBottom, CharacterCapsuleRadius, 8, GetColor(127, 255, 0), GetColor(0, 255, 255), FALSE);
	MV1DrawModel(model);
	if (!outflg)
	{
		fist->Draw();
	}
	shield->Draw();
	effect->Draw();
}