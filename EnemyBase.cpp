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

	// ゲームシーンの機能をいつでも使えるようにメンバ変数に格納
	gameScene_ = scene;

	// 敵キャラ個別のパラメータ設定
	SetParam();

	int dirNum = static_cast<int>(AsoUtility::DIR::MAX);
	int allNum = NUM_ANIM * dirNum;

	std::string path = "Image/Enemy/";
	path = path + imgFileName_;

	// 分割された画像を読み込む
	LoadDivGraph(path.c_str(),
		allNum,
		NUM_ANIM,
		dirNum,
		size_.x,
		size_.y,
		&imgs_[0][0]
	);

	// 座標の初期化
	pos_.x = 400;
	pos_.y = 400;

	// 向き
	dir_ = AsoUtility::DIR::DOWN;

	// アニメーションカウンタ
	cntAnim_ = 0;

	// 敵の生存
	isAlive_ = true;

}

void EnemyBase::SetParam(void)
{
}

void EnemyBase::Update(void)
{
	// ステージの衝突
	StageCollision();

	// アニメーションカウンタの進行
	cntAnim_++;

}

void EnemyBase::Draw(void)
{

	if (!isAlive_)
	{
		// 生存していなければ描画しない
		return;
	}

	// 最新ゲームシーンから、カメラの位置を取得
	Vector2 cameraPos = gameScene_->GetCameraPos();

	// アニメーションのチップ番号(0～3)を作る
	int animNo = static_cast<int>(static_cast<float>(cntAnim_) * speedAnim_) % NUM_ANIM;

	Vector2 pos = AsoUtility::Round(pos_);
	DrawGraph(pos_.x - size_.x / 2 - cameraPos.x,
		pos_.y - size_.y / 2 - cameraPos.y,
		imgs_[static_cast<int>(dir_)][animNo], true);

}

void EnemyBase::Release(void)
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

	// HPを減らす ダメージ量分
	hp_ -= damage;

	// HPが０以下になったら敵を生存していないことにする
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

	if (size < 320)
	{
		if (size > 0)
		{

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
	}
}

bool EnemyBase::IsStageCollision(Vector2F movedPos)
{

	bool retX = true;
	bool retY = true;

	// 足元座標の宣言
	Vector2 footPos;

	// 衝突判定(Y)
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

	return retY || retX;

}

Vector2F EnemyBase::Move(Vector2F dir)
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
