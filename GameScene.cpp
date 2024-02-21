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

    // ステージの初期化
    stage_ = new Stage();
    stage_->Init(this);

	// プレイヤーの初期化
	player_ = new Player();
	player_->Init(this);

	// エネミーボスの初期化
	enemyBoss_ = new EnemyBoss();
	enemyBoss_->Init(this);

	// 弾の初期化
	shot_ = new Shot();
	shot_->Init(this);

	// スタートメッセージの初期化
	startMes_ = new StartMes();
	startMes_->Init(this);

	// エンカウンター初期化
	enCounter = 0;

    // カメラ座標の初期化
	cameraPos_.x = player_->GetPos().x - (Application::SCREEN_SIZE_X / 2);
    cameraPos_.y = player_->GetPos().y - (Application::SCREEN_SIZE_Y / 2);

	// アクター画像を読み込む
	Actorimg_ = LoadGraph("Image/Player/Actor1.png");

	// 鍵1の画像の初期化
	keyImage1_ = LoadGraph("Image/UI/key1.png");
	
	// 鍵2の画像の初期化
	keyImage2_ = LoadGraph("Image/UI/key2.png");

	// 鍵3の画像の初期化
	keyImage3_ = LoadGraph("Image/UI/key3.png");

	// 鍵4の画像の初期化
	keyImage4_ = LoadGraph("Image/UI/key4.png");

	// 画像の読み込み
	imgGameClear_ = LoadGraph("Image/UI/GameClear.png");

	// UIの矢の画像の読み込み
	ArrowBack_ = LoadGraph("Image/UI/ArrowBack.png");

	// UI用の武器の読み込み
	UIimgs_ = LoadGraph("Image/Player/IconArrow.png");

	// UI用の武器の読み込み
	UIimgs2_ = LoadGraph("Image/Player/IconArrow2.png");

	// UI用の武器の読み込み
	UIimgs3_ = LoadGraph("Image/Player/IconArrow3.png");

	// UI用の武器の読み込み
	UIimgs4_ = LoadGraph("Image/Player/IconArrow4.png");

	// UI用の武器の読み込み
	UIimgs5_ = LoadGraph("Image/Player/IconArrow5.png");

	// レベル1画像の読み込み
	Level1_ = LoadGraph("Image/UI/Level1.png");

	// レベル2画像の読み込み
	Level2_ = LoadGraph("Image/UI/Level2.png");

	// レベル3画像の読み込み
	Level3_ = LoadGraph("Image/UI/Level3.png");

	// レベル4画像の読み込み
	Level4_ = LoadGraph("Image/UI/Level4.png");

	// レベル5画像の読み込み
	Level5_ = LoadGraph("Image/UI/Level5.png");

	// レベル画像の背景
	LevelBack_ = LoadGraph("Image/UI/LevelBack.png");

	// 読み込むフォントファイルのパス
	LPCSTR font_path = "DotGothic16.ttf";

		// 一時的な描画領域
	tmpScreen_ = MakeScreen(
		Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, true);

	isKey1_ = false;
	isKey2_ = false;
	isKey3_ = false;
	isKey4_ = false;

	// 時間のカウンタの初期化
	timecnt_ = 0;

	// ゲームシーンのBGM
	bgmGameScene_ = LoadSoundMem("Music/ゲーム.ogg");

	// ゲームシーンのBGM再生
	PlaySoundMem(bgmGameScene_, DX_PLAYTYPE_LOOP, true);

	// 決定ボタンのSEの読み込み
	SEBotton_ = LoadSoundMem("Music/決定ボタン.mp3");

	// 決定ボタンのSEの読み込み
	SEActor_ = LoadSoundMem("Music/アクター.mp3");

	// 攻撃ボタンのSE
	SEAttack_ = LoadSoundMem("Music/攻撃.mp3");

	// 打撃音のSE
	SE1Hit_ = LoadSoundMem("Music/打撃レベル1.mp3");

	// 打撃音のSE
	SE2Hit_ = LoadSoundMem("Music/打撃レベル2.mp3");

	// 打撃音のSE
	SE3Hit_ = LoadSoundMem("Music/打撃レベル3.mp3");

	// 打撃音のSE
	SE4Hit_ = LoadSoundMem("Music/打撃レベル4.mp3");

	// 打撃音のSE
	SE5Hit_ = LoadSoundMem("Music/打撃レベル5.mp3");

	// ボスの打撃音のSE
	SEBossHit_ = LoadSoundMem("Music/ボスの打撃.mp3");

	// ドアのSE
	SEDoor_ = LoadSoundMem("Music/ドア.mp3");

}

