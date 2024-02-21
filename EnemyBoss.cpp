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

	// ゲームシーンの機能をいつでも使えるようにメンバ変数に格納
	gameScene_ = scene;

	// 弾の初期化
	enemyShot_ = new EnemyShot();
	enemyShot_->Init(scene);

	int dirNum = static_cast<int>(AsoUtility::DIR::MAX);
	int allNum = NUM_ANIM * dirNum;
	// 分割された画像を読み込む
	LoadDivGraph("Image/Enemy/StormGiant.png",
		allNum,
		NUM_ANIM,
		dirNum,
		SIZE_X,
		SIZE_Y,
		&imgs_[0][0]
	);

	// 座標の初期化
	pos_.x = 368;
	pos_.y = 1840;

	// 移動速度
	speed_ = SPEED_DEFAULT;

	// 向き
	dir_ = AsoUtility::DIR::DOWN;

	// アニメーションカウンタ
	cntAnim_ = 0;

	// アニメーション速度
	speedAnim_ = ANIM_SPEED_DEFAULT;

	// HP
	hpMax_ = 300;
	hp_ = hpMax_;

	// 生存判定
	isAlive_ = true;

	// ボスの攻撃音のSE
	SEBossAttack_ = LoadSoundMem("Music/ボスの攻撃.mp3");

}

void EnemyBoss::Update(void)
{

	// プレイヤーの位置を取得
	Vector2 pPos = gameScene_->GetPlayerPos();

	if (isAlive_)
	{

		// ステージの衝突
		StageCollision();

		// アニメーションカウンタの進行
		cntAnim_++;

		//弾の生成処理
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
					//弾の生成 
					enemyShot_->Create(pos_, dir);

					// ボスの打撃音
					PlaySoundMem(SEBossAttack_, DX_PLAYTYPE_BACK, true);

				}
			}
		}


		// 弾の更新
		enemyShot_->Update();
	}
}

void EnemyBoss::Draw(void)
{

	if (isAlive_)
	{


		// 最新ゲームシーンから、カメラの位置を取得
		Vector2 cameraPos = gameScene_->GetCameraPos();

		// アニメーションのチップ番号(0～8)を作る
		int animNo = static_cast<int>(static_cast<float>(cntAnim_) * speedAnim_) % NUM_ANIM;

		DrawGraph(pos_.x - SIZE_X / 2 - cameraPos.x,
			pos_.y - SIZE_Y / 2 - cameraPos.y,
			imgs_[static_cast<int>(dir_)][animNo], true);

		// 弾の描画
		enemyShot_->Draw();
	}
}

void EnemyBoss::Release(void)
{

	int dirNum = static_cast<int>(AsoUtility::DIR::MAX);

	// 読み込んだ画像の開放
	for (int y = 0; y < dirNum; y++)
	{
		for (int x = 0; x < NUM_ANIM; x++)
		{
			DeleteGraph(imgs_[y][x]);
		}
	}

	// 敵の弾開放
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

	// HPを減らす ダメージ量分
	hp_ -= damage;

	//HPが０以下になったらプレイヤーを生存していないことにする
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

	// プレイヤーの位置を取得
	Vector2 pPos = gameScene_->GetPlayerPos();

	// プレイヤーに向けたベクトル
	Vector2F vec;
	vec.x = static_cast<float>(pPos.x - pos_.x);
	vec.y = static_cast<float>(pPos.y - pos_.y);

	// 移動前座標を確保
	Vector2F prePos = pos_;

	// 移動予定の座標を確保
	Vector2F movedPos = pos_;


	// ベクトルの大きさ
	float size = sqrtf(vec.x * vec.x + vec.y * vec.y);


	if (size < 16)
	{
		// 近すぎるので移動しない
		return;
	}



	// 移動方向を決める
	Vector2F direction;
	direction.x = vec.x / size;
	direction.y = vec.y / size;

	// 移動後座標を計算する
	movedPos = Move(direction);

	// 衝突のチェック
	if (IsStageCollision(movedPos))
	{
		Vector2F directionX;
		// 衝突した
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
			// 衝突した
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

	// 足元座標の宣言
	Vector2 footPos;

	// 衝突判定(Y)
	footPos = movedPos;
	footPos.y += 20;

	if (gameScene_->GetKey1() && gameScene_->GetKey2() && gameScene_->GetKey3() && gameScene_->GetKey4())
	{
		// ステージの衝突判定
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
				// 移動可能と判断できたので、現座標を更新
				pos_ = movedPos;
				retY = false;
			}

			if ((stage->IsDoor2(chipNo1) || stage->IsDoor2(chipNo2))
				&& gameScene_->GetKey2())
			{
				// 移動可能と判断できたので、現座標を更新
				pos_ = movedPos;
				retY = false;
			}

			if ((stage->IsDoor3(chipNo1) || stage->IsDoor3(chipNo2))
				&& gameScene_->GetKey3())
			{
				// 移動可能と判断できたので、現座標を更新
				pos_ = movedPos;
				retY = false;
			}

			if ((stage->IsDoor4(chipNo1) || stage->IsDoor4(chipNo2))
				&& gameScene_->GetKey4())
			{
				// 移動可能と判断できたので、現座標を更新
				pos_ = movedPos;
				retY = false;
			}

			// 衝突している -> 座標を元に戻す
			movedPos = pos_;

		}
		else
		{
			// 移動可能と判断できたので、現座標を更新
			pos_ = movedPos;
			retY = false;
		}

		// 衝突判定(X)
		footPos = movedPos;
		footPos.y += 20;

		// ステージの衝突判定
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
				// 移動可能と判断できたので、現座標を更新
				pos_ = movedPos;
				retX = false;
			}

			if ((stage->IsDoor2(chipNo1) || stage->IsDoor2(chipNo2))
				&& gameScene_->GetKey2())
			{
				// 移動可能と判断できたので、現座標を更新
				pos_ = movedPos;
				retX = false;
			}

			if ((stage->IsDoor3(chipNo1) || stage->IsDoor3(chipNo2))
				&& gameScene_->GetKey3())
			{
				// 移動可能と判断できたので、現座標を更新
				pos_ = movedPos;
				retX = false;
			}

			if ((stage->IsDoor4(chipNo1) || stage->IsDoor4(chipNo2))
				&& gameScene_->GetKey4())
			{
				// 移動可能と判断できたので、現座標を更新
				pos_ = movedPos;
				retX = false;
			}

			// 衝突している -> 座標を元に戻す
			movedPos = pos_;
		}

		else
		{
			// 移動可能と判断できたので、現座標を更新
			pos_ = movedPos;
			retX = false;
		}
	}
	return retY || retX;

}

Vector2F EnemyBoss::Move(Vector2F dir)
{

	// 移動予定の座標を確保
	Vector2F movedPos = pos_;

	// 移動量
	Vector2F movePow;
	movePow.x = dir.x * speed_;
	movePow.y = dir.y * speed_;

	// 移動処理(座標+移動量)
	movedPos.x += (movePow.x);
	movedPos.y += (movePow.y);

	// 向きを変える(移動量が大きい向きを優先)
	if (abs(dir.x) > abs(dir.y))
	{
		// 左向きか右向きか
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
