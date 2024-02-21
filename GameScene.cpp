#include <algorithm>
#include <DxLib.h>
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "Application.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Stage.h"
#include "Player.h"
#include "EnemyBoss.h"
#include "EnemyShot.h"
#include "EnemyBase.h"
#include "EnemyAcidOoze.h"
#include "EnemyBlindedGrimlock.h"
#include "EnemyBloodshotEye.h"
#include "Shot.h"
#include "StartMes.h"
#include "GameScene.h"



GameScene::GameScene(void)
{
}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
{

    // �X�e�[�W�̏�����
    stage_ = new Stage();
    stage_->Init(this);

	// �v���C���[�̏�����
	player_ = new Player();
	player_->Init(this);

	// �G�l�~�[�{�X�̏�����
	enemyBoss_ = new EnemyBoss();
	enemyBoss_->Init(this);

	// �e�̏�����
	shot_ = new Shot();
	shot_->Init(this);

	// �X�^�[�g���b�Z�[�W�̏�����
	startMes_ = new StartMes();
	startMes_->Init(this);

	// �G���J�E���^�[������
	enCounter = 0;

    // �J�������W�̏�����
	cameraPos_.x = player_->GetPos().x - (Application::SCREEN_SIZE_X / 2);
    cameraPos_.y = player_->GetPos().y - (Application::SCREEN_SIZE_Y / 2);

	// �A�N�^�[�摜��ǂݍ���
	Actorimg_ = LoadGraph("Image/Player/Actor1.png");

	// ��1�̉摜�̏�����
	keyImage1_ = LoadGraph("Image/UI/key1.png");
	
	// ��2�̉摜�̏�����
	keyImage2_ = LoadGraph("Image/UI/key2.png");

	// ��3�̉摜�̏�����
	keyImage3_ = LoadGraph("Image/UI/key3.png");

	// ��4�̉摜�̏�����
	keyImage4_ = LoadGraph("Image/UI/key4.png");

	// �摜�̓ǂݍ���
	imgGameClear_ = LoadGraph("Image/UI/GameClear.png");

	// UI�̖�̉摜�̓ǂݍ���
	ArrowBack_ = LoadGraph("Image/UI/ArrowBack.png");

	// UI�p�̕���̓ǂݍ���
	UIimgs_ = LoadGraph("Image/Player/IconArrow.png");

	// UI�p�̕���̓ǂݍ���
	UIimgs2_ = LoadGraph("Image/Player/IconArrow2.png");

	// UI�p�̕���̓ǂݍ���
	UIimgs3_ = LoadGraph("Image/Player/IconArrow3.png");

	// UI�p�̕���̓ǂݍ���
	UIimgs4_ = LoadGraph("Image/Player/IconArrow4.png");

	// UI�p�̕���̓ǂݍ���
	UIimgs5_ = LoadGraph("Image/Player/IconArrow5.png");

	// ���x��1�摜�̓ǂݍ���
	Level1_ = LoadGraph("Image/UI/Level1.png");

	// ���x��2�摜�̓ǂݍ���
	Level2_ = LoadGraph("Image/UI/Level2.png");

	// ���x��3�摜�̓ǂݍ���
	Level3_ = LoadGraph("Image/UI/Level3.png");

	// ���x��4�摜�̓ǂݍ���
	Level4_ = LoadGraph("Image/UI/Level4.png");

	// ���x��5�摜�̓ǂݍ���
	Level5_ = LoadGraph("Image/UI/Level5.png");

	// ���x���摜�̔w�i
	LevelBack_ = LoadGraph("Image/UI/LevelBack.png");

	// �ǂݍ��ރt�H���g�t�@�C���̃p�X
	LPCSTR font_path = "DotGothic16.ttf";

		// �ꎞ�I�ȕ`��̈�
	tmpScreen_ = MakeScreen(
		Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, true);

	isKey1_ = false;
	isKey2_ = false;
	isKey3_ = false;
	isKey4_ = false;

	// ���Ԃ̃J�E���^�̏�����
	timecnt_ = 0;

	// �Q�[���V�[����BGM
	bgmGameScene_ = LoadSoundMem("Music/�Q�[��.ogg");

	// �Q�[���V�[����BGM�Đ�
	PlaySoundMem(bgmGameScene_, DX_PLAYTYPE_LOOP, true);

	// ����{�^����SE�̓ǂݍ���
	SEBotton_ = LoadSoundMem("Music/����{�^��.mp3");

	// ����{�^����SE�̓ǂݍ���
	SEActor_ = LoadSoundMem("Music/�A�N�^�[.mp3");

	// �U���{�^����SE
	SEAttack_ = LoadSoundMem("Music/�U��.mp3");

	// �Ō�����SE
	SE1Hit_ = LoadSoundMem("Music/�Ō����x��1.mp3");

	// �Ō�����SE
	SE2Hit_ = LoadSoundMem("Music/�Ō����x��2.mp3");

	// �Ō�����SE
	SE3Hit_ = LoadSoundMem("Music/�Ō����x��3.mp3");

	// �Ō�����SE
	SE4Hit_ = LoadSoundMem("Music/�Ō����x��4.mp3");

	// �Ō�����SE
	SE5Hit_ = LoadSoundMem("Music/�Ō����x��5.mp3");

	// �{�X�̑Ō�����SE
	SEBossHit_ = LoadSoundMem("Music/�{�X�̑Ō�.mp3");

	// �h�A��SE
	SEDoor_ = LoadSoundMem("Music/�h�A.mp3");

}

