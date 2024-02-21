#pragma once
#include <string>
#include "Vector2.h"
#include "Vector2F.h"
#include "AsoUtility.h"
class GameScene;

class EnemyBase
{
public:

	// 方向ごとのアニメーション数
	static constexpr int NUM_ANIM = 4;

	// 敵の種類
	enum class TYPE
	{
		AcidOoze,
		BlindedGrimlock,
		BloodshotEye,
		MAX
	};

	// コンストラクタ
	EnemyBase(void);

	// デストラクタ
	virtual ~EnemyBase(void);

	virtual void Init(GameScene* scene);

	// パラメータ設定
	virtual void SetParam(void) = 0;

	virtual void Update(void);
	virtual void Draw(void);
	virtual void Release(void);

	// 座標取得(ゲッター)
	Vector2F GetPos(void);

	// 座標の設定(セッター)
	void SetPos(Vector2F pos);

	// 生存判定の取得(ゲッター)
	bool IsGetAlive(void);

	// 生存判定の取得(セッター)
	void IsSetAlive(bool alive);

	// 画像サイズの取得
	Vector2 GetSize(void);

	// ダメージを与える
	void Damage(int damage);

	// 経験値
	int GetExp(void);

	// 足元座標
	int GetFootPosY(void);

protected:

	// ゲームシーンのポインタ変数
	GameScene* gameScene_;

	// 画像のファイル名
	std::string imgFileName_;

	// 画像[向き][アニメーション]
	int imgs_[static_cast<int>(AsoUtility::DIR::MAX)][NUM_ANIM];

	// 表示座標
	Vector2F pos_;

	// 画像のサイズ
	Vector2 size_;

	// 移動速度
	float speed_;

	// 移動方向
	AsoUtility::DIR dir_;

	// アニメーションカウンタ
	int cntAnim_;

	// アニメーション速度
	float speedAnim_;

	// 体力
	int hp_;

	// 体力の最大値
	int hpMax_;

	// 生存判定
	bool isAlive_;

	// 経験値
	int exp_;

	// 敵のステージの衝突
	void StageCollision(void);

	// 敵のステージの衝突判定
	bool IsStageCollision(Vector2F movedPos);

	// 敵の動き
	Vector2F Move(Vector2F dir);
};

