#include <DxLib.h>
#include "EnemyBase.h"
#include "GameScene.h"
#include "Stage.h"

EnemyBase::EnemyBase(void)
{
}

EnemyBase::~EnemyBase(void)
{
}

void EnemyBase::Init(GameScene* scene)
{

	// �Q�[���V�[���̋@�\�����ł��g����悤�Ƀ����o�ϐ��Ɋi�[
	gameScene_ = scene;

	// �G�L�����ʂ̃p�����[�^�ݒ�
	SetParam();

	int dirNum = static_cast<int>(AsoUtility::DIR::MAX);
	int allNum = NUM_ANIM * dirNum;

	std::string path = "Image/Enemy/";
	path = path + imgFileName_;

	// �������ꂽ�摜��ǂݍ���
	LoadDivGraph(path.c_str(),
		allNum,
		NUM_ANIM,
		dirNum,
		size_.x,
		size_.y,
		&imgs_[0][0]
	);

	// ���W�̏�����
	pos_.x = 400;
	pos_.y = 400;

	// ����
	dir_ = AsoUtility::DIR::DOWN;

	// �A�j���[�V�����J�E���^
	cntAnim_ = 0;

	// �G�̐���
	isAlive_ = true;

}

void EnemyBase::SetParam(void)
{
}

void EnemyBase::Update(void)
{
	// �X�e�[�W�̏Փ�
	StageCollision();

	// �A�j���[�V�����J�E���^�̐i�s
	cntAnim_++;

}

void EnemyBase::Draw(void)
{

	if (!isAlive_)
	{
		// �������Ă��Ȃ���Ε`�悵�Ȃ�
		return;
	}

	// �ŐV�Q�[���V�[������A�J�����̈ʒu���擾
	Vector2 cameraPos = gameScene_->GetCameraPos();

	// �A�j���[�V�����̃`�b�v�ԍ�(0�`3)�����
	int animNo = static_cast<int>(static_cast<float>(cntAnim_) * speedAnim_) % NUM_ANIM;

	Vector2 pos = AsoUtility::Round(pos_);
	DrawGraph(pos_.x - size_.x / 2 - cameraPos.x,
		pos_.y - size_.y / 2 - cameraPos.y,
		imgs_[static_cast<int>(dir_)][animNo], true);

}

void EnemyBase::Release(void)
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

Vector2F EnemyBase::GetPos(void)
{
    return pos_;
}

void EnemyBase::SetPos(Vector2F pos)
{
	pos_ = pos;
}

bool EnemyBase::IsGetAlive(void)
{
	return isAlive_;
}

void EnemyBase::IsSetAlive(bool alive)
{
	isAlive_ = alive;
}

Vector2 EnemyBase::GetSize(void)
{
	return size_;
}

void EnemyBase::Damage(int damage)
{

	// HP�����炷 �_���[�W�ʕ�
	hp_ -= damage;

	// HP���O�ȉ��ɂȂ�����G�𐶑����Ă��Ȃ����Ƃɂ���
	if (hp_ <= 0)
	{
		hp_ = 0;
		isAlive_ = false;
	}

}

int EnemyBase::GetExp(void)
{
	return exp_;
}

//int EnemyBase::GetHP(void)
//{
//	return hp_;
//}

int EnemyBase::GetFootPosY(void)
{
	return static_cast<int>(pos_.y) + size_.y / 2;
}

void EnemyBase::StageCollision(void)
{


	// �v���C���[�̈ʒu���擾
	Vector2 pPos = gameScene_->GetPlayerPos();

	// �v���C���[�Ɍ������x�N�g��
	Vector2F vec;
	vec.x = static_cast<float>(pPos.x - pos_.x);
	vec.y = static_cast<float>(pPos.y - pos_.y);

	// �ړ��O���W���m��
	Vector2F prePos = pos_;

	// �ړ��\��̍��W���m��
	Vector2F movedPos = pos_;


	// �x�N�g���̑傫��
	float size = sqrtf(vec.x * vec.x + vec.y * vec.y);

	if (size < 320)
	{
		if (size > 0)
		{

			// �ړ����������߂�
			Vector2F direction;
			direction.x = vec.x / size;
			direction.y = vec.y / size;

			// �ړ�����W���v�Z����
			movedPos = Move(direction);

			// �Փ˂̃`�F�b�N
			if (IsStageCollision(movedPos))
			{
				Vector2F directionX;
				// �Փ˂���
				if (direction.x >= 0.0f)
				{
					directionX = { 1.0f,0.0f };
				}
				else
				{
					directionX = { -1.0f, 0.0f };
				}

				movedPos = Move(directionX);

				if (IsStageCollision(movedPos))
				{
					Vector2F directionY;
					// �Փ˂���
					if (direction.y >= 0.0f)
					{
						directionY = { 0.0f,1.0f };
					}
					else
					{
						directionY = { 0.0f, -1.0f };
					}
					movedPos = Move(directionY);

					if (IsStageCollision(movedPos))
					{

					}
				}

			}
		}
	}
}