void GameScene::Update(void)
{

	// �X�^�[�g���b�Z�[�W�̍X�V
	startMes_->Update();

	// �q�b�g�X�g�b�v�ŏ������f
	if (hitStopCnt_ > 0)
	{
		hitStopCnt_--;
		return;
	}

	// �X���[
	if (slowCnt_ > 0)
	{
		slowCnt_--;
		if (slowCnt_ % 5 != 0)
		{
			return;
		}
	}


	if (startMes_->GetCnt() >= 240)
	{
		if (!isActor1_)
		{
			if (!isActor2_)
			{
				if (!isActor3_)
				{
					if (!isActor4_)
					{
						if (!gameClear_)
						{


							// �J��������
							CameraMove();

							// �v���C���[�̍X�V
							player_->Update();

							// �G�l�~�[�{�X�̍X�V
							enemyBoss_->Update();

							// �G�l�~�[�̍X�V
							size_t size = enemys_.size();
							for (int i = 0; i < size; i++)
							{
								enemys_[i]->Update();
							}


							//�e�̐�������
							if (shot_->IsEnableCreate())
							{

								InputManager& ins = InputManager::GetInstance();

								// �P�t���[���O�̃}�E�X�N���b�N���
								isShotKeyOld_ = isShotKeyNew_;
								// ���݃t���[���̃}�E�X�N���b�N���
								isShotKeyNew_ = ins.IsClickMouseLeft();

								// �}�E�X�����������Ă���ԁA�e���o������
								//if (CheckHitKey(KEY_INPUT_Z)||ins.IsClickMouseLeft())

								// �}�E�X���������Ƃ������A�e���o��(�I���W�i��)
								//if (CheckHitKey(KEY_INPUT_Z)||(isShotKeyNew_ == true && isShotKeyOld_ == false))

								auto info = ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1);
								// ���A�i���O�L�[
								info.AKeyLX;
								// �E�A�i���O�L�[
								info.AKeyRX;

								auto pad = InputManager::JOYPAD_NO::PAD1;
								auto input = ins.IsPadBtnTrgDown(pad, InputManager::JOYPAD_BTN::RIGHT);

								// �}�E�X���������Ƃ������A�e���o��(InputManager)
								if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_Z) || input)
								{

									//�e�̐���
									shot_->Create(player_->GetPos().ToVector2F(), player_->GetDir());

									// �U����
									PlaySoundMem(SEAttack_, DX_PLAYTYPE_BACK, true);

								}

							}

							// �e�̍X�V
							shot_->Update();

							// �G���J�E���g
							enCounter++;

							if (enCounter > ENCOUNT)
							{

								// �G���J�E���g���Z�b�g
								enCounter = 0;

								// �G�������_���ɐ���
								EnemyBase* e = nullptr;
								int eType = GetRand(static_cast<int>(EnemyBase::TYPE::MAX) - 1);
								EnemyBase::TYPE type = static_cast<EnemyBase::TYPE>(eType);

								switch (type)
								{
								case EnemyBase::TYPE::AcidOoze:
									e = new EnemyAcidOoze();
									break;
								case EnemyBase::TYPE::BlindedGrimlock:
									e = new EnemyBlindedGrimlock();
									break;
								case EnemyBase::TYPE::BloodshotEye:
									e = new EnemyBloodshotEye();
									break;
								}

								e->Init(this);

								// �X�̕����Ƀ����_���ɃX�|�[��������
								int roomMapPosX = GetRand(2);
								int roomMapPosY = GetRand(2);

								int roomChipNumX = 23;
								int roomChipNumY = 23;

								int roomChipSizeX = 32;
								int roomChipSizeY = 32;

								int cx = roomMapPosX * roomChipNumX * roomChipSizeX + (roomChipNumX * roomChipSizeX / 2);
								int cy = roomMapPosY * roomChipNumY * roomChipSizeY + (roomChipNumY * roomChipSizeY / 2);

								int randX = -300 + GetRand(500);
								int randY = -300 + GetRand(500);

								Vector2 randPos = { cx + randX , cy + randY };


								Vector2 footPos = randPos;
								footPos.y += 20;

								if ((!IsCollisionStage(randPos) &&
									!IsCollisionStage(footPos)))
								{
									// ���W�̐ݒ�
									e->SetPos(randPos.ToVector2F());
								}

								// �ϒ��z��̈�Ԍ��ɒǉ�
								enemys_.push_back(e);

							}

							// �Փˏ���
							Collision();



							// �v���C���[��HP���[���ɂȂ�����Q�[���I�[�o�[
							if (!player_->IsAlive())
							{
								SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMEOVER, true);

								// �Q�[���V�[����BGM��~
								StopSoundMem(bgmGameScene_);
							}

							// �X�C�b�`�̔���
							TreasureChest();
						}
							// �E�o�Q�[�g�ɓ���������Q�[���N���A
							if (IsCollisionGate(player_->GetPos()) && enemyBoss_->GetHP() <= 0)
							{
								gameClear_ = true;



								auto& ins = InputManager::GetInstance();
								auto pad = InputManager::JOYPAD_NO::PAD1;
								auto input = ins.IsPadBtnTrgDown(pad, InputManager::JOYPAD_BTN::RIGHT);

								if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE) || input && gameClear_)
								{
									SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE, true);

									// �Q�[���V�[����BGM��~
									StopSoundMem(bgmGameScene_);
								}
							}

					}
				}
			}
		}
	}
	// �A�N�^�[�̔���
	Actor();

}

