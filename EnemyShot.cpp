#include <DxLib.h>
#include "EnemyShot.h"
#include "GameScene.h"
#include "Stage.h"

EnemyShot::EnemyShot(void)
{
}

EnemyShot::~EnemyShot(void)
{
}

void EnemyShot::Init(GameScene* scene)
{

	// �Q�[���V�[���̋@�\�����ł��g����悤�Ƀ����o�ϐ��Ɋi�[
	gameScene_ = scene;

	// �������ꂽ�摜��ǂݍ���
	LoadDivGraph("Image/Enemy/Shot.png",
		E_SHOT_ANIM_NUM,
		E_SHOT_ANIM_NUM,
		1,
		E_SHOT_SIZE_X,
		E_SHOT_SIZE_Y,
		&imgs_[0]
	);

	// �����G�t�F�N�g�ǂݍ���
	LoadDivGraph("Image/Player/Blast.png",
		BLAST_ANIM_NUM,
		4,
		4,
		BLAST_SIZE_X,
		BLAST_SIZE_Y,
		blastImgs_
	);

	// �e�̐�������
	cntAlive_ = 0;

	// �e�̃X�s�[�h
	speed_ = 5.0f;

	// �e�̃A�j���[�V�����p�J�E���^
	cntAnim_ = 0;

	// �e�̃A�j���[�V�������x
	speedAnim_ = 0.2f;

	// �����̃A�j���[�V�������x
	blastSpeedAnim_ = 0.5f;

	// �����A�j���[�V�����p�J�E���^
	blastCntAnim_ = 0;

	// ��Ԃ̏�����
	state_ = STATE::NONE;

	// �{�X�̑Ō�����SE
	SEBossHit_ = LoadSoundMem("Music/�{�X�̑Ō�.mp3");

}

void EnemyShot::Update(void)
{

	// �e�ƃX�e�[�W�̏Փ˔���
	StageCollision();

	switch (state_)
	{

	case EnemyShot::STATE::SHOT:
		UpdateShot();
		break;
	case EnemyShot::STATE::BLAST:
		UpdateBlast();
		break;
	case EnemyShot::STATE::END:
		UpdateEnd();
		break;

	}


}

void EnemyShot::UpdateShot(void)
{

	// �e�̈ړ�
	// �ړ��ʂƂ́A�����~�X�s�[�h(�́A�X�J���[)
	int movePowX = dir_.x * speed_;
	int movePowY = dir_.y * speed_;

	// �ړ��Ƃ́A���W�{�ړ���
	pos_.x += movePowX;
	pos_.y += movePowY;

	// �e�̐����J�E���^����
	// (��U�A�������Ԃ��߂�����AEND��Ԃ֑J��)
	cntAlive_--;
	if (cntAlive_ < 0)
	{
		cntAlive_ = 0;

		// ����������
		Blast(pos_);

		// �{�X�̑Ō���
		PlaySoundMem(SEBossHit_, DX_PLAYTYPE_BACK, true);

	}

	// �e�̃A�j���[�V����
	cntAnim_++;

	// �e�̃A�j���[�V�����ԍ�(0�`1)

	idxAnim_ = static_cast<int>(static_cast<float>(cntAnim_) * speedAnim_) % E_SHOT_ANIM_NUM;

}

void EnemyShot::UpdateBlast(void)
{

	// �����̃A�j���[�V����
	blastCntAnim_++;

	// �����̃A�j���[�V�����ԍ�
	blastIdxAnim_ = static_cast<int>(static_cast<float>(blastCntAnim_) * blastSpeedAnim_) % BLAST_ANIM_NUM;

	// �����̃A�j���[�V�����̏I������
	if (blastIdxAnim_ + 1 >= BLAST_ANIM_NUM)
	{
		ChangeState(STATE::END);
	}

}

void EnemyShot::UpdateEnd(void)
{

	// �e�̏�������
	state_ = STATE::END;

}

void EnemyShot::Draw(void)
{

	switch (state_)
	{

	case EnemyShot::STATE::SHOT:
		DrawShot();
		break;
	case EnemyShot::STATE::BLAST:
		DrawBlast();
		break;
	case EnemyShot::STATE::END:
		DrawEnd();
		break;

	}
}

