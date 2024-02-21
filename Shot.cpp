#include <DxLib.h>
#include "Shot.h"
#include "GameScene.h"
#include "Player.h"
#include "Stage.h"

Shot::Shot(void)
{
}

Shot::~Shot(void)
{
}

void Shot::Init(GameScene* scene)
{

	// �Q�[���V�[���̋@�\�����ł��g����悤�Ƀ����o�ϐ��Ɋi�[
	gameScene_ = scene;

	// �������ꂽ�摜��ǂݍ���
	LoadDivGraph("Image/Player/arrow.png",
		SHOT_NUM,
		SHOT_NUM_X,
		SHOT_NUM_Y,
		SHOT_SIZE_X,
		SHOT_SIZE_Y,
		&imgs_[0]
	);

	// �������ꂽ�摜��ǂݍ���
	LoadDivGraph("Image/Player/arrow2.png",
		SHOT_NUM,
		SHOT_NUM_X,
		SHOT_NUM_Y,
		SHOT_SIZE_X,
		SHOT_SIZE_Y,
		&imgs2_[0]
	);

	// �������ꂽ�摜��ǂݍ���
	LoadDivGraph("Image/Player/arrow3.png",
		SHOT_NUM,
		SHOT_NUM_X,
		SHOT_NUM_Y,
		SHOT_SIZE_X,
		SHOT_SIZE_Y,
		&imgs3_[0]
	);

	// �������ꂽ�摜��ǂݍ���
	LoadDivGraph("Image/Player/arrow4.png",
		SHOT_NUM,
		SHOT_NUM_X,
		SHOT_NUM_Y,
		SHOT_SIZE_X,
		SHOT_SIZE_Y,
		&imgs4_[0]
	);

	// �������ꂽ�摜��ǂݍ���
	LoadDivGraph("Image/Player/arrow5.png",
		SHOT_NUM,
		SHOT_NUM_X,
		SHOT_NUM_Y,
		SHOT_SIZE_X,
		SHOT_SIZE_Y,
		&imgs5_[0]
	);

	// �����G�t�F�N�g�ǂݍ���
	LoadDivGraph("Image/Player/Blast1.png",
		BLAST_ANIM_NUM,
		4,
		1,
		BLAST_SIZE_X,
		BLAST_SIZE_Y,
		blastImgs_
	);

	// �����G�t�F�N�g�ǂݍ���
	LoadDivGraph("Image/Player/Blast2.png",
		BLAST_ANIM_NUM,
		4,
		1,
		BLAST2_SIZE_X,
		BLAST2_SIZE_Y,
		blastImgs2_
	);

	// �����G�t�F�N�g�ǂݍ���
	LoadDivGraph("Image/Player/Blast3.png",
		BLAST_ANIM_NUM,
		4,
		1,
		BLAST3_SIZE_X,
		BLAST3_SIZE_Y,
		blastImgs3_
	);

	// �����G�t�F�N�g�ǂݍ���
	LoadDivGraph("Image/Player/Blast4.png",
		BLAST_ANIM_NUM,
		4,
		1,
		BLAST4_SIZE_X,
		BLAST4_SIZE_Y,
		blastImgs4_
	);

	// �����G�t�F�N�g�ǂݍ���
	LoadDivGraph("Image/Player/Blast5.png",
		BLAST_ANIM_NUM,
		4,
		1,
		BLAST5_SIZE_X,
		BLAST5_SIZE_Y,
		blastImgs5_
	);

	// �e�̐�������
	cntAlive_ = 0;

	// �e�̃X�s�[�h
	speed_ = 10.0f;

	// �����̃A�j���[�V�������x
	blastSpeedAnim_ = 0.2f;

	// �����A�j���[�V�����p�J�E���^
	blastCntAnim_ = 0;

	// ��Ԃ̏�����
	state_ = STATE::NONE;

	// �Ō���1��SE
	SE1Hit_ = LoadSoundMem("Music/�Ō����x��1.mp3");

	// �Ō���2��SE
	SE2Hit_ = LoadSoundMem("Music/�Ō����x��2.mp3");

	// �Ō���3��SE
	SE3Hit_ = LoadSoundMem("Music/�Ō����x��3.mp3");

	// �Ō���4��SE
	SE4Hit_ = LoadSoundMem("Music/�Ō����x��4.mp3");

	// �Ō���5��SE
	SE5Hit_ = LoadSoundMem("Music/�Ō����x��5.mp3");

}

