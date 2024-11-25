#pragma once

//他クラス
class Shield;
class Fist;
class SEManager;
class Effect;
class Collision;

class CharacterBase
{
public:	
	//コンストラクタ
	CharacterBase();
	//デストラクタ
	~CharacterBase();
	//盾衝突se再生
	void PlayShieldHitSE(bool hit);
	//アウト確認
	void CheckOut(bool hit);
	//ポジション反映
	void ReflectPosition();
	//終了後も更新
	void ForeverUpdate(bool settlement);
	//描画
	void Draw();

	//攻撃に当たり判定を付けるか判断
	void CheckAttackOnCollision();
	//当たり判定
	bool FistWithCharacter(VECTOR charatop, VECTOR charabottom, bool charaout);
	bool FistWithShield(VECTOR Shieldleft, VECTOR Shieldright);
	bool ShieldWithShield(VECTOR myshieldleft, VECTOR myshieldright, VECTOR shieldleft, VECTOR shieldright);
	void RemoveShield(VECTOR shieldleft, VECTOR shieldright);

	//Get・Set
	VECTOR GetPositioncapsuleTop() { return capsuleTop; }
	VECTOR GetPositioncapsuleBotoom() { return capsuleBottom; }
	VECTOR GetShieldPosition();
	VECTOR GetShieldLeft();
	VECTOR GetShieldRight();
	void SetShieldHit(bool hit);
	bool GetShieldHit() { return shieldhit; }
	bool GetOutflg() { return outflg; }
	float GetAngle() { return angle; }

protected:
	const float Speed = 10.0f;//速さ
	const float CharacterCapsuleRadius = 120.0f;

	//アニメーションの種類
	enum class AnimKind : int
	{
		None = -1,//無し
		Run = 0,//走り
		Punch = 1,//パンチ
	};

	//他クラス
	Shield* shield;
	Fist* fist;
	SEManager* semanager;
	Effect* effect;
	Collision* collision;

	//初期化
	void BaseInitialize();
	//角度初期化
	void InitializeAngle();
	//カプセルの更新
	void UpdateCapsule();
	//他クラスの更新
	void OtherClassUpdate(bool Settlement);
	//エフェクト更新
	void UpdateEffect();
	//吹っ飛ぶ
	void Blow(bool Settlement);

	//モデル・アニメーション
	int model;//モデル
	int animtotaltime;//総アニメーション時間
	float animplaytime;//現在のアニメーション再生時間
	bool isanimflg;//アニメーションを再生するか
	int nowPlayAnimKind;//現在再生中のアニメーション
	int nowPlayAnim;//現在のアニメーションアタッチ番号
	int prevPlayAnim;//変更前のアニメーション

	//エフェクト
	bool Playplayerhiteffectflg;//プレイヤー衝突エフェクト再生フラグ
	bool Playshieldhiteffectflg;//盾衝突エフェクトフラグ

	//ポジション
	VECTOR position;//ポジション
	VECTOR moveVec;//入力があってからの動く方向
	VECTOR targetLookDirection;//モデルが向くべき方向のベクトル
	float angle;//現在のキャラクター角度
	VECTOR capsuleTop;//カプセル上
	VECTOR capsuleBottom;//カプセル下

	//攻撃
	bool attackflg;//攻撃中フラグ
	bool attackOnCollision;//攻撃に当たり判定を付けるフラグ

	bool outflg;//脱落
	bool shieldhit;//攻撃が盾に当たった
	bool shieldhitseflg;//盾衝突seフラグ

	//角度更新
	void UpdateAngle();
	//アニメーション切り替え
	void ChangeAnimation(AnimKind nextkind);
	//アニメーション再生
	void PlayAnimation();
	//他クラスの初期化
	void OtherClassInitialize();
	//攻撃処理
	void Attack();
};