void GameScene::Update(void)
{

	// スタートメッセージの更新
	startMes_->Update();

	// ヒットストップで処理中断
	if (hitStopCnt_ > 0)
	{
		hitStopCnt_--;
		return;
	}

	// スロー
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


							// カメラ操作
							CameraMove();

							// プレイヤーの更新
							player_->Update();

							// エネミーボスの更新
							enemyBoss_->Update();

							// エネミーの更新
							size_t size = enemys_.size();
							for (int i = 0; i < size; i++)
							{
								enemys_[i]->Update();
							}


							//弾の生成処理
							if (shot_->IsEnableCreate())
							{

								InputManager& ins = InputManager::GetInstance();

								// １フレーム前のマウスクリック状態
								isShotKeyOld_ = isShotKeyNew_;
								// 現在フレームのマウスクリック状態
								isShotKeyNew_ = ins.IsClickMouseLeft();

								// マウスを押し続けている間、弾が出続ける
								//if (CheckHitKey(KEY_INPUT_Z)||ins.IsClickMouseLeft())

								// マウスを押したときだけ、弾が出る(オリジナル)
								//if (CheckHitKey(KEY_INPUT_Z)||(isShotKeyNew_ == true && isShotKeyOld_ == false))

								auto info = ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1);
								// 左アナログキー
								info.AKeyLX;
								// 右アナログキー
								info.AKeyRX;

								auto pad = InputManager::JOYPAD_NO::PAD1;
								auto input = ins.IsPadBtnTrgDown(pad, InputManager::JOYPAD_BTN::RIGHT);

								// マウスを押したときだけ、弾が出る(InputManager)
								if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_Z) || input)
								{

									//弾の生成
									shot_->Create(player_->GetPos().ToVector2F(), player_->GetDir());

									// 攻撃音
									PlaySoundMem(SEAttack_, DX_PLAYTYPE_BACK, true);

								}

							}

							// 弾の更新
							shot_->Update();

							// エンカウント
							enCounter++;

							if (enCounter > ENCOUNT)
							{

								// エンカウントリセット
								enCounter = 0;

								// 敵をランダムに生成
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

								// ９つの部屋にランダムにスポーンさせる
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
									// 座標の設定
									e->SetPos(randPos.ToVector2F());
								}

								// 可変長配列の一番後ろに追加
								enemys_.push_back(e);

							}

							// 衝突処理
							Collision();



							// プレイヤーのHPがゼロになったらゲームオーバー
							if (!player_->IsAlive())
							{
								SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMEOVER, true);

								// ゲームシーンのBGM停止
								StopSoundMem(bgmGameScene_);
							}

							// スイッチの判定
							TreasureChest();
						}
							// 脱出ゲートに当たったらゲームクリア
							if (IsCollisionGate(player_->GetPos()) && enemyBoss_->GetHP() <= 0)
							{
								gameClear_ = true;



								auto& ins = InputManager::GetInstance();
								auto pad = InputManager::JOYPAD_NO::PAD1;
								auto input = ins.IsPadBtnTrgDown(pad, InputManager::JOYPAD_BTN::RIGHT);

								if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE) || input && gameClear_)
								{
									SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE, true);

									// ゲームシーンのBGM停止
									StopSoundMem(bgmGameScene_);
								}
							}

					}
				}
			}
		}
	}
	// アクターの判定
	Actor();

}

