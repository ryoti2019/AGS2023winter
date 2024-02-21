#include <DxLib.h>
#include "Player.h"
#include "InputManager.h"
#include "Application.h"
#include "Stage.h"

Player::Player(void)
{
}

Player::~Player(void)
{
}

void Player::Init(GameScene* scene)
{

	// �Q�[���V�[���̋@�\�����ł��g����悤�Ƀ����o�ϐ��Ɋi�[
	gameScene_ = scene;

	int dirNum = static_cast<int>(AsoUtility::DIR::MAX);
	int allNum = NUM_ANIM * dirNum;
	// �������ꂽ�摜��ǂݍ���
	LoadDivGraph("Image/Player/Player.png",
		allNum,
		NUM_ANIM,
		dirNum,
		SIZE_X,
		SIZE_Y,
		&imgs_[0][0]
	);

	// ���W�̏�����
	pos_.x = Application::SCREEN_SIZE_X / 2;
	pos_.y = Application::SCREEN_SIZE_Y / 2;

	// �ړ����x
	speed_ = SPEED_DEFAULT;

	// ����
	dir_ = AsoUtility::DIR::DOWN;

	// �A�j���[�V�����J�E���^
	cntAnim_ = 0;

	// �A�j���[�V�������x
	speedAnim_ = ANIM_SPEED_DEFAULT;

	// HP
	hpMax_ = 500;
	hp_ = hpMax_;

	// ��������
	isAlive_ = true;

	// ���x��
	level_ = 1;

}

void Player::Update(void)
{
	auto& ins = InputManager::GetInstance();
	auto pad = InputManager::JOYPAD_NO::PAD1;

	// �v���C���[�̏Փ�
	StageCollision();

	// ���x��
	Level();

	//int i = 0;
	//if (gameScene_->IsCollisionGate(pos_))
	//{
	//	i = 1;
	//}

}

void Player::Draw(void)
{


	if (!isAlive_)
	{
		// �������Ă��Ȃ���Ε`�悵�Ȃ�
		return;
	}

	// �ŐV�Q�[���V�[������A�J�����̈ʒu���擾
	Vector2 cameraPos = gameScene_->GetCameraPos();

	// �A�j���[�V�����̃`�b�v�ԍ�(0�`2)�����
	AnimData_[0] = 0;
	AnimData_[1] = 1;
	AnimData_[2] = 2;
	AnimData_[3] = 1;

	// �v���C���[�̕`��
	DrawGraph(pos_.x - SIZE_X / 2 - cameraPos.x, pos_.y - SIZE_Y / 2 - cameraPos.y, imgs_[static_cast<int>(dir_)][AnimData_[(cntAnim_ / 10) % 4]], true);
	
	//DrawFormatString(0, 0, 0xffffff, "exp = %d", exp_);
	//DrawFormatString(0, 15, 0xffffff, "level = %d", level_);
	DrawDebug();

}

void Player::Release(void)
{

	int dirNum = static_cast<int>(AsoUtility::DIR::MAX);

	// �ǂݍ��񂾉摜�̊J��
	for (int y = 0; y < dirNum; y++)
	{
		for (int x = 0; x < NUM_ANIM; x++)
		{
			DeleteGraph(imgs_[y][x]);
		}
	}

}

Vector2 Player::GetPos(void)
{
	return pos_;
}

void Player::SetPos(Vector2 pos)
{
	pos_ = pos;
}

AsoUtility::DIR Player::GetDir(void)
{
	return dir_;
}

void Player::Damage(int damage)
{

	// HP�����炷 �_���[�W�ʕ�
	hp_ -= damage;

	//HP���O�ȉ��ɂȂ�����v���C���[�𐶑����Ă��Ȃ����Ƃɂ���
	if (hp_ <= 0)
	{
		hp_ = 0;
		isAlive_ = false;
	}

}

int Player::GetHP(void)
{
	return hp_;
}

int Player::GetHPMax(void)
{
	return hpMax_;
}

bool Player::IsAlive(void)
{
	return isAlive_;
}

void Player::IsSetAlive(bool alive)
{
	isAlive_ = alive;
}

int Player::GetLevel(void)
{
	return level_;
}