void GameScene::Draw(void)
{

	if (!gameClear_)
	{

		// �U��
		if (hitStopCnt_ > 0)
		{
			// �`���̃X�N���[����ݒ� �q�b�g�X�g�b�v���́A
			SetDrawScreen(tmpScreen_);
		}

		// �X�e�[�W�̕`��
		stage_->Draw();

		// �v���C���[�̕`��
		player_->Draw();

		// �G�l�~�[�{�X�̕`��
		enemyBoss_->Draw();

		// �G�̕`�揇���\�[�g����
		//SortEnemys();
		sort(enemys_.begin(), enemys_.end(),
			[](EnemyBase* a, EnemyBase* b) {

				return a->GetFootPosY() < b->GetFootPosY();

			}
		);

		// �G�`��(�������O�ɕ`�悵�Ă���)
		// �͈�for��
		//int cnt = 0;
		for (EnemyBase* enemy : enemys_)
		{
			//cnt++;
			enemy->Draw();
		}


		// �e�̕`��
		shot_->Draw();

		// UI�̕`��
		DrawUI();

		  // �X�^�[�g���b�Z�[�W�̕`��
		startMes_->Draw();

		// �U��
		if (hitStopCnt_ > 0)
		{
			// �`���̃X�N���[����ݒ�
			SetDrawScreen(DX_SCREEN_BACK);
			// 0 or 1
			int shake = hitStopCnt_ / 5 % 2;
			// 0 or 2 �摜���o�b�N�o�b�t�@�ɏ�������
			shake *= 2;
			// -1 or 1 ���̍ۂɏ������ވʒu��
			shake -= 1;
			// -5 or 5
			shake *= 5;
			DrawGraph(shake, shake, tmpScreen_, true);
		}
	}


	// �Q�[���N���A
	if (gameClear_)
	{
		fadeCnt_++;
		//SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeCnt_ < 255 ? 255 - fadeCnt_ : 0);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeCnt_);
		DrawGraph(0, 0, imgGameClear_, true);
		SetFontSize(50);	// ���₷���̂��߁A�t�H���g�T�C�Y��傫��
		ChangeFont("DotGothic16", DX_CHARSET_DEFAULT);
		DrawFormatString(250, 100, 0xffffff, "�^�C��:%d��%d�b", minute_, second_);
	}

}