void Shot::Update(void)
{

	// �e�ƃX�e�[�W�̏Փ˔���
	StageCollision();

	switch (state_)
	{

	case Shot::STATE::SHOT:
		UpdateShot();
		break;
	case Shot::STATE::BLAST:
		UpdateBlast();
		break;
	case Shot::STATE::END:
		UpdateEnd();
		break;

	}


}

void Shot::UpdateShot(void)
{

	// �e�̈ړ�
	// �ړ��ʂƂ́A�����~�X�s�[�h(�́A�X�J���[)
	int movePowX = dir_.x * speed_;
	int movePowY = dir_.y * speed_;

	// �ړ��Ƃ́A���W�{�ړ���
	pos_.x += movePowX;
	pos_.y += movePowY;

	// ���x��
	Player* player = gameScene_->GetPlayer();

	int level = player->GetLevel();

	// �e�̐����J�E���^����
	// (��U�A�������Ԃ��߂�����AEND��Ԃ֑J��)
	cntAlive_--;
	if (cntAlive_ < 0)
	{
		cntAlive_ = 0;

		// ����������
		Blast(pos_);

		if (level == 1)
		{
			// �Ō���
			PlaySoundMem(SE1Hit_, DX_PLAYTYPE_BACK, true);
		}

		if (level == 2)
		{
			// �Ō���
			PlaySoundMem(SE2Hit_, DX_PLAYTYPE_BACK, true);
		}

		if (level == 3)
		{
			// �Ō���
			PlaySoundMem(SE3Hit_, DX_PLAYTYPE_BACK, true);
		}

		if (level == 4)
		{
			// �Ō���
			PlaySoundMem(SE4Hit_, DX_PLAYTYPE_BACK, true);
		}

		if (level == 5)
		{
			// �Ō���
			PlaySoundMem(SE5Hit_, DX_PLAYTYPE_BACK, true);
		}
	}

}

void Shot::UpdateBlast(void)
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

void Shot::UpdateEnd(void)
{

	// �e�̏�������
	state_ = STATE::END;

}

void Shot::Draw(void)
{

	switch (state_)
	{

	case Shot::STATE::SHOT:
		DrawShot();
		break;
	case Shot::STATE::BLAST:
		DrawBlast();
		break;
	case Shot::STATE::END:
		DrawEnd();
		break;

	}

}

void Shot::DrawShot(void)
{

	// �J�������W
	Vector2 cameraPos = gameScene_->GetCameraPos();

	// �v���C���[�̎擾
	Player* player = gameScene_->GetPlayer();

	// ���x���̎擾
	int level = player->GetLevel();

	// ��̍��W
	Vector2 pos = pos_.ToVector2();

	// ��̕`��
	if (level == 1)
	{
		DrawGraph(pos.x - SHOT_SIZE_X / 2 - cameraPos.x, pos.y - SHOT_SIZE_Y / 2 - cameraPos.y,imgs_[static_cast<int>(shotDir_)], true);
	}

	if (level == 2)
	{
		DrawGraph(pos.x - SHOT_SIZE_X / 2 - cameraPos.x, pos.y - SHOT_SIZE_Y / 2 - cameraPos.y, imgs2_[static_cast<int>(shotDir_)], true);
	}

	if (level == 3)
	{
		DrawGraph(pos.x - SHOT_SIZE_X / 2 - cameraPos.x, pos.y - SHOT_SIZE_Y / 2 - cameraPos.y, imgs3_[static_cast<int>(shotDir_)], true);
	}

	if (level == 4)
	{
		DrawGraph(pos.x - SHOT_SIZE_X / 2 - cameraPos.x, pos.y - SHOT_SIZE_Y / 2 - cameraPos.y, imgs4_[static_cast<int>(shotDir_)], true);
	}

	if (level == 5)
	{
		DrawGraph(pos.x - SHOT_SIZE_X / 2 - cameraPos.x, pos.y - SHOT_SIZE_Y / 2 - cameraPos.y, imgs5_[static_cast<int>(shotDir_)], true);
	}

}