void GameScene::Draw(void)
{

	if (!gameClear_)
	{

		// 振動
		if (hitStopCnt_ > 0)
		{
			// 描画先のスクリーンを設定 ヒットストップ中は、
			SetDrawScreen(tmpScreen_);
		}

		// ステージの描画
		stage_->Draw();

		// プレイヤーの描画
		player_->Draw();

		// エネミーボスの描画
		enemyBoss_->Draw();

		// 敵の描画順をソートする
		//SortEnemys();
		sort(enemys_.begin(), enemys_.end(),
			[](EnemyBase* a, EnemyBase* b) {

				return a->GetFootPosY() < b->GetFootPosY();

			}
		);

		// 敵描画(奥から手前に描画していく)
		// 範囲for文
		//int cnt = 0;
		for (EnemyBase* enemy : enemys_)
		{
			//cnt++;
			enemy->Draw();
		}


		// 弾の描画
		shot_->Draw();

		// UIの描画
		DrawUI();

		  // スタートメッセージの描画
		startMes_->Draw();

		// 振動
		if (hitStopCnt_ > 0)
		{
			// 描画先のスクリーンを設定
			SetDrawScreen(DX_SCREEN_BACK);
			// 0 or 1
			int shake = hitStopCnt_ / 5 % 2;
			// 0 or 2 画像をバックバッファに書き込む
			shake *= 2;
			// -1 or 1 その際に書き込む位置を
			shake -= 1;
			// -5 or 5
			shake *= 5;
			DrawGraph(shake, shake, tmpScreen_, true);
		}
	}


	// ゲームクリア
	if (gameClear_)
	{
		fadeCnt_++;
		//SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeCnt_ < 255 ? 255 - fadeCnt_ : 0);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeCnt_);
		DrawGraph(0, 0, imgGameClear_, true);
		SetFontSize(50);	// 見やすさのため、フォントサイズを大きく
		ChangeFont("DotGothic16", DX_CHARSET_DEFAULT);
		DrawFormatString(250, 100, 0xffffff, "タイム:%d分%d秒", minute_, second_);
	}

}

void GameScene::DrawUI(void)
{

	if(startMes_->GetCnt() >= 240)
	// 時間
	if (!gameClear_)
	{
		timecnt_ += 1;

		second_ = timecnt_ / 60;
		if (second_ >= 59)
		{
			minute_++;
			timecnt_ = 0;
		}

		SetFontSize(40);	// 見やすさのため、フォントサイズを大きく
		DrawFormatString(0, 0, 0xffffff, "タイム:%d分%d秒", minute_, second_);

		// HPゲージの割合計算

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

		SetFontSize(20);	// 見やすさのため、フォントサイズを大きく
		ChangeFont("DotGothic16", DX_CHARSET_DEFAULT);
		DrawFormatString(10, Application::SCREEN_SIZE_Y - 75, 0x000000, "HP");

		// アクター画像の表示
		Vector2 pPos = { 0, 400 };
		if (isActor1_)
		{
			DrawBox(0, 400, 384, 500, 0x000000, true);
			DrawGraph(pPos.x, pPos.y, Actorimg_, true);
			DrawFormatString(100, 420, 0xffffff, "扉が開いたようだ");
		}

		if (isActor2_)
		{
			DrawBox(0, 400, 384, 500, 0x000000, true);
			DrawGraph(pPos.x, pPos.y, Actorimg_, true);
			DrawFormatString(100, 420, 0xffffff, "扉が開いたようだ");
		}

		if (isActor3_)
		{
			DrawBox(0, 400, 384, 500, 0x000000, true);
			DrawGraph(pPos.x, pPos.y, Actorimg_, true);
			DrawFormatString(100, 420, 0xffffff, "扉が開いたようだ");
		}

		if (isActor4_)
		{
			DrawBox(0, 400, 384, 500, 0x000000, true);
			DrawGraph(pPos.x, pPos.y, Actorimg_, true);
			DrawFormatString(100, 420, 0xffffff, "扉が開いたようだ");
		}

		// レベルの取得
		int level = player_->GetLevel();

		// UIの矢の画像の背景
		DrawGraph(600, 500, ArrowBack_, true);

		// UIの矢1の画像
		if (level == 1)
		{
			DrawGraph(617, 517 , UIimgs_, true);
		}

		// UIの矢2の画像
		if (level == 2)
		{
			DrawGraph(617, 517, UIimgs2_, true);
		}

		// UIの矢3の画像
		if (level == 3)
		{
			DrawGraph(617, 517, UIimgs3_, true);
		}

		// UIの矢4の画像
		if (level == 4)
		{
			DrawGraph(617, 517, UIimgs4_, true);
		}

		// UIの矢5の画像
		if (level == 5)
		{
			DrawGraph(617, 517, UIimgs5_, true);
		}

		// レベル画像の背景
		DrawGraph(475, 525, LevelBack_, true);

		// レベル1の画像
		if (level == 1)
		{
			DrawGraph(475, 525, Level1_, true);
		}

		// レベル2の画像
		if (level == 2)
		{
			DrawGraph(475, 525, Level2_, true);
		}

		// レベル3の画像
		if (level == 3)
		{
			DrawGraph(475, 525, Level3_, true);
		}

		// レベル4の画像
		if (level == 4)
		{
			DrawGraph(475, 525, Level4_, true);
		}

		// レベル5の画像
		if (level == 5)
		{
			DrawGraph(475, 525, Level5_, true);
		}

	}

}