void GameScene::DrawUI(void)
{

	if(startMes_->GetCnt() >= 240)
	// ����
	if (!gameClear_)
	{
		timecnt_ += 1;

		second_ = timecnt_ / 60;
		if (second_ >= 59)
		{
			minute_++;
			timecnt_ = 0;
		}

		SetFontSize(40);	// ���₷���̂��߁A�t�H���g�T�C�Y��傫��
		DrawFormatString(0, 0, 0xffffff, "�^�C��:%d��%d�b", minute_, second_);

		// HP�Q�[�W�̊����v�Z

		float H;
		int hpGauge = 0;
		int hpLength = 400;

		H = player_->GetHP() * (512.0f / player_->GetHPMax()) - 100;

		int R = min(max((384 - H), 0), 0xff);

		int G = min(max((H + 64), 0), 0xff);

		int B = max((H - 384), 0);

		hpGauge = hpLength * player_->GetHP() / player_->GetHPMax();

		DrawBox(0, Application::SCREEN_SIZE_Y - 75, 50, Application::SCREEN_SIZE_Y - 50, 0xffffff, true);
		DrawBox(50, Application::SCREEN_SIZE_Y - 75, 50 + hpGauge, Application::SCREEN_SIZE_Y - 50, GetColor(R, G, B), true);

		SetFontSize(20);	// ���₷���̂��߁A�t�H���g�T�C�Y��傫��
		ChangeFont("DotGothic16", DX_CHARSET_DEFAULT);
		DrawFormatString(10, Application::SCREEN_SIZE_Y - 75, 0x000000, "HP");

		// �A�N�^�[�摜�̕\��
		Vector2 pPos = { 0, 400 };
		if (isActor1_)
		{
			DrawBox(0, 400, 384, 500, 0x000000, true);
			DrawGraph(pPos.x, pPos.y, Actorimg_, true);
			DrawFormatString(100, 420, 0xffffff, "�����J�����悤��");
		}

		if (isActor2_)
		{
			DrawBox(0, 400, 384, 500, 0x000000, true);
			DrawGraph(pPos.x, pPos.y, Actorimg_, true);
			DrawFormatString(100, 420, 0xffffff, "�����J�����悤��");
		}

		if (isActor3_)
		{
			DrawBox(0, 400, 384, 500, 0x000000, true);
			DrawGraph(pPos.x, pPos.y, Actorimg_, true);
			DrawFormatString(100, 420, 0xffffff, "�����J�����悤��");
		}

		if (isActor4_)
		{
			DrawBox(0, 400, 384, 500, 0x000000, true);
			DrawGraph(pPos.x, pPos.y, Actorimg_, true);
			DrawFormatString(100, 420, 0xffffff, "�����J�����悤��");
		}

		// ���x���̎擾
		int level = player_->GetLevel();

		// UI�̖�̉摜�̔w�i
		DrawGraph(600, 500, ArrowBack_, true);

		// UI�̖�1�̉摜
		if (level == 1)
		{
			DrawGraph(617, 517 , UIimgs_, true);
		}

		// UI�̖�2�̉摜
		if (level == 2)
		{
			DrawGraph(617, 517, UIimgs2_, true);
		}

		// UI�̖�3�̉摜
		if (level == 3)
		{
			DrawGraph(617, 517, UIimgs3_, true);
		}

		// UI�̖�4�̉摜
		if (level == 4)
		{
			DrawGraph(617, 517, UIimgs4_, true);
		}

		// UI�̖�5�̉摜
		if (level == 5)
		{
			DrawGraph(617, 517, UIimgs5_, true);
		}

		// ���x���摜�̔w�i
		DrawGraph(475, 525, LevelBack_, true);

		// ���x��1�̉摜
		if (level == 1)
		{
			DrawGraph(475, 525, Level1_, true);
		}

		// ���x��2�̉摜
		if (level == 2)
		{
			DrawGraph(475, 525, Level2_, true);
		}

		// ���x��3�̉摜
		if (level == 3)
		{
			DrawGraph(475, 525, Level3_, true);
		}

		// ���x��4�̉摜
		if (level == 4)
		{
			DrawGraph(475, 525, Level4_, true);
		}

		// ���x��5�̉摜
		if (level == 5)
		{
			DrawGraph(475, 525, Level5_, true);
		}

	}

}


void GameScene::Release(void)
{

    // �X�e�[�W�J��
    stage_->Release();
    delete stage_;

	// �v���C���[�J��
	player_->Release();
	delete player_;

	// �G�l�~�[�{�X�̊J��
	enemyBoss_->Release();
	delete enemyBoss_;

	// �G�l�~�[�J��
	size_t size = enemys_.size();
	for (int i = 0; i < size; i++)
	{
		enemys_[i]->Release();
		delete enemys_[i];
	}

	// �e�J��
	shot_->Release();
	delete shot_;

	// �X�^�[�g���b�Z�[�W�̍X�V
	startMes_->Release();
	delete startMes_;

}

Vector2 GameScene::GetCameraPos(void)
{
    return cameraPos_;
}

Vector2 GameScene::World2MapPos(Vector2 worldPos)
{

    Vector2 ret;

    int  mapX = worldPos.x / Stage::CHIP_SIZE_X;
    int  mapY = worldPos.y / Stage::CHIP_SIZE_Y;

    ret.x = mapX;
    ret.y = mapY;

    return ret;

}

bool GameScene::IsCollisionStage(Vector2 worldPos)
{

	// ���[���h���W����}�b�v���W�ɕϊ�����
	Vector2 mapPos = World2MapPos(worldPos);

	// �}�b�v���W����}�b�v�`�b�v�ԍ����擾����
	int chipNo = stage_->GetCollisionStageNo(mapPos);

	if (chipNo != -1)
	{
		return true;
	}

	return false;
}

bool GameScene::IsCollisionDoor(Vector2 worldPos)
{

	// ���[���h���W����}�b�v���W�ɕϊ�����
	Vector2 mapPos = World2MapPos(worldPos);

	// �}�b�v���W����}�b�v�`�b�v�ԍ����擾����
	int chipNo = stage_->GetCollisionDoorNo(mapPos);

	if (chipNo != -1)
	{
		return true;
	}

	return false;
}