void EnemyShot::DrawShot(void)
{

	// �J�������W
	Vector2 cameraPos = gameScene_->GetCameraPos();

	// �e�̕`��
	Vector2 pos = pos_.ToVector2();
	DrawGraph(pos.x - E_SHOT_SIZE_X / 2 - cameraPos.x, pos.y - E_SHOT_SIZE_X / 2 - cameraPos.y, imgs_[idxAnim_], true);

}

void EnemyShot::DrawBlast(void)
{

	// �J�������W
	Vector2 cameraPos = gameScene_->GetCameraPos();

	// �e�̕`��
	Vector2 pos = blastPos_.ToVector2();
	DrawGraph(pos.x - BLAST_SIZE_X / 2 - cameraPos.x, pos.y - BLAST_SIZE_X / 2 - cameraPos.y, blastImgs_[blastIdxAnim_], true);

}

void EnemyShot::DrawEnd(void)
{

}

void EnemyShot::Release(void)
{

	// �ǂݍ��񂾉摜�̊J��
	for (int i = 0; i < E_SHOT_ANIM_NUM; i++)
	{
		DeleteGraph(imgs_[i]);
	}

	// �ǂݍ��񂾉摜�̊J��
	for (int i = 0; i < BLAST_ANIM_NUM; i++)
	{
		DeleteGraph(blastImgs_[i]);
	}


}

void EnemyShot::Create(Vector2F pos, Vector2F dir)
{
	// �������Ԃ̐ݒ�
	cntAlive_ = SHOT_CNT_ALIVE;

	// �e�̔��ˈʒu
	pos_ = pos;

	// �e�̕���
	dir_ = dir;

	ChangeState(STATE::SHOT);


}

bool EnemyShot::IsEnableCreate(void)
{
	return state_ == STATE::NONE || state_ == STATE::END;

}

void EnemyShot::Blast(Vector2F pos)
{
	blastPos_ = pos;
	ChangeState(STATE::BLAST);
}

Vector2F EnemyShot::GetPos(void)
{
	return pos_;
}

bool EnemyShot::IsShotState(void)
{
	return state_ == STATE::SHOT;

}

void EnemyShot::ChangeState(STATE state)
{
	// ��Ԃ̍X�V
	state_ = state;

	// ��ԑJ�ڎ��̏�����
	switch (state_)
	{
	case EnemyShot::STATE::SHOT:
		cntAnim_ = 0;
		break;
	case EnemyShot::STATE::BLAST:
		blastCntAnim_ = 0;
		break;
	case EnemyShot::STATE::END:
		break;
	}
}

void EnemyShot::StageCollision(void)
{

	// �e���
	Vector2 shotPos = pos_;

	// �X�e�[�W�̏Փ˔���
	if (gameScene_->IsCollisionStage(shotPos) == true
		|| gameScene_->IsCollisionDoor(shotPos) == true)
	{

		Stage* stage = gameScene_->GetStage();

		Vector2 mapPos1 = gameScene_->World2MapPos(shotPos);

		int chipNo1 = stage->GetDoorNo(mapPos1);

		if ((stage->IsDoor1(chipNo1)) && gameScene_->GetKey1())
		{
			// �ړ��\�Ɣ��f�ł����̂ŁA�����W���X�V
			pos_ = shotPos;
			return;
		}

		if ((stage->IsDoor2(chipNo1)) && gameScene_->GetKey2())
		{
			// �ړ��\�Ɣ��f�ł����̂ŁA�����W���X�V
			pos_ = shotPos;
			return;
		}

		if ((stage->IsDoor3(chipNo1)) && gameScene_->GetKey3())
		{
			// �ړ��\�Ɣ��f�ł����̂ŁA�����W���X�V
			pos_ = shotPos;
			return;
		}

		if ((stage->IsDoor4(chipNo1)) && gameScene_->GetKey4())
		{
			// �ړ��\�Ɣ��f�ł����̂ŁA�����W���X�V
			pos_ = shotPos;
			return;
		}

		// �Փ˂��Ă��� -> ���W�����ɖ߂�
		shotPos = pos_;

		// �Փ˂�����e�̐������Ԃ��[���ɂ���
		cntAlive_ = 0.0f;

	}
	else
	{
		// �ړ��\�Ɣ��f�ł����̂ŁA�����W���X�V
		pos_ = shotPos;
	}


}
