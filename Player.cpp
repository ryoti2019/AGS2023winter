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

	// ゲームシーンの機能をいつでも使えるようにメンバ変数に格納
	gameScene_ = scene;

	int dirNum = static_cast<int>(AsoUtility::DIR::MAX);
	int allNum = NUM_ANIM * dirNum;
	// 分割された画像を読み込む
	LoadDivGraph("Image/Player/Player.png",
		allNum,
		NUM_ANIM,
		dirNum,
		SIZE_X,
		SIZE_Y,
		&imgs_[0][0]
	);

	// 座標の初期化
	pos_.x = Application::SCREEN_SIZE_X / 2;
	pos_.y = Application::SCREEN_SIZE_Y / 2;

	// 移動速度
	speed_ = SPEED_DEFAULT;

	// 向き
	dir_ = AsoUtility::DIR::DOWN;

	// アニメーションカウンタ
	cntAnim_ = 0;

	// アニメーション速度
	speedAnim_ = ANIM_SPEED_DEFAULT;

	// HP
	hpMax_ = 500;
	hp_ = hpMax_;

	// 生存判定
	isAlive_ = true;

	// レベル
	level_ = 1;

}

void Player::Update(void)
{
	auto& ins = InputManager::GetInstance();
	auto pad = InputManager::JOYPAD_NO::PAD1;

	// プレイヤーの衝突
	StageCollision();

	// レベル
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
		// 生存していなければ描画しない
		return;
	}

	// 最新ゲームシーンから、カメラの位置を取得
	Vector2 cameraPos = gameScene_->GetCameraPos();

	// アニメーションのチップ番号(0～2)を作る
	AnimData_[0] = 0;
	AnimData_[1] = 1;
	AnimData_[2] = 2;
	AnimData_[3] = 1;

	// プレイヤーの描画
	DrawGraph(pos_.x - SIZE_X / 2 - cameraPos.x, pos_.y - SIZE_Y / 2 - cameraPos.y, imgs_[static_cast<int>(dir_)][AnimData_[(cntAnim_ / 10) % 4]], true);
	
	//DrawFormatString(0, 0, 0xffffff, "exp = %d", exp_);
	//DrawFormatString(0, 15, 0xffffff, "level = %d", level_);
	DrawDebug();

}

void Player::Release(void)
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

	// HPを減らす ダメージ量分
	hp_ -= damage;

	//HPが０以下になったらプレイヤーを生存していないことにする
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

	//// 最新ゲームシーンから、カメラの位置を取得
	//Vector2 cameraPos = gameScene_->GetCameraPos();

	//// デバッグ用
	//DrawBox(pos_.x - 3 - cameraPos.x,
	//	pos_.y - 3 - cameraPos.y,
	//	pos_.x + 3 - cameraPos.x,
	//	pos_.y + 3 - cameraPos.y,
	//	0xff0000, true);

	//// オレンジ
	//int color = 0xff8c00;

	//// デバッグ用：足元衝突判定
	//Vector2 footPos = pos_;
	//footPos.y += 20;

	//// デバッグ用：足元左衝突判定
	//Vector2 leftFootPos = pos_;
	//leftFootPos.x -= 10;
	//leftFootPos.y += 20;

	//// デバッグ用：足元右衝突判定
	//Vector2 rightFootPos = pos_;
	//rightFootPos.x += 10;
	//rightFootPos.y += 20;

	//// 足元：中央
	//DrawBox(footPos.x - 3 - cameraPos.x, footPos.y - 3 - cameraPos.y, 
	//	footPos.x + 3 - cameraPos.x, footPos.y + 3 - cameraPos.y, color, true);

	//// 足元：左
	//DrawBox(leftFootPos.x - 3 - cameraPos.x, leftFootPos.y - 3 - cameraPos.y,
	//	leftFootPos.x + 3 - cameraPos.x, leftFootPos.y + 3 - cameraPos.y, color, true);

	//// 足元：右
	//DrawBox(rightFootPos.x - 3 - cameraPos.x, rightFootPos.y - 3 - cameraPos.y,
	//	rightFootPos.x + 3 - cameraPos.x, rightFootPos.y + 3 - cameraPos.y, color, true);

}

