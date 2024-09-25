#pragma once

class CharacterBase
{
protected:
	const float Speed = 10.0f;//速さ

	//アニメーションの種類
	enum class AnimKind : int
	{
		None = -1,//無し
		Run = 0,//走り
		Punch = 1,//パンチ
	};

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
	float angle;//現在のプレイヤー角度

	//攻撃
	bool attackflg;

	//角度更新
	void UpdateAngle();
	//アニメーション切り替え
	void ChangeAnimation(AnimKind nextkind);
	//アニメーション再生
	void PlayAnimation();
	//攻撃処理
	void Attack();

public:
	//描画
	void Draw();
};