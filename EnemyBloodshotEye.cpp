#include "EnemyBloodshotEye.h"

void EnemyBloodshotEye::SetParam(void)
{

	// �摜�̃t�@�C����
	imgFileName_ = "BloodshotEye.png";

	// �T�C�Y
	size_ = { 24, 24 };

	// �ړ����x
	speed_ = 2.0f;

	// �A�j���[�V�������x
	speedAnim_ = 0.2f;

	hpMax_ = 100;
	hp_ = 10;

	exp_ = 10 ;
}
