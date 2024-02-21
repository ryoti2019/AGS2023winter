#pragma once
#include "GameScene.h"
#include "AsoUtility.h"
#include "Vector2.h"

class Player
{

public:

	// 方向ごとのアニメーション数
	static constexpr int NUM_ANIM = 3;

	// 横のサイズ
	static constexpr int SIZE_X = 48;

	// 縦のサイズ
	static constexpr int SIZE_Y = 48;

	// 移動速度
	static constexpr int SPEED_DEFAULT = 5;

	// アニメーション速度
	static constexpr float ANIM_SPEED_DEFAULT = 0.1f;

	// コンストラクタ
	Player(void);

	// デストラクタ
	~Player(void);

	void Init(GameScene* scene);
	void Update(void);
	void Draw(void);
	void Release(void);

	// 座標取得(ゲッター)
	Vector2 GetPos(void);

	// 座標の設定(セッター)
	void SetPos(Vector2 pos);

	// 移動方向の取得(ゲッター)
	AsoUtility::DIR GetDir(void);

	// ダメージを与える
	void Damage(int damage);

	// HPの取得(ゲッター)
	int GetHP(void);

	// HPMAXの取得
	int GetHPMax(void);

	// 生存判定の取得(ゲッター)
	bool IsAlive(void);

	// 生存判定の設定(セッター)
	void IsSetAlive(bool alive);

	// レベルの取得(ゲッター)
	int GetLevel(void);

	// 経験値
	void Exp(int exp);

private:

	// ゲームシーンのポインタ変数
	GameScene* gameScene_;

	// 画像
	int imgs_[static_cast<int>(AsoUtility::DIR::MAX)][NUM_ANIM];

	// 表示座標
	Vector2 pos_;

	// 移動速度
	int speed_;

	// 移動方向
	AsoUtility::DIR dir_;

	// アニメーションカウンタ
	int cntAnim_;

	// アニメーション速度
	float speedAnim_;

	// アニメーションデータ
	int AnimData_[4];

	// 体力
	int hp_;

	// 体力最大値
	int hpMax_;

	// 生存判定
	bool isAlive_;

	// レベル
	int level_;

	// レベル最大値
	int levelMax_;

	// 経験値
	int exp_;

	// 歩きのSE
	int SEFoot_;

	// プレイヤーのデバッグ描画
	void DrawDebug(void);

	// プレイヤーのステージの衝突
	void StageCollision(void);

	// レベル
	void Level(void);

};