bool GameScene::IsCollisionGate(Vector2 worldPos)
{

	// ���[���h���W����}�b�v���W�ɕϊ�����
	Vector2 mapPos = World2MapPos(worldPos);

	// �}�b�v���W����}�b�v�`�b�v�ԍ����擾����
	int chipNo = stage_->GetGateNo(mapPos);

	if (chipNo != -1)
	{
		return true;
	}

	return false;
}

Vector2 GameScene::GetPlayerPos(void)
{
	return player_->GetPos();
}

void GameScene::CameraMove(void)
{

	// �v���C���[�̈ʒu���擾
	Vector2 playerPos = player_->GetPos();

	// �v���C���[�̈ʒu�ƃJ�����̈ʒu�̍��������
	int diffX = playerPos.x - cameraPos_.x;
	int diffY = playerPos.y - cameraPos_.y;


	// �J�����̍��[�̏���
	if (diffX < CAMERA_WIDTH)
	{
		cameraPos_.x -= CAMERA_WIDTH - diffX;
	}

	// �J�����̉E�[�̏���
	if (diffX > Application::SCREEN_SIZE_X - CAMERA_WIDTH)
	{
		cameraPos_.x -= Application::SCREEN_SIZE_X - CAMERA_WIDTH - diffX;
	}

	// �J�����̏�[�̘g����
	if (diffY < CAMERA_HEIGHT)
	{
		cameraPos_.y -= CAMERA_HEIGHT - diffY;
	}

	// �J�����̉��[�̏���
	if (diffY > Application::SCREEN_SIZE_Y - CAMERA_HEIGHT)
	{
		cameraPos_.y -= Application::SCREEN_SIZE_Y - CAMERA_HEIGHT - diffY;
	}

	// �J�����ʒu�̐���
	int mapSizeX = Stage::MAP_MAX_SIZE_X;
	int mapSizeY = Stage::MAP_MAX_SIZE_Y;	// +3��UI�摜�̕�
	int maxPos = 0;

	// �E�[����
	maxPos = mapSizeX * Stage::CHIP_SIZE_X - Application::SCREEN_SIZE_X;
	if (cameraPos_.x > maxPos)
	{
		cameraPos_.x = maxPos;
	}

	// ���[����
	if (cameraPos_.x < 0)
	{
		cameraPos_.x = 0;
	}

	// ��[����
	maxPos = mapSizeY * Stage::CHIP_SIZE_Y - Application::SCREEN_SIZE_Y;
	if (cameraPos_.y > maxPos)
	{
		cameraPos_.y = maxPos;
	}

	// ���[����
	if (cameraPos_.y < 0)
	{
		cameraPos_.y = 0;
	}

	// �f�o�b�O�p
	CameraMoveDebug();

}

void GameScene::CameraMoveDebug(void)
{
	// WASD�ŃJ�������W���ړ������ĉ�����
	int SPEED_CAMERA = 8;

	if (CheckHitKey(KEY_INPUT_W))
	{
		cameraPos_.y -= SPEED_CAMERA;
	}

	if (CheckHitKey(KEY_INPUT_S))
	{
		cameraPos_.y += SPEED_CAMERA;
	}

	if (CheckHitKey(KEY_INPUT_A))
	{
		cameraPos_.x -= SPEED_CAMERA;
	}

	if (CheckHitKey(KEY_INPUT_D))
	{
		cameraPos_.x += SPEED_CAMERA;
	}

}

