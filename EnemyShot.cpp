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

	// ゲームシーンの機能をいつでも使えるようにメンバ変数に格納
	gameScene_ = scene;

	// 分割された画像を読み込む
	LoadDivGraph("Image/Enemy/Shot.png",
		E_SHOT_ANIM_NUM,
		E_SHOT_ANIM_NUM,
		1,
		E_SHOT_SIZE_X,
		E_SHOT_SIZE_Y,
		&imgs_[0]
	);

	// 爆発エフェクト読み込み
	LoadDivGraph("Image/Player/Blast.png",
		BLAST_ANIM_NUM,
		4,
		4,
		BLAST_SIZE_X,
		BLAST_SIZE_Y,
		blastImgs_
	);

	// 弾の生存時間
	cntAlive_ = 0;

	// 弾のスピード
	speed_ = 5.0f;

	// 弾のアニメーション用カウンタ
	cntAnim_ = 0;

	// 弾のアニメーション速度
	speedAnim_ = 0.2f;

	// 爆発のアニメーション速度
	blastSpeedAnim_ = 0.5f;

	// 爆発アニメーション用カウンタ
	blastCntAnim_ = 0;

	// 状態の初期化
	state_ = STATE::NONE;

	// ボスの打撃音のSE
	SEBossHit_ = LoadSoundMem("Music/ボスの打撃.mp3");

}

void EnemyShot::Update(void)
{

	// 弾とステージの衝突判定
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

	// 弾の移動
	// 移動量とは、方向×スピード(力、スカラー)
	int movePowX = dir_.x * speed_;
	int movePowY = dir_.y * speed_;

	// 移動とは、座標＋移動量
	pos_.x += movePowX;
	pos_.y += movePowY;

	// 弾の生存カウンタ制御
	// (一旦、生存時間が過ぎたら、END状態へ遷移)
	cntAlive_--;
	if (cntAlive_ < 0)
	{
		cntAlive_ = 0;

		// 爆発させる
		Blast(pos_);

		// ボスの打撃音
		PlaySoundMem(SEBossHit_, DX_PLAYTYPE_BACK, true);

	}

	// 弾のアニメーション
	cntAnim_++;

	// 弾のアニメーション番号(0～1)

	idxAnim_ = static_cast<int>(static_cast<float>(cntAnim_) * speedAnim_) % E_SHOT_ANIM_NUM;

}

void EnemyShot::UpdateBlast(void)
{

	// 爆発のアニメーション
	blastCntAnim_++;

	// 爆発のアニメーション番号
	blastIdxAnim_ = static_cast<int>(static_cast<float>(blastCntAnim_) * blastSpeedAnim_) % BLAST_ANIM_NUM;

	// 爆発のアニメーションの終了判定
	if (blastIdxAnim_ + 1 >= BLAST_ANIM_NUM)
	{
		ChangeState(STATE::END);
	}

}

void EnemyShot::UpdateEnd(void)
{

	// 弾の消失判定
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

	// カメラ座標
	Vector2 cameraPos = gameScene_->GetCameraPos();

	// 弾の描画
	Vector2 pos = pos_.ToVector2();
	DrawGraph(pos.x - E_SHOT_SIZE_X / 2 - cameraPos.x, pos.y - E_SHOT_SIZE_X / 2 - cameraPos.y, imgs_[idxAnim_], true);

}

void EnemyShot::DrawBlast(void)
{

	// カメラ座標
	Vector2 cameraPos = gameScene_->GetCameraPos();

	// 弾の描画
	Vector2 pos = blastPos_.ToVector2();
	DrawGraph(pos.x - BLAST_SIZE_X / 2 - cameraPos.x, pos.y - BLAST_SIZE_X / 2 - cameraPos.y, blastImgs_[blastIdxAnim_], true);

}

void EnemyShot::DrawEnd(void)
{

}

void EnemyShot::Release(void)
{

	// 読み込んだ画像の開放
	for (int i = 0; i < E_SHOT_ANIM_NUM; i++)
	{
		DeleteGraph(imgs_[i]);
	}

	// 読み込んだ画像の開放
	for (int i = 0; i < BLAST_ANIM_NUM; i++)
	{
		DeleteGraph(blastImgs_[i]);
	}


}

void EnemyShot::Create(Vector2F pos, Vector2F dir)
{
	// 生存時間の設定
	cntAlive_ = SHOT_CNT_ALIVE;

	// 弾の発射位置
	pos_ = pos;

	// 弾の方向
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
	// 状態の更新
	state_ = state;

	// 状態遷移時の初期化
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

	// 弾情報
	Vector2 shotPos = pos_;

	// ステージの衝突判定
	if (gameScene_->IsCollisionStage(shotPos) == true
		|| gameScene_->IsCollisionDoor(shotPos) == true)
	{

		Stage* stage = gameScene_->GetStage();

		Vector2 mapPos1 = gameScene_->World2MapPos(shotPos);

		int chipNo1 = stage->GetDoorNo(mapPos1);

		if ((stage->IsDoor1(chipNo1)) && gameScene_->GetKey1())
		{
			// 移動可能と判断できたので、現座標を更新
			pos_ = shotPos;
			return;
		}

		if ((stage->IsDoor2(chipNo1)) && gameScene_->GetKey2())
		{
			// 移動可能と判断できたので、現座標を更新
			pos_ = shotPos;
			return;
		}

		if ((stage->IsDoor3(chipNo1)) && gameScene_->GetKey3())
		{
			// 移動可能と判断できたので、現座標を更新
			pos_ = shotPos;
			return;
		}

		if ((stage->IsDoor4(chipNo1)) && gameScene_->GetKey4())
		{
			// 移動可能と判断できたので、現座標を更新
			pos_ = shotPos;
			return;
		}

		// 衝突している -> 座標を元に戻す
		shotPos = pos_;

		// 衝突したら弾の生存時間をゼロにする
		cntAlive_ = 0.0f;

	}
	else
	{
		// 移動可能と判断できたので、現座標を更新
		pos_ = shotPos;
	}


}
