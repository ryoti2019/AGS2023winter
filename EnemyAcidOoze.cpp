#include "EnemyAcidOoze.h"

void EnemyAcidOoze::SetParam(void)
{

	// �摜�̃t�@�C����
	imgFileName_ = "AcidOoze.png";

	// �T�C�Y
	size_ = { 24, 24 };

	// �ړ����x
	speed_ = 1.0f;

	// �A�j���[�V�������x
	speedAnim_ = 0.1f;

	hpMax_ = 100;
	hp_ = 20;

	exp_ = 20;

}