void Player::StageCollision(void)
{
	// 移動前座標を確保
	Vector2 prePos = pos_;

	// 移動予定の座標を確保
	Vector2 movedPos = pos_;

	// 足元衝突判定
	Vector2 footPos;

	// 足元右衝突判定
	Vector2 rightFootPos;

	// 足元右衝突判定
	Vector2 leftFootPos;

	auto& ins = InputManager::GetInstance();
	auto inputState = ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1);

	// 移動処理(Y)
	if (ins.IsNew(KEY_INPUT_UP) || inputState.AKeyLY < 0.0f)
	{
		// 上移動
		movedPos.y -= speed_;

		// 向きの変更
		dir_ = AsoUtility::DIR::UP;

		// アニメーションカウンタの進行
		cntAnim_++;
	}

	if (ins.IsNew(KEY_INPUT_DOWN) || inputState.AKeyLY > 0.0f)
	{
		// 下移動
		movedPos.y += speed_;

		// 向きの変更
		dir_ = AsoUtility::DIR::DOWN;

		// アニメーションカウンタの進行
		cntAnim_++;
	}

	// 衝突判定(Y)
	footPos = movedPos;
	footPos.y += 20;

	leftFootPos = movedPos;
	leftFootPos.x -= 10;
	leftFootPos.y += 20;

	rightFootPos = movedPos;
	rightFootPos.x += 10;
	rightFootPos.y += 20;

	// ステージの衝突判定
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
			// 移動可能と判断できたので、現座標を更新
			pos_ = movedPos;
			//return;
		}

		if (
			(
				stage->IsDoor2(chipNo1) || stage->IsDoor2(chipNo2) || stage->IsDoor2(chipNo3) || stage->IsDoor2(chipNo4)
				)
			&& gameScene_->GetKey2())
		{
			// 移動可能と判断できたので、現座標を更新
			pos_ = movedPos;
			//return;
		}

		if (
			(
				stage->IsDoor3(chipNo1) || stage->IsDoor3(chipNo2) || stage->IsDoor3(chipNo3) || stage->IsDoor3(chipNo4)
				)
			&& gameScene_->GetKey3())
		{
			// 移動可能と判断できたので、現座標を更新
			pos_ = movedPos;
			//return;
		}

		if (
			(
				stage->IsDoor4(chipNo1) || stage->IsDoor4(chipNo2) || stage->IsDoor4(chipNo3) || stage->IsDoor4(chipNo4)
				)
			&& gameScene_->GetKey4())
		{
			// 移動可能と判断できたので、現座標を更新
			pos_ = movedPos;
			//return;
		}

		if (stage->IsGate(chipNo5) || stage->IsGate(chipNo6) || stage->IsGate(chipNo7) || stage->IsGate(chipNo8))
		{
			// 移動可能と判断できたので、現座標を更新
			pos_ = movedPos;
			//return;
		}

		// 衝突している -> 座標を元に戻す
		movedPos = pos_;
		//return;
	}

	else
	{
		// 移動可能と判断できたので、現座標を更新
		pos_ = movedPos;
	}


	// 移動処理(X)
	if (ins.IsNew(KEY_INPUT_LEFT) || inputState.AKeyLX < 0.0f)
	{
		// 左移動
		movedPos.x -= speed_;

		// 向きの変更
		dir_ = AsoUtility::DIR::LEFT;

		// アニメーションカウンタの進行
		cntAnim_++;
	}

	if (ins.IsNew(KEY_INPUT_RIGHT) || inputState.AKeyLX > 0.0f)
	{
		// 右移動
		movedPos.x += speed_;

		// 向きの変更
		dir_ = AsoUtility::DIR::RIGHT;

		// アニメーションカウンタの進行
		cntAnim_++;
	}

	// 衝突判定(X)
	footPos = movedPos;
	footPos.y += 20;

	leftFootPos = movedPos;
	leftFootPos.x -= 10;
	leftFootPos.y += 20;

	rightFootPos = movedPos;
	rightFootPos.x += 10;
	rightFootPos.y += 20;

	// ステージの衝突判定
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
			// 移動可能と判断できたので、現座標を更新
			pos_ = movedPos;
			//return;
		}

		if (
			(
				stage->IsDoor2(chipNo1) || stage->IsDoor2(chipNo2) || stage->IsDoor2(chipNo3) || stage->IsDoor2(chipNo4)
				)
			&& gameScene_->GetKey2())
		{
			// 移動可能と判断できたので、現座標を更新
			pos_ = movedPos;
			//return;
		}

		if (
			(
				stage->IsDoor3(chipNo1) || stage->IsDoor3(chipNo2) || stage->IsDoor3(chipNo3) || stage->IsDoor3(chipNo4)
				)
			&& gameScene_->GetKey3())
		{
			// 移動可能と判断できたので、現座標を更新
			pos_ = movedPos;
			//return;
		}

		if (
			(
				stage->IsDoor4(chipNo1) || stage->IsDoor4(chipNo2) || stage->IsDoor4(chipNo3) || stage->IsDoor4(chipNo4)
				)
			&& gameScene_->GetKey4())
		{
			// 移動可能と判断できたので、現座標を更新
			pos_ = movedPos;
			//return;
		}

		if (stage->IsGate(chipNo5) || stage->IsGate(chipNo6) || stage->IsGate(chipNo7) || stage->IsGate(chipNo8))
		{
			// 移動可能と判断できたので、現座標を更新
			pos_ = movedPos;
			//return;
		}

		// 衝突している -> 座標を元に戻す
		movedPos = pos_;
		//return;
	}

	else
	{
		// 移動可能と判断できたので、現座標を更新
		pos_ = movedPos;
	}

	// 移動量によって向きを判定する
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

	// 経験値が一定の値に達したらレベルを上げる
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