void GameScene::Collision(void)
{

	// �e���
	Vector2 shotPos = shot_->GetPos();
	Vector2 shotSize = { Shot::SHOT_SIZE_X, Shot::SHOT_SIZE_Y };

	// �v���C���[���
	Vector2 playerPos = player_->GetPos();
	Vector2 playerSize = { Player::SIZE_X, Player::SIZE_Y };

	// �Œ蒷��ϒ��Ɍ��炸�A
	// �Ώە���"�����`"�̏ꍇ�́A�K��for�����g�p���A
	// ���[�v����邱��

	// �G�̐����������[�v����
	size_t size = enemys_.size();
	for (int i = 0; i < size; i++)
	{
		// �G�̃|�C���^���ꎞ�ϐ��Ɋi�[(�������̂���)
		EnemyBase* tmpEnemy = enemys_[i];

		// �G�̐�������
		if (!tmpEnemy->IsGetAlive())
		{
			continue;
		}

		Vector2 enemyPos = tmpEnemy->GetPos().ToVector2();
		Vector2 enemySize = tmpEnemy->GetSize();

		// ���G(����)�ƃv���C���[(1��)�Ƃ̏Փ˔���
		if (player_->IsAlive())
		{
			if (IsCollisionRectCenter(playerPos, playerSize, enemyPos, enemySize))
			{

				// �v���C���[�Ƀ_���[�W��^����
				player_->Damage(1);

			}
		}

		// �v���C���[�̒e�ƓG�Ƃ̏Փ˔���
		if (shot_->IsShotState())
		{

			// ���S���W�ƃT�C�Y�ŋ�`���m�̏Փ˔�����s��
			if (IsCollisionRectCenter(shotPos, shotSize, enemyPos, enemySize))
			{
				// ���x�����ƂɍU���͂�ς���
				if (player_->GetLevel() == 1)
				{
					// �G�Ƀ_���[�W��^����
					tmpEnemy->Damage(10);

					// �e�̔���
					shot_->Blast(shot_->GetPos());

					// �Ō���
					PlaySoundMem(SE1Hit_, DX_PLAYTYPE_BACK, true);

				}

				if (player_->GetLevel() == 2)
				{
					// �G�Ƀ_���[�W��^����
					tmpEnemy->Damage(20);

					// �e�̔���
					shot_->Blast(shot_->GetPos());

					// �Ō���
					PlaySoundMem(SE2Hit_, DX_PLAYTYPE_BACK, true);

				}

				if (player_->GetLevel() == 3)
				{
					// �G�Ƀ_���[�W��^����
					tmpEnemy->Damage(30);

					// �e�̔���
					shot_->Blast(shot_->GetPos());

					// �Ō���
					PlaySoundMem(SE3Hit_, DX_PLAYTYPE_BACK, true);

				}

				if (player_->GetLevel() == 4)
				{
					// �G�Ƀ_���[�W��^����
					tmpEnemy->Damage(40);

					// �e�̔���
					shot_->Blast(shot_->GetPos());

					// �Ō���
					PlaySoundMem(SE4Hit_, DX_PLAYTYPE_BACK, true);

				}

				if (player_->GetLevel() == 5)
				{
					// �G�Ƀ_���[�W��^����
					tmpEnemy->Damage(50);

					// �e�̔���
					shot_->Blast(shot_->GetPos());

					// �Ō���
					PlaySoundMem(SE5Hit_, DX_PLAYTYPE_BACK, true);

				}

			}

			// �G�̐�������
			if (!tmpEnemy->IsGetAlive())
			{
				player_->Exp(tmpEnemy->GetExp());
			}

			// �v���C���[�̐�������
			if (!player_->IsAlive())
			{

				// for���𒆒f����
				break;

			}
		}

	}

	// �{�X
	Vector2 BossPos = enemyBoss_->GetPos();
	Vector2 BossSize = { EnemyBoss::SIZE_X, EnemyBoss::SIZE_Y };
	// �{�X�ƃv���C���[(1��)�Ƃ̏Փ˔���
	if (enemyBoss_->IsGetAlive())
	{
		if (IsCollisionRectCenter(playerPos, playerSize, BossPos, BossSize))
		{

			// �v���C���[�Ƀ_���[�W��^����
			player_->Damage(0.1f);

		}
		// �v���C���[�̒e�ƃ{�X�̏Փ˔���
		if (shot_->IsShotState())
		{

			if (IsCollisionRectCenter(shotPos, shotSize, BossPos, BossSize))
			{
				// ���x�����ƂɍU���͂�ς���
				if (player_->GetLevel() == 1)
				{
					// �G�Ƀ_���[�W��^����
					enemyBoss_->Damage(10);

					// �e�̔���
					shot_->Blast(shot_->GetPos());

					// �Ō���
					PlaySoundMem(SE1Hit_, DX_PLAYTYPE_BACK, true);

				}

				if (player_->GetLevel() == 2)
				{
					// �G�Ƀ_���[�W��^����
					enemyBoss_->Damage(20);

					// �e�̔���
					shot_->Blast(shot_->GetPos());

					// �Ō���
					PlaySoundMem(SE2Hit_, DX_PLAYTYPE_BACK, true);

				}

				if (player_->GetLevel() == 3)
				{
					// �G�Ƀ_���[�W��^����
					enemyBoss_->Damage(30);

					// �e�̔���
					shot_->Blast(shot_->GetPos());

					// �Ō���
					PlaySoundMem(SE3Hit_, DX_PLAYTYPE_BACK, true);

				}

				if (player_->GetLevel() == 4)
				{
					// �G�Ƀ_���[�W��^����
					enemyBoss_->Damage(40);

					// �e�̔���
					shot_->Blast(shot_->GetPos());

					// �Ō���
					PlaySoundMem(SE4Hit_, DX_PLAYTYPE_BACK, true);

				}

				if (player_->GetLevel() == 5)
				{
					// �G�Ƀ_���[�W��^����
					enemyBoss_->Damage(50);

					// �e�̔���
					shot_->Blast(shot_->GetPos());

					// �Ō���
					PlaySoundMem(SE5Hit_, DX_PLAYTYPE_BACK, true);

				}

			}

			if (IsCollisionRectCenter(shotPos, shotSize, BossPos, BossSize) && !enemyBoss_->IsGetAlive())
			{
				hitStopCnt_ = 60;

				slowCnt_ = 60;
			}
		}

		Vector2 eShotPos;
		Vector2 eShotSize;
		enemyShot_ = enemyBoss_->GetEnemyShot();
		eShotPos = enemyShot_->GetPos();
		eShotSize = { EnemyShot::E_SHOT_SIZE_X, EnemyShot::E_SHOT_SIZE_Y };

		// �v���C���[�ƓG�̒e�Ƃ̏Փ˔���
		if (enemyShot_->IsShotState())
		{
			// �G�̒e�ƃv���C���[�̓����蔻��
			if (IsCollisionRectCenter(eShotPos, eShotSize, playerPos, playerSize))
			{

				// �v���C���[�Ƀ_���[�W��^����
				player_->Damage(20);

				// �e�̔���
				enemyShot_->Blast(enemyShot_->GetPos());

				// �{�X�̑Ō���
				PlaySoundMem(SEBossHit_, DX_PLAYTYPE_BACK, true);

			}
		}
	}
}

