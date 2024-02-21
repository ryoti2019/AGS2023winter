#include "EnemyBlindedGrimlock.h"

void EnemyBlindedGrimlock::SetParam(void)
{

	// 画像のファイル名
	imgFileName_ = "BlindedGrimlock.png";

	// サイズ
	size_ = { 32, 32 };

	// 移動速度
	speed_ = 0.5f;

	// アニメーション速度
	speedAnim_ = 0.1f;

	hpMax_ = 100;
	hp_ = 40;

	exp_ = 30;
}