bool EnemyBase::IsStageCollision(Vector2F movedPos)
{

	bool retX = true;
	bool retY = true;

	// �������W�̐錾
	Vector2 footPos;

	// �Փ˔���(Y)
	footPos = movedPos;
	footPos.y += 20;

	// �X�e�[�W�̏Փ˔���
	if (gameScene_->IsCollisionStage(movedPos) == true
		|| gameScene_->IsCollisionStage(footPos) == true
		|| gameScene_->IsCollisionDoor(movedPos) == true
		|| gameScene_->IsCollisionDoor(footPos) == true)
	{

		Stage* stage = gameScene_->GetStage();

		Vector2 mapPos1 = gameScene_->World2MapPos(movedPos);
		Vector2 mapPos2 = gameScene_->World2MapPos(footPos);

		int chipNo1 = stage->GetDoorNo(mapPos1);
		int chipNo2 = stage->GetDoorNo(mapPos2);


		if ((stage->IsDoor1(chipNo1) || stage->IsDoor1(chipNo2))
			&& gameScene_->GetKey1())
		{
			// �ړ��\�Ɣ��f�ł����̂ŁA�����W���X�V
			pos_ = movedPos;
			retY = false;
		}

		if ((stage->IsDoor2(chipNo1) || stage->IsDoor2(chipNo2))
			&& gameScene_->GetKey2())
		{
			// �ړ��\�Ɣ��f�ł����̂ŁA�����W���X�V
			pos_ = movedPos;
			retY = false;
		}

		if ((stage->IsDoor3(chipNo1) || stage->IsDoor3(chipNo2))
			&& gameScene_->GetKey3())
		{
			// �ړ��\�Ɣ��f�ł����̂ŁA�����W���X�V
			pos_ = movedPos;
			retY = false;
		}

		if ((stage->IsDoor4(chipNo1) || stage->IsDoor4(chipNo2))
			&& gameScene_->GetKey4())
		{
			// �ړ��\�Ɣ��f�ł����̂ŁA�����W���X�V
			pos_ = movedPos;
			retY = false;
		}

		// �Փ˂��Ă��� -> ���W�����ɖ߂�
		movedPos = pos_;

	}
	else
	{
		// �ړ��\�Ɣ��f�ł����̂ŁA�����W���X�V
		pos_ = movedPos;
		retY = false;
	}

	// �Փ˔���(X)
	footPos = movedPos;
	footPos.y += 20;

	// �X�e�[�W�̏Փ˔���
	if (gameScene_->IsCollisionStage(movedPos) == true
		|| gameScene_->IsCollisionStage(footPos) == true
		|| gameScene_->IsCollisionDoor(movedPos) == true
		|| gameScene_->IsCollisionDoor(footPos) == true)
	{

		Stage* stage = gameScene_->GetStage();

		Vector2 mapPos1 = gameScene_->World2MapPos(movedPos);
		Vector2 mapPos2 = gameScene_->World2MapPos(footPos);

		int chipNo1 = stage->GetDoorNo(mapPos1);
		int chipNo2 = stage->GetDoorNo(mapPos2);


		if ((stage->IsDoor1(chipNo1) || stage->IsDoor1(chipNo2))
			&& gameScene_->GetKey1())
		{
			// �ړ��\�Ɣ��f�ł����̂ŁA�����W���X�V
			pos_ = movedPos;
			retX = false;
		}

		if ((stage->IsDoor2(chipNo1) || stage->IsDoor2(chipNo2))
			&& gameScene_->GetKey2())
		{
			// �ړ��\�Ɣ��f�ł����̂ŁA�����W���X�V
			pos_ = movedPos;
			retX = false;
		}

		if ((stage->IsDoor3(chipNo1) || stage->IsDoor3(chipNo2))
			&& gameScene_->GetKey3())
		{
			// �ړ��\�Ɣ��f�ł����̂ŁA�����W���X�V
			pos_ = movedPos;
			retX = false;
		}

		if ((stage->IsDoor4(chipNo1) || stage->IsDoor4(chipNo2))
			&& gameScene_->GetKey4())
		{
			// �ړ��\�Ɣ��f�ł����̂ŁA�����W���X�V
			pos_ = movedPos;
			retX = false;
		}

		// �Փ˂��Ă��� -> ���W�����ɖ߂�
		movedPos = pos_;
	}

	else
	{
		// �ړ��\�Ɣ��f�ł����̂ŁA�����W���X�V
		pos_ = movedPos;
		retX = false;
	}

	return retY || retX;

}

Vector2F EnemyBase::Move(Vector2F dir)
{

	// �ړ��\��̍��W���m��
	Vector2F movedPos = pos_;

	// �ړ���
	Vector2F movePow;
	movePow.x = dir.x * speed_;
	movePow.y = dir.y * speed_;

	// �ړ�����(���W+�ړ���)
	movedPos.x += (movePow.x);
	movedPos.y += (movePow.y);

	// ������ς���(�ړ��ʂ��傫��������D��)
	if (abs(dir.x) > abs(dir.y))
	{
		// ���������E������
		if (dir.x > 0)
		{
			dir_ = AsoUtility::DIR::RIGHT;
		}
		else
		{
			dir_ = AsoUtility::DIR::LEFT;
		}
	}

	return movedPos;

}