bool GameScene::IsCollisionRect(Vector2 stPos1, Vector2 edPos1, Vector2 stPos2, Vector2 edPos2)
{

	// ��`���m�̏Փ˔���
	// ��`�P�̍������A��`�Q�̉E���傫��
	// ��`�Q�̍������A��`�P�̉E���傫��
	if (stPos1.x < edPos2.x
		&& stPos2.x < edPos1.x
		&& stPos1.y < edPos2.y
		&& stPos2.y < edPos1.y)
	{
		return true;
	}
	return false;

}

//Vector2 GameScene::GetBoxPos(void)
//{
//	return boxPos_;
//}


bool GameScene::GetKey1(void)
{
	return isKey1_;
}

bool GameScene::GetKey2(void)
{
	return isKey2_;
}

bool GameScene::GetKey3(void)
{
	return isKey3_;
}

bool GameScene::GetKey4(void)
{
	return isKey4_;
}

int GameScene::GetMinute(void)
{
	return minute_;
}

int GameScene::GetSecond(void)
{
	return second_;
}

bool GameScene::IsCollisionRectCenter(Vector2 centerPos1, Vector2 size1, Vector2 centerPos2, Vector2 size2)
{

	// ��`1(������W�A�E����W)
	Vector2 stPos1 = centerPos1;
	Vector2 edPos1 = centerPos1;
	Vector2 hSize1 = { size1.x / 2, size1.y / 2 };

	stPos1.x -= hSize1.x;
	stPos1.y -= hSize1.y;
	edPos1.x += hSize1.x;
	edPos1.y += hSize1.y;

	// ��`�Q(������W�A�E����W)
	Vector2 stPos2 = centerPos2;
	Vector2 edPos2 = centerPos2;
	Vector2 hSize2 = { size2.x / 2, size2.y / 2 };

	stPos2.x -= hSize2.x;
	stPos2.y -= hSize2.y;
	edPos2.x += hSize2.x;
	edPos2.y += hSize2.y;

	// ��`���m�̏Փ˔���
	// ��`�P�̍������A��`�Q�̉E���傫��
	// ��`�Q�̍������A��`�P�̉E���傫��
	if (IsCollisionRect(stPos1, edPos1, stPos2, edPos2))
	{
		return true;
	}
	return false;

}

Stage* GameScene::GetStage(void)
{
	return stage_;
}

Player* GameScene::GetPlayer(void)
{
	return player_;
}

void GameScene::ClearEnemys(void)
{

	size_t size = enemys_.size();
	for (int i = 0; i < size; i++)
	{
		enemys_[i]->Release();
		delete enemys_[i];
	}
	enemys_.clear();

}

void GameScene::SortEnemys(void)
{

	// �G�̃\�[�g�z����N���A
	sortEnemys_.clear();

	// �G�̃\�[�g����ݒ�
	EnemyBase* targetEnemy;
	bool isInsert;

	//// ���̂���|�C���^�ɕϊ�
	//bool* ptr = &isInsert;

	//// �|�C���^������̂ɕϊ�
	//bool* entity = *ptr;

	size_t size = enemys_.size();
	for (int i = 0; i < size; i++)
	{

		// �ǉ��Ώۂ̓G�L����
		targetEnemy = enemys_[i];

		isInsert = false;

		for (auto itr = sortEnemys_.begin(); itr != sortEnemys_.end(); itr++)
		{

			// �ǉ��ΏۃL�����̕����A����(Y���W��������)��������
			if ((*itr)->GetFootPosY() > targetEnemy->GetFootPosY())
			{
				// �z��̓r���ɑ}��(�ΏۃC�e���[�^�̑O�ɑ}��)
				sortEnemys_.insert(itr, targetEnemy);
				isInsert = true;
				break;
			}

		}

		if (!isInsert)
		{
			// �ǂ��ɂ���������Ȃ�������A�z��̍Ō�ɒǉ�
			sortEnemys_.emplace_back(targetEnemy);
		}

	}

}