void Shot::DrawBlast(void)
{

	// �J�������W
	Vector2 cameraPos = gameScene_->GetCameraPos();

	// �v���C���[�̎擾
	Player* player = gameScene_->GetPlayer();

	// ���x���̎擾
	int level = player->GetLevel();

	// �G�t�F�N�g�̍��W
	Vector2 pos = blastPos_.ToVector2();

	// �G�t�F�N�g�̕`��
	if (level == 1)
	{
		DrawGraph(pos.x - BLAST_SIZE_X / 2 - cameraPos.x, pos.y - BLAST_SIZE_X / 2 - cameraPos.y, blastImgs_[blastIdxAnim_], true);
	}
	
	if (level == 2)
	{
		DrawGraph(pos.x - BLAST2_SIZE_X / 2 - cameraPos.x, pos.y - BLAST2_SIZE_X / 2 - cameraPos.y, blastImgs2_[blastIdxAnim_], true);
	}

	if (level == 3)
	{
		DrawGraph(pos.x - BLAST3_SIZE_X / 2 - cameraPos.x, pos.y - BLAST3_SIZE_X / 2 - cameraPos.y, blastImgs3_[blastIdxAnim_], true);
	}

	if (level == 4)
	{
		DrawGraph(pos.x - BLAST4_SIZE_X / 2 - cameraPos.x, pos.y - BLAST4_SIZE_X / 2 - cameraPos.y, blastImgs4_[blastIdxAnim_], true);
	}

	if (level == 5)
	{
		DrawGraph(pos.x - BLAST5_SIZE_X / 2 - cameraPos.x, pos.y - BLAST5_SIZE_X / 2 - cameraPos.y, blastImgs5_[blastIdxAnim_], true);
	}
}

void Shot::DrawEnd(void)
{
}

void Shot::Release(void)
{

	// �ǂݍ��񂾉摜�̊J��
	for (int i = 0; i < SHOT_NUM; i++)
	{
		DeleteGraph(imgs_[i]);
	}

	// �ǂݍ��񂾉摜�̊J��
	for (int i = 0; i < SHOT_NUM; i++)
	{
		DeleteGraph(imgs2_[i]);
	}

	// �ǂݍ��񂾉摜�̊J��
	for (int i = 0; i < BLAST_ANIM_NUM; i++)
	{
		DeleteGraph(blastImgs_[i]);
	}

}

void Shot::Create(Vector2F pos, AsoUtility::DIR dir)
{

	// �������Ԃ̐ݒ�
	cntAlive_ = SHOT_CNT_ALIVE;

	// �e�̔��ˈʒu
	pos_ = pos;

	shotDir_ = dir;


	// �ړ�
	switch (dir)
	{
	case AsoUtility::DIR::UP:
		dir_.x = 0.0f;
		dir_.y = -1.0f;
		break;
	case AsoUtility::DIR::RIGHT:
		dir_.x = 1.0f;
		dir_.y = 0.0f;
		break;
	case AsoUtility::DIR::DOWN:
		dir_.x = 0.0f;
		dir_.y = 1.0f;
		break;
	case AsoUtility::DIR::LEFT:
		dir_.x = -1.0f;
		dir_.y = 0.0f;
		break;
	}

	ChangeState(STATE::SHOT);

}

bool Shot::IsEnableCreate(void)
{
	return state_ == STATE::NONE || state_ == STATE::END;
}

void Shot::Blast(Vector2F pos)
{

	blastPos_ = pos;
	ChangeState(STATE::BLAST);

}

Vector2F Shot::GetPos(void)
{
	return pos_;
}

bool Shot::IsShotState(void)
{
	return state_ == STATE::SHOT;
}

bool Shot::IsAlive(void)
{
	return cntAlive_;
}

void Shot::SetAlive(float time)
{
	cntAlive_ = time;
}

void Shot::ChangeState(STATE state)
{

	// ��Ԃ̍X�V
	state_ = state;

	// ��ԑJ�ڎ��̏�����
	switch (state_)
	{
	case Shot::STATE::BLAST:
		blastCntAnim_ = 0;
		break;
	case Shot::STATE::END:
		break;
	}

}

void Shot::StageCollision(void)
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

		if ((stage->IsDoor1(chipNo1))&& gameScene_->GetKey1())
		{
			// �ړ��\�Ɣ��f�ł����̂ŁA�����W���X�V
			pos_ = shotPos;
			return;
		}

		if ((stage->IsDoor2(chipNo1))&& gameScene_->GetKey2())
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
