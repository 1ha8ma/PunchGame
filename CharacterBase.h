#pragma once

//他クラス
class Shield;
class Fist;

class CharacterBase
{
protected:
	const float Speed = 10.0f;//速さ
	const float CharacterR = 120.0f;

	//アニメーションの種類
	enum class AnimKind : int
	{
		None = -1,//無し
		Run = 0,//走り
		Punch = 1,//パンチ
	};

	enum class EffectKind :int
	{
		None = -1,//無し
		HitPlayer = 0,//プレイヤー衝突
		HitShield = 1,//盾衝突
	};

	

	//他クラス
	Shield* shield;
	Fist* fist;

	//モデル・アニメーション
	int model;//モデル
	int animtotaltime;//総アニメーション時間
	float animplaytime;//現在のアニメーション再生時間
	bool isanimflg;//アニメーションを再生するか
	int nowPlayAnimKind;//現在再生中のアニメーション
	int nowPlayAnim;//現在のアニメーションアタッチ番号
	int prevPlayAnim;//変更前のアニメーション

	//エフェクト
	int PlayingEffectKind;//再生中のエフェクトの種類
	int PlayingEffecthandle;//再生中のエフェクト
	int PlayingEffectSpeed;//再生中のエフェクト再生速度
	int playerhiteffecthandle;//プレイヤー衝突エフェクトハンドル
	bool Playplayerhiteffectflg;//プレイヤー衝突エフェクト再生フラグ
	VECTOR playerhiteffectangle;//プレイヤー衝突エフェクト角度
	VECTOR playerhiteffectposition;//プレイヤー衝突エフェクトポジション
	int shieldhiteffecthandle;//盾衝突エフェクトハンドル
	bool Playshieldhiteffectflg;//盾衝突エフェクトフラグ
	VECTOR shieldhiteffectangle;//盾衝突エフェクト角度
	VECTOR shieldhiteffectposition;//盾衝突エフェクトポジション


	//ポジション
	VECTOR position;//ポジション
	VECTOR moveVec;//入力があってからの動く方向
	VECTOR targetLookDirection;//モデルが向くべき方向のベクトル
	float angle;//現在のキャラクター角度
	VECTOR capsuleTop;
	VECTOR capsuleBottom;

	//攻撃
	bool attackflg;//攻撃開始フラグ
	
	bool outflg;//脱落
	bool shieldhit;//攻撃が盾に当たった


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


public:
	//当たり判定
	bool FistWithCharacter(VECTOR charatop, VECTOR charabottom,float charaR,bool charaout);
	bool FistWithShield(VECTOR Shieldleft, VECTOR Shieldright, float shieldR);
	//コンストラクタ
	CharacterBase();
	//初期化
	void BaseInitialize();
	//カプセルの更新
	void UpdateCapsule();
	//他クラスの更新
	void OtherClassUpdate(bool shieldhit);
	//エフェクト更新
	void UpdateEffect();
	//吹っ飛ぶ
	void Blow();
	//アウト確認
	void CheckOut(bool hit);
	//描画
	void Draw();

	VECTOR GetPositioncapsuleTop() { return capsuleTop; }
	VECTOR GetPositioncapsuleBotoom() { return capsuleBottom; }
	VECTOR GetShieldLeft();
	VECTOR GetShieldRight();
	bool GetOutflg() { return outflg; }
};