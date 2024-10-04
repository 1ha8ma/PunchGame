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
	//カプセルの更新
	void UpdateCapsule();
	//攻撃処理
	void Attack();


public:
	//当たり判定
	bool FistWithCharacter(VECTOR charatop, VECTOR charabottom,float charaR,bool charaout);
	bool FistWithShield(VECTOR Shieldleft, VECTOR Shieldright, float shieldR);
	//コンストラクタ
	CharacterBase();
	//他クラスの更新
	void OtherClassUpdate(bool shieldhit);
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
	bool GetAttackflg(){ return attackflg; }
};