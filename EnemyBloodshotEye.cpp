#include "EnemyBloodshotEye.h"

void EnemyBloodshotEye::SetParam(void)
{

	// 画像のファイル名
	imgFileName_ = "BloodshotEye.png";

	// サイズ
	size_ = { 24, 24 };

	// 移動速度
	speed_ = 2.0f;

	// アニメーション速度
	speedAnim_ = 0.2f;

	hpMax_ = 100;
	hp_ = 10;

	exp_ = 10 ;
}