void GameScene::Release(void)
{

    // ステージ開放
    stage_->Release();
    delete stage_;

	// プレイヤー開放
	player_->Release();
	delete player_;

	// エネミーボスの開放
	enemyBoss_->Release();
	delete enemyBoss_;

	// エネミー開放
	size_t size = enemys_.size();
	for (int i = 0; i < size; i++)
	{
		enemys_[i]->Release();
		delete enemys_[i];
	}

	// 弾開放
	shot_->Release();
	delete shot_;

	// スタートメッセージの更新
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

	// ワールド座標からマップ座標に変換する
	Vector2 mapPos = World2MapPos(worldPos);

	// マップ座標からマップチップ番号を取得する
	int chipNo = stage_->GetCollisionStageNo(mapPos);

	if (chipNo != -1)
	{
		return true;
	}

	return false;
}

bool GameScene::IsCollisionDoor(Vector2 worldPos)
{

	// ワールド座標からマップ座標に変換する
	Vector2 mapPos = World2MapPos(worldPos);

	// マップ座標からマップチップ番号を取得する
	int chipNo = stage_->GetCollisionDoorNo(mapPos);

	if (chipNo != -1)
	{
		return true;
	}

	return false;
}

bool GameScene::IsCollisionGate(Vector2 worldPos)
{

	// ワールド座標からマップ座標に変換する
	Vector2 mapPos = World2MapPos(worldPos);

	// マップ座標からマップチップ番号を取得する
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

	// プレイヤーの位置を取得
	Vector2 playerPos = player_->GetPos();

	// プレイヤーの位置とカメラの位置の差分を取る
	int diffX = playerPos.x - cameraPos_.x;
	int diffY = playerPos.y - cameraPos_.y;


	// カメラの左端の処理
	if (diffX < CAMERA_WIDTH)
	{
		cameraPos_.x -= CAMERA_WIDTH - diffX;
	}

	// カメラの右端の処理
	if (diffX > Application::SCREEN_SIZE_X - CAMERA_WIDTH)
	{
		cameraPos_.x -= Application::SCREEN_SIZE_X - CAMERA_WIDTH - diffX;
	}

	// カメラの上端の枠処理
	if (diffY < CAMERA_HEIGHT)
	{
		cameraPos_.y -= CAMERA_HEIGHT - diffY;
	}

	// カメラの下端の処理
	if (diffY > Application::SCREEN_SIZE_Y - CAMERA_HEIGHT)
	{
		cameraPos_.y -= Application::SCREEN_SIZE_Y - CAMERA_HEIGHT - diffY;
	}

	// カメラ位置の制限
	int mapSizeX = Stage::MAP_MAX_SIZE_X;
	int mapSizeY = Stage::MAP_MAX_SIZE_Y;	// +3はUI画像の分
	int maxPos = 0;

	// 右端制限
	maxPos = mapSizeX * Stage::CHIP_SIZE_X - Application::SCREEN_SIZE_X;
	if (cameraPos_.x > maxPos)
	{
		cameraPos_.x = maxPos;
	}

	// 左端制限
	if (cameraPos_.x < 0)
	{
		cameraPos_.x = 0;
	}

	// 上端制限
	maxPos = mapSizeY * Stage::CHIP_SIZE_Y - Application::SCREEN_SIZE_Y;
	if (cameraPos_.y > maxPos)
	{
		cameraPos_.y = maxPos;
	}

	// 下端制限
	if (cameraPos_.y < 0)
	{
		cameraPos_.y = 0;
	}

	// デバッグ用
	CameraMoveDebug();

}

