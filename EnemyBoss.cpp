#include <DxLib.h>
#include "EnemyBoss.h"
#include "EnemyShot.h"
#include "Application.h"
#include "Stage.h"

EnemyBoss::EnemyBoss(void)
{
}

EnemyBoss::~EnemyBoss(void)
{
}

void EnemyBoss::Init(GameScene* scene)
{

	// �Q�[���V�[���̋@�\�����ł��g����悤�Ƀ����o�ϐ��Ɋi�[
	gameScene_ = scene;

	// �e�̏�����
	enemyShot_ = new EnemyShot();
	enemyShot_->Init(scene);

	int dirNum = static_cast<int>(AsoUtility::DIR::MAX);
	int allNum = NUM_ANIM * dirNum;
	// �������ꂽ�摜��ǂݍ���
	LoadDivGraph("Image/Enemy/StormGiant.png",
		allNum,
		NUM_ANIM,
		dirNum,
		SIZE_X,
		SIZE_Y,
		&imgs_[0][0]
	);

	// ���W�̏�����
	pos_.x = 368;
	pos_.y = 1840;

	// �ړ����x
	speed_ = SPEED_DEFAULT;

	// ����
	dir_ = AsoUtility::DIR::DOWN;

	// �A�j���[�V�����J�E���^
	cntAnim_ = 0;

	// �A�j���[�V�������x
	speedAnim_ = ANIM_SPEED_DEFAULT;

	// HP
	hpMax_ = 300;
	hp_ = hpMax_;

	// ��������
	isAlive_ = true;

	// �{�X�̍U������SE
	SEBossAttack_ = LoadSoundMem("Music/�{�X�̍U��.mp3");

}

void EnemyBoss::Update(void)
{

	// �v���C���[�̈ʒu���擾
	Vector2 pPos = gameScene_->GetPlayerPos();

	if (isAlive_)
	{

		// �X�e�[�W�̏Փ�
		StageCollision();

		// �A�j���[�V�����J�E���^�̐i�s
		cntAnim_++;

		//�e�̐�������
		Vector2 playerPos = gameScene_->GetPlayerPos();
		Vector2 ePos = pos_;
		Vector2 vector;
		vector.x = pPos.x - ePos.x;
		vector.y = pPos.y - ePos.y;
		float len = sqrtf(vector.x * vector.x + vector.y * vector.y);
		Vector2F dir;
		dir.x = vector.x / len;
		dir.y = vector.y / len;

		if (gameScene_->GetKey1() && gameScene_->GetKey2() && gameScene_->GetKey3() && gameScene_->GetKey4())
		{
			if (enemyShot_->IsEnableCreate())
			{
				if (len <= 500)
				{
					//�e�̐��� 
					enemyShot_->Create(pos_, dir);

					// �{�X�̑Ō���
					PlaySoundMem(SEBossAttack_, DX_PLAYTYPE_BACK, true);

				}
			}
		}


		// �e�̍X�V
		enemyShot_->Update();
	}
}

void EnemyBoss::Draw(void)
{

	if (isAlive_)
	{


		// �ŐV�Q�[���V�[������A�J�����̈ʒu���擾
		Vector2 cameraPos = gameScene_->GetCameraPos();

		// �A�j���[�V�����̃`�b�v�ԍ�(0�`8)�����
		int animNo = static_cast<int>(static_cast<float>(cntAnim_) * speedAnim_) % NUM_ANIM;

		DrawGraph(pos_.x - SIZE_X / 2 - cameraPos.x,
			pos_.y - SIZE_Y / 2 - cameraPos.y,
			imgs_[static_cast<int>(dir_)][animNo], true);

		// �e�̕`��
		enemyShot_->Draw();
	}
}

void EnemyBoss::Release(void)
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

	// �G�̒e�J��
	enemyShot_->Release();
	delete enemyShot_;

}

Vector2 EnemyBoss::GetPos(void)
{
	return pos_;
}

EnemyShot* EnemyBoss::GetEnemyShot(void)
{
	return enemyShot_;
}

void EnemyBoss::SetPos(Vector2 pos)
{
	pos_ = pos;
}

AsoUtility::DIR EnemyBoss::GetDir(void)
{
	return dir_;
}

void EnemyBoss::Damage(int damage)
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

int EnemyBoss::GetHP(void)
{
	return hp_;
}

int EnemyBoss::GetHPMax(void)
{
	return hpMax_;
}

bool EnemyBoss::IsGetAlive(void)
{
	return isAlive_;
}

void EnemyBoss::IsSetAlive(bool alive)
{
	isAlive_ = alive;
}

void EnemyBoss::StageCollision(void)
{

	if (!isAlive_)
	{
		return;
	}

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


	if (size < 16)
	{
		// �߂�����̂ňړ����Ȃ�
		return;
	}



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

bool EnemyBoss::IsStageCollision(Vector2F movedPos)
{

	bool retX = true;
	bool retY = true;

	// �������W�̐錾
	Vector2 footPos;

	// �Փ˔���(Y)
	footPos = movedPos;
	footPos.y += 20;

	if (gameScene_->GetKey1() && gameScene_->GetKey2() && gameScene_->GetKey3() && gameScene_->GetKey4())
	{
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
	}
	return retY || retX;

}

Vector2F EnemyBoss::Move(Vector2F dir)
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