void Player::DrawDebug(void)
{

	//// �ŐV�Q�[���V�[������A�J�����̈ʒu���擾
	//Vector2 cameraPos = gameScene_->GetCameraPos();

	//// �f�o�b�O�p
	//DrawBox(pos_.x - 3 - cameraPos.x,
	//	pos_.y - 3 - cameraPos.y,
	//	pos_.x + 3 - cameraPos.x,
	//	pos_.y + 3 - cameraPos.y,
	//	0xff0000, true);

	//// �I�����W
	//int color = 0xff8c00;

	//// �f�o�b�O�p�F�����Փ˔���
	//Vector2 footPos = pos_;
	//footPos.y += 20;

	//// �f�o�b�O�p�F�������Փ˔���
	//Vector2 leftFootPos = pos_;
	//leftFootPos.x -= 10;
	//leftFootPos.y += 20;

	//// �f�o�b�O�p�F�����E�Փ˔���
	//Vector2 rightFootPos = pos_;
	//rightFootPos.x += 10;
	//rightFootPos.y += 20;

	//// �����F����
	//DrawBox(footPos.x - 3 - cameraPos.x, footPos.y - 3 - cameraPos.y, 
	//	footPos.x + 3 - cameraPos.x, footPos.y + 3 - cameraPos.y, color, true);

	//// �����F��
	//DrawBox(leftFootPos.x - 3 - cameraPos.x, leftFootPos.y - 3 - cameraPos.y,
	//	leftFootPos.x + 3 - cameraPos.x, leftFootPos.y + 3 - cameraPos.y, color, true);

	//// �����F�E
	//DrawBox(rightFootPos.x - 3 - cameraPos.x, rightFootPos.y - 3 - cameraPos.y,
	//	rightFootPos.x + 3 - cameraPos.x, rightFootPos.y + 3 - cameraPos.y, color, true);

}

