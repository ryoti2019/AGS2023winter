#include "EnemyBlindedGrimlock.h"

void EnemyBlindedGrimlock::SetParam(void)
{

	// �摜�̃t�@�C����
	imgFileName_ = "BlindedGrimlock.png";

	// �T�C�Y
	size_ = { 32, 32 };

	// �ړ����x
	speed_ = 0.5f;

	// �A�j���[�V�������x
	speedAnim_ = 0.1f;

	hpMax_ = 100;
	hp_ = 40;

	exp_ = 30;
}