void GameScene::TreasureChest(void)
{

	auto& ins = InputManager::GetInstance();
	auto pad = InputManager::JOYPAD_NO::PAD1;
	auto input = ins.IsPadBtnTrgDown(pad, InputManager::JOYPAD_BTN::DOWN);


	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_X) || input)
	{


		Vector2 pPos = player_->GetPos();

		Vector2 mapPos = World2MapPos(pPos);

		AsoUtility::DIR dir = player_->GetDir();

		switch (dir)
		{
		case AsoUtility::DIR::DOWN:
			mapPos.y += 1;
			break;
		case AsoUtility::DIR::LEFT:
			mapPos.x -= 1;
			break;
		case AsoUtility::DIR::RIGHT:
			mapPos.x += 1;
			break;
		case AsoUtility::DIR::UP:
			mapPos.y -= 1;
			break;
		}

		int object1 = stage_->GetSwitch1No(mapPos);
		int object2 = stage_->GetSwitch2No(mapPos);
		int object3 = stage_->GetSwitch3No(mapPos);
		int object4 = stage_->GetSwitch4No(mapPos);

		if (object1 == 168)
		{
			isKey1_ = true;

			// �h�A��SE
			PlaySoundMem(SEDoor_, DX_PLAYTYPE_BACK, true);

		}

		if (object2 == 169)
		{
			isKey2_ = true;

			// �h�A��SE
			PlaySoundMem(SEDoor_, DX_PLAYTYPE_BACK, true);

		}

		if (object3 == 170)
		{
			isKey3_ = true;

			// �h�A��SE
			PlaySoundMem(SEDoor_, DX_PLAYTYPE_BACK, true);

		}

		if (object4 == 171)
		{
			isKey4_ = true;

			// �h�A��SE
			PlaySoundMem(SEDoor_, DX_PLAYTYPE_BACK, true);

		}

		int door = stage_->GetDoorNo(mapPos);

		if (stage_->IsDoor1(door))
		{
			// �v���C���[�̑O�̓h�A1
			if (isKey1_)
			{
				openDoor1_ = true;
			}
		}

		if (stage_->IsDoor2(door))
		{
			// �v���C���[�̑O�̓h�A2
			if (isKey2_)
			{
				openDoor2_ = true;
			}
		}

		if (stage_->IsDoor3(door))
		{
			// �v���C���[�̑O�̓h�A3
			if (isKey3_)
			{
				openDoor3_ = true;
			}
		}

		if (stage_->IsDoor4(door))
		{
			// �v���C���[�̑O�̓h�A4
			if (isKey4_)
			{
				openDoor4_ = true;
			}
		}
	}
}

void GameScene::Actor(void)
{

	auto& ins = InputManager::GetInstance();
	auto pad = InputManager::JOYPAD_NO::PAD1;
	auto input = ins.IsPadBtnTrgDown(pad, InputManager::JOYPAD_BTN::LEFT);

	// �A�N�^�[�摜�̏��
	if (isKey1_ && !isActor1a_)
	{
		isActor1_ = true;
		isActor1a_ = true;
	}
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_C) && isKey1_ || input)
	{
		isActor1_ = false;

		// �A�N�^�[��SE
		PlaySoundMem(SEActor_, DX_PLAYTYPE_BACK, true);

	}

	// �A�N�^�[�摜�̏��
	if (isKey2_ && !isActor2a_)
	{
		isActor2_ = true;
		isActor2a_ = true;
	}
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_C) && isKey2_ || input)
	{
		isActor2_ = false;

		// �A�N�^�[��SE
		PlaySoundMem(SEActor_, DX_PLAYTYPE_BACK, true);

	}

	// �A�N�^�[�摜�̏��
	if (isKey3_ && !isActor3a_)
	{
		isActor3_ = true;
		isActor3a_ = true;
	}
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_C) && isKey3_ || input)
	{
		isActor3_ = false;

		// �A�N�^�[��SE
		PlaySoundMem(SEActor_, DX_PLAYTYPE_BACK, true);

	}

	// �A�N�^�[�摜�̏��
	if (isKey4_ && !isActor4a_)
	{
		isActor4_ = true;
		isActor4a_ = true;
	}
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_C) && isKey4_ || input)
	{
		isActor4_ = false;

		// �A�N�^�[��SE
		PlaySoundMem(SEActor_, DX_PLAYTYPE_BACK, true);

	}

}

void GameScene::GameClear(void)
{



}

void GameScene::BGM(void)
{



}