void GameScene::CameraMoveDebug(void)
{
	// WASDでカメラ座標を移動させて下さい
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

	// 弾情報
	Vector2 shotPos = shot_->GetPos();
	Vector2 shotSize = { Shot::SHOT_SIZE_X, Shot::SHOT_SIZE_Y };

	// プレイヤー情報
	Vector2 playerPos = player_->GetPos();
	Vector2 playerSize = { Player::SIZE_X, Player::SIZE_Y };

	// 固定長や可変長に限らず、
	// 対象物が"複数形"の場合は、必ずfor文を使用し、
	// ループを作ること

	// 敵の数分だけループを回す
	size_t size = enemys_.size();
	for (int i = 0; i < size; i++)
	{
		// 敵のポインタを一時変数に格納(高速化のため)
		EnemyBase* tmpEnemy = enemys_[i];

		// 敵の生存判定
		if (!tmpEnemy->IsGetAlive())
		{
			continue;
		}

		Vector2 enemyPos = tmpEnemy->GetPos().ToVector2();
		Vector2 enemySize = tmpEnemy->GetSize();

		// ■敵(複数)とプレイヤー(1体)との衝突判定
		if (player_->IsAlive())
		{
			if (IsCollisionRectCenter(playerPos, playerSize, enemyPos, enemySize))
			{

				// プレイヤーにダメージを与える
				player_->Damage(1);

			}
		}

		// プレイヤーの弾と敵との衝突判定
		if (shot_->IsShotState())
		{

			// 中心座標とサイズで矩形同士の衝突判定を行う
			if (IsCollisionRectCenter(shotPos, shotSize, enemyPos, enemySize))
			{
				// レベルごとに攻撃力を変える
				if (player_->GetLevel() == 1)
				{
					// 敵にダメージを与える
					tmpEnemy->Damage(10);

					// 弾の爆発
					shot_->Blast(shot_->GetPos());

					// 打撃音
					PlaySoundMem(SE1Hit_, DX_PLAYTYPE_BACK, true);

				}

				if (player_->GetLevel() == 2)
				{
					// 敵にダメージを与える
					tmpEnemy->Damage(20);

					// 弾の爆発
					shot_->Blast(shot_->GetPos());

					// 打撃音
					PlaySoundMem(SE2Hit_, DX_PLAYTYPE_BACK, true);

				}

				if (player_->GetLevel() == 3)
				{
					// 敵にダメージを与える
					tmpEnemy->Damage(30);

					// 弾の爆発
					shot_->Blast(shot_->GetPos());

					// 打撃音
					PlaySoundMem(SE3Hit_, DX_PLAYTYPE_BACK, true);

				}

				if (player_->GetLevel() == 4)
				{
					// 敵にダメージを与える
					tmpEnemy->Damage(40);

					// 弾の爆発
					shot_->Blast(shot_->GetPos());

					// 打撃音
					PlaySoundMem(SE4Hit_, DX_PLAYTYPE_BACK, true);

				}

				if (player_->GetLevel() == 5)
				{
					// 敵にダメージを与える
					tmpEnemy->Damage(50);

					// 弾の爆発
					shot_->Blast(shot_->GetPos());

					// 打撃音
					PlaySoundMem(SE5Hit_, DX_PLAYTYPE_BACK, true);

				}

			}

			// 敵の生存判定
			if (!tmpEnemy->IsGetAlive())
			{
				player_->Exp(tmpEnemy->GetExp());
			}

			// プレイヤーの生存判定
			if (!player_->IsAlive())
			{

				// for文を中断する
				break;

			}
		}

	}

	// ボス
	Vector2 BossPos = enemyBoss_->GetPos();
	Vector2 BossSize = { EnemyBoss::SIZE_X, EnemyBoss::SIZE_Y };
	// ボスとプレイヤー(1体)との衝突判定
	if (enemyBoss_->IsGetAlive())
	{
		if (IsCollisionRectCenter(playerPos, playerSize, BossPos, BossSize))
		{

			// プレイヤーにダメージを与える
			player_->Damage(0.1f);

		}
		// プレイヤーの弾とボスの衝突判定
		if (shot_->IsShotState())
		{

			if (IsCollisionRectCenter(shotPos, shotSize, BossPos, BossSize))
			{
				// レベルごとに攻撃力を変える
				if (player_->GetLevel() == 1)
				{
					// 敵にダメージを与える
					enemyBoss_->Damage(10);

					// 弾の爆発
					shot_->Blast(shot_->GetPos());

					// 打撃音
					PlaySoundMem(SE1Hit_, DX_PLAYTYPE_BACK, true);

				}

				if (player_->GetLevel() == 2)
				{
					// 敵にダメージを与える
					enemyBoss_->Damage(20);

					// 弾の爆発
					shot_->Blast(shot_->GetPos());

					// 打撃音
					PlaySoundMem(SE2Hit_, DX_PLAYTYPE_BACK, true);

				}

				if (player_->GetLevel() == 3)
				{
					// 敵にダメージを与える
					enemyBoss_->Damage(30);

					// 弾の爆発
					shot_->Blast(shot_->GetPos());

					// 打撃音
					PlaySoundMem(SE3Hit_, DX_PLAYTYPE_BACK, true);

				}

				if (player_->GetLevel() == 4)
				{
					// 敵にダメージを与える
					enemyBoss_->Damage(40);

					// 弾の爆発
					shot_->Blast(shot_->GetPos());

					// 打撃音
					PlaySoundMem(SE4Hit_, DX_PLAYTYPE_BACK, true);

				}

				if (player_->GetLevel() == 5)
				{
					// 敵にダメージを与える
					enemyBoss_->Damage(50);

					// 弾の爆発
					shot_->Blast(shot_->GetPos());

					// 打撃音
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

		// プレイヤーと敵の弾との衝突判定
		if (enemyShot_->IsShotState())
		{
			// 敵の弾とプレイヤーの当たり判定
			if (IsCollisionRectCenter(eShotPos, eShotSize, playerPos, playerSize))
			{

				// プレイヤーにダメージを与える
				player_->Damage(20);

				// 弾の爆発
				enemyShot_->Blast(enemyShot_->GetPos());

				// ボスの打撃音
				PlaySoundMem(SEBossHit_, DX_PLAYTYPE_BACK, true);

			}
		}
	}
}

bool GameScene::IsCollisionRect(Vector2 stPos1, Vector2 edPos1, Vector2 stPos2, Vector2 edPos2)
{

	// 矩形同士の衝突判定
	// 矩形１の左よりも、矩形２の右が大きい
	// 矩形２の左よりも、矩形１の右が大きい
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

	// 矩形1(左上座標、右上座標)
	Vector2 stPos1 = centerPos1;
	Vector2 edPos1 = centerPos1;
	Vector2 hSize1 = { size1.x / 2, size1.y / 2 };

	stPos1.x -= hSize1.x;
	stPos1.y -= hSize1.y;
	edPos1.x += hSize1.x;
	edPos1.y += hSize1.y;

	// 矩形２(左上座標、右上座標)
	Vector2 stPos2 = centerPos2;
	Vector2 edPos2 = centerPos2;
	Vector2 hSize2 = { size2.x / 2, size2.y / 2 };

	stPos2.x -= hSize2.x;
	stPos2.y -= hSize2.y;
	edPos2.x += hSize2.x;
	edPos2.y += hSize2.y;

	// 矩形同士の衝突判定
	// 矩形１の左よりも、矩形２の右が大きい
	// 矩形２の左よりも、矩形１の右が大きい
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

	// 敵のソート配列をクリア
	sortEnemys_.clear();

	// 敵のソート情報を設定
	EnemyBase* targetEnemy;
	bool isInsert;

	//// 実体からポインタに変換
	//bool* ptr = &isInsert;

	//// ポインタから実体に変換
	//bool* entity = *ptr;

	size_t size = enemys_.size();
	for (int i = 0; i < size; i++)
	{

		// 追加対象の敵キャラ
		targetEnemy = enemys_[i];

		isInsert = false;

		for (auto itr = sortEnemys_.begin(); itr != sortEnemys_.end(); itr++)
		{

			// 追加対象キャラの方が、奥側(Y座標が小さい)だったら
			if ((*itr)->GetFootPosY() > targetEnemy->GetFootPosY())
			{
				// 配列の途中に挿入(対象イテレータの前に挿入)
				sortEnemys_.insert(itr, targetEnemy);
				isInsert = true;
				break;
			}

		}

		if (!isInsert)
		{
			// どこにも導入されなかったら、配列の最後に追加
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

			// ドアのSE
			PlaySoundMem(SEDoor_, DX_PLAYTYPE_BACK, true);

		}

		if (object2 == 169)
		{
			isKey2_ = true;

			// ドアのSE
			PlaySoundMem(SEDoor_, DX_PLAYTYPE_BACK, true);

		}

		if (object3 == 170)
		{
			isKey3_ = true;

			// ドアのSE
			PlaySoundMem(SEDoor_, DX_PLAYTYPE_BACK, true);

		}

		if (object4 == 171)
		{
			isKey4_ = true;

			// ドアのSE
			PlaySoundMem(SEDoor_, DX_PLAYTYPE_BACK, true);

		}

		int door = stage_->GetDoorNo(mapPos);

		if (stage_->IsDoor1(door))
		{
			// プレイヤーの前はドア1
			if (isKey1_)
			{
				openDoor1_ = true;
			}
		}

		if (stage_->IsDoor2(door))
		{
			// プレイヤーの前はドア2
			if (isKey2_)
			{
				openDoor2_ = true;
			}
		}

		if (stage_->IsDoor3(door))
		{
			// プレイヤーの前はドア3
			if (isKey3_)
			{
				openDoor3_ = true;
			}
		}

		if (stage_->IsDoor4(door))
		{
			// プレイヤーの前はドア4
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

	// アクター画像の状態
	if (isKey1_ && !isActor1a_)
	{
		isActor1_ = true;
		isActor1a_ = true;
	}
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_C) && isKey1_ || input)
	{
		isActor1_ = false;

		// アクターのSE
		PlaySoundMem(SEActor_, DX_PLAYTYPE_BACK, true);

	}

	// アクター画像の状態
	if (isKey2_ && !isActor2a_)
	{
		isActor2_ = true;
		isActor2a_ = true;
	}
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_C) && isKey2_ || input)
	{
		isActor2_ = false;

		// アクターのSE
		PlaySoundMem(SEActor_, DX_PLAYTYPE_BACK, true);

	}

	// アクター画像の状態
	if (isKey3_ && !isActor3a_)
	{
		isActor3_ = true;
		isActor3a_ = true;
	}
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_C) && isKey3_ || input)
	{
		isActor3_ = false;

		// アクターのSE
		PlaySoundMem(SEActor_, DX_PLAYTYPE_BACK, true);

	}

	// アクター画像の状態
	if (isKey4_ && !isActor4a_)
	{
		isActor4_ = true;
		isActor4a_ = true;
	}
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_C) && isKey4_ || input)
	{
		isActor4_ = false;

		// アクターのSE
		PlaySoundMem(SEActor_, DX_PLAYTYPE_BACK, true);

	}

}

void GameScene::GameClear(void)
{



}

void GameScene::BGM(void)
{



}

