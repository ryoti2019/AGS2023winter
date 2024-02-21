#include "EnemyAcidOoze.h"

void EnemyAcidOoze::SetParam(void)
{

	// 画像のファイル名
	imgFileName_ = "AcidOoze.png";

	// サイズ
	size_ = { 24, 24 };

	// 移動速度
	speed_ = 1.0f;

	// アニメーション速度
	speedAnim_ = 0.1f;

	hpMax_ = 100;
	hp_ = 20;

	exp_ = 20;

}