void Player::StageCollision(void)
{
	// �ړ��O���W���m��
	Vector2 prePos = pos_;

	// �ړ��\��̍��W���m��
	Vector2 movedPos = pos_;

	// �����Փ˔���
	Vector2 footPos;

	// �����E�Փ˔���
	Vector2 rightFootPos;

	// �����E�Փ˔���
	Vector2 leftFootPos;

	auto& ins = InputManager::GetInstance();
	auto inputState = ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1);

	// �ړ�����(Y)
	if (ins.IsNew(KEY_INPUT_UP) || inputState.AKeyLY < 0.0f)
	{
		// ��ړ�
		movedPos.y -= speed_;

		// �����̕ύX
		dir_ = AsoUtility::DIR::UP;

		// �A�j���[�V�����J�E���^�̐i�s
		cntAnim_++;
	}

	if (ins.IsNew(KEY_INPUT_DOWN) || inputState.AKeyLY > 0.0f)
	{
		// ���ړ�
		movedPos.y += speed_;

		// �����̕ύX
		dir_ = AsoUtility::DIR::DOWN;

		// �A�j���[�V�����J�E���^�̐i�s
		cntAnim_++;
	}

	// �Փ˔���(Y)
	footPos = movedPos;
	footPos.y += 20;

	leftFootPos = movedPos;
	leftFootPos.x -= 10;
	leftFootPos.y += 20;

	rightFootPos = movedPos;
	rightFootPos.x += 10;
	rightFootPos.y += 20;

	// �X�e�[�W�̏Փ˔���
	if (gameScene_->IsCollisionStage(movedPos) == true
		|| gameScene_->IsCollisionStage(footPos) == true
		|| gameScene_->IsCollisionStage(rightFootPos) == true
		|| gameScene_->IsCollisionStage(leftFootPos) == true
		|| gameScene_->IsCollisionDoor(movedPos) == true
		|| gameScene_->IsCollisionDoor(footPos) == true
		|| gameScene_->IsCollisionDoor(rightFootPos) == true
		|| gameScene_->IsCollisionDoor(leftFootPos) == true
		|| gameScene_->IsCollisionGate(movedPos) == true
		|| gameScene_->IsCollisionGate(footPos) == true
		|| gameScene_->IsCollisionGate(rightFootPos) == true
		|| gameScene_->IsCollisionGate(leftFootPos) == true)
	{

		Stage* stage = gameScene_->GetStage();

		Vector2 mapPos1 = gameScene_->World2MapPos(movedPos);
		Vector2 mapPos2 = gameScene_->World2MapPos(footPos);
		Vector2 mapPos3 = gameScene_->World2MapPos(rightFootPos);
		Vector2 mapPos4 = gameScene_->World2MapPos(leftFootPos);

		int chipNo1 = stage->GetDoorNo(mapPos1);
		int chipNo2 = stage->GetDoorNo(mapPos2);
		int chipNo3 = stage->GetDoorNo(mapPos3);
		int chipNo4 = stage->GetDoorNo(mapPos4);
		int chipNo5 = stage->GetGateNo(mapPos1);
		int chipNo6 = stage->GetGateNo(mapPos2);
		int chipNo7 = stage->GetGateNo(mapPos3);
		int chipNo8 = stage->GetGateNo(mapPos4);

		if (
			(
				stage->IsDoor1(chipNo1) || stage->IsDoor1(chipNo2) || stage->IsDoor1(chipNo3) || stage->IsDoor1(chipNo4)
				)
			&& gameScene_->GetKey1())
		{
			// �ړ��\�Ɣ��f�ł����̂ŁA�����W���X�V
			pos_ = movedPos;
			//return;
		}

		if (
			(
				stage->IsDoor2(chipNo1) || stage->IsDoor2(chipNo2) || stage->IsDoor2(chipNo3) || stage->IsDoor2(chipNo4)
				)
			&& gameScene_->GetKey2())
		{
			// �ړ��\�Ɣ��f�ł����̂ŁA�����W���X�V
			pos_ = movedPos;
			//return;
		}

		if (
			(
				stage->IsDoor3(chipNo1) || stage->IsDoor3(chipNo2) || stage->IsDoor3(chipNo3) || stage->IsDoor3(chipNo4)
				)
			&& gameScene_->GetKey3())
		{
			// �ړ��\�Ɣ��f�ł����̂ŁA�����W���X�V
			pos_ = movedPos;
			//return;
		}

		if (
			(
				stage->IsDoor4(chipNo1) || stage->IsDoor4(chipNo2) || stage->IsDoor4(chipNo3) || stage->IsDoor4(chipNo4)
				)
			&& gameScene_->GetKey4())
		{
			// �ړ��\�Ɣ��f�ł����̂ŁA�����W���X�V
			pos_ = movedPos;
			//return;
		}

		if (stage->IsGate(chipNo5) || stage->IsGate(chipNo6) || stage->IsGate(chipNo7) || stage->IsGate(chipNo8))
		{
			// �ړ��\�Ɣ��f�ł����̂ŁA�����W���X�V
			pos_ = movedPos;
			//return;
		}

		// �Փ˂��Ă��� -> ���W�����ɖ߂�
		movedPos = pos_;
		//return;
	}

	else
	{
		// �ړ��\�Ɣ��f�ł����̂ŁA�����W���X�V
		pos_ = movedPos;
	}


	// �ړ�����(X)
	if (ins.IsNew(KEY_INPUT_LEFT) || inputState.AKeyLX < 0.0f)
	{
		// ���ړ�
		movedPos.x -= speed_;

		// �����̕ύX
		dir_ = AsoUtility::DIR::LEFT;

		// �A�j���[�V�����J�E���^�̐i�s
		cntAnim_++;
	}

	if (ins.IsNew(KEY_INPUT_RIGHT) || inputState.AKeyLX > 0.0f)
	{
		// �E�ړ�
		movedPos.x += speed_;

		// �����̕ύX
		dir_ = AsoUtility::DIR::RIGHT;

		// �A�j���[�V�����J�E���^�̐i�s
		cntAnim_++;
	}

	// �Փ˔���(X)
	footPos = movedPos;
	footPos.y += 20;

	leftFootPos = movedPos;
	leftFootPos.x -= 10;
	leftFootPos.y += 20;

	rightFootPos = movedPos;
	rightFootPos.x += 10;
	rightFootPos.y += 20;

	// �X�e�[�W�̏Փ˔���
	if (gameScene_->IsCollisionStage(movedPos) == true
		|| gameScene_->IsCollisionStage(footPos) == true
		|| gameScene_->IsCollisionStage(rightFootPos) == true
		|| gameScene_->IsCollisionStage(leftFootPos) == true
		|| gameScene_->IsCollisionDoor(movedPos) == true
		|| gameScene_->IsCollisionDoor(footPos) == true
		|| gameScene_->IsCollisionDoor(rightFootPos) == true
		|| gameScene_->IsCollisionDoor(leftFootPos) == true
		|| gameScene_->IsCollisionGate(movedPos) == true
		|| gameScene_->IsCollisionGate(footPos) == true
		|| gameScene_->IsCollisionGate(rightFootPos) == true
		|| gameScene_->IsCollisionGate(leftFootPos) == true)
	{

		Stage* stage = gameScene_->GetStage();

		Vector2 mapPos1 = gameScene_->World2MapPos(movedPos);
		Vector2 mapPos2 = gameScene_->World2MapPos(footPos);
		Vector2 mapPos3 = gameScene_->World2MapPos(rightFootPos);
		Vector2 mapPos4 = gameScene_->World2MapPos(leftFootPos);

		int chipNo1 = stage->GetDoorNo(mapPos1);
		int chipNo2 = stage->GetDoorNo(mapPos2);
		int chipNo3 = stage->GetDoorNo(mapPos3);
		int chipNo4 = stage->GetDoorNo(mapPos4);
		int chipNo5 = stage->GetGateNo(mapPos1);
		int chipNo6 = stage->GetGateNo(mapPos2);
		int chipNo7 = stage->GetGateNo(mapPos3);
		int chipNo8 = stage->GetGateNo(mapPos4);

		if (
			(
				stage->IsDoor1(chipNo1) || stage->IsDoor1(chipNo2) || stage->IsDoor1(chipNo3) || stage->IsDoor1(chipNo4)
				)
			&& gameScene_->GetKey1())
		{
			// �ړ��\�Ɣ��f�ł����̂ŁA�����W���X�V
			pos_ = movedPos;
			//return;
		}

		if (
			(
				stage->IsDoor2(chipNo1) || stage->IsDoor2(chipNo2) || stage->IsDoor2(chipNo3) || stage->IsDoor2(chipNo4)
				)
			&& gameScene_->GetKey2())
		{
			// �ړ��\�Ɣ��f�ł����̂ŁA�����W���X�V
			pos_ = movedPos;
			//return;
		}

		if (
			(
				stage->IsDoor3(chipNo1) || stage->IsDoor3(chipNo2) || stage->IsDoor3(chipNo3) || stage->IsDoor3(chipNo4)
				)
			&& gameScene_->GetKey3())
		{
			// �ړ��\�Ɣ��f�ł����̂ŁA�����W���X�V
			pos_ = movedPos;
			//return;
		}

		if (
			(
				stage->IsDoor4(chipNo1) || stage->IsDoor4(chipNo2) || stage->IsDoor4(chipNo3) || stage->IsDoor4(chipNo4)
				)
			&& gameScene_->GetKey4())
		{
			// �ړ��\�Ɣ��f�ł����̂ŁA�����W���X�V
			pos_ = movedPos;
			//return;
		}

		if (stage->IsGate(chipNo5) || stage->IsGate(chipNo6) || stage->IsGate(chipNo7) || stage->IsGate(chipNo8))
		{
			// �ړ��\�Ɣ��f�ł����̂ŁA�����W���X�V
			pos_ = movedPos;
			//return;
		}

		// �Փ˂��Ă��� -> ���W�����ɖ߂�
		movedPos = pos_;
		//return;
	}

	else
	{
		// �ړ��\�Ɣ��f�ł����̂ŁA�����W���X�V
		pos_ = movedPos;
	}

	// �ړ��ʂɂ���Č����𔻒肷��
	Vector2 diffMovePow;
	diffMovePow.x = pos_.x - prePos.x;
	diffMovePow.y = pos_.y - prePos.y;

	if (diffMovePow.x > 0)
	{
		dir_ = AsoUtility::DIR::RIGHT;
	}

	else if (diffMovePow.x < 0)
	{
		dir_ = AsoUtility::DIR::LEFT;
	}

	else if (diffMovePow.y > 0)
	{
		dir_ = AsoUtility::DIR::DOWN;
	}

	else if (diffMovePow.y < 0)
	{
		dir_ = AsoUtility::DIR::UP;
	}

}

void Player::Level(void)
{

	// �o���l�����̒l�ɒB�����烌�x�����グ��
	if (exp_ >= 100)
	{
		level_ = 2;
	}

	if (exp_ >= 200)
	{
		level_ = 3;
	}

	if (exp_ >= 300)
	{
		level_ = 4;
	}

	if (exp_ >= 400)
	{
		level_ = 5;
	}

}

void Player::Exp(int exp)
{
	exp_ += exp;
}
