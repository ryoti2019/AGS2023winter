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

	// ゲームシーンの機能をいつでも使えるようにメンバ変数に格納
	gameScene_ = scene;

	// 分割された画像を読み込む
	LoadDivGraph("Image/Player/arrow.png",
		SHOT_NUM,
		SHOT_NUM_X,
		SHOT_NUM_Y,
		SHOT_SIZE_X,
		SHOT_SIZE_Y,
		&imgs_[0]
	);

	// 分割された画像を読み込む
	LoadDivGraph("Image/Player/arrow2.png",
		SHOT_NUM,
		SHOT_NUM_X,
		SHOT_NUM_Y,
		SHOT_SIZE_X,
		SHOT_SIZE_Y,
		&imgs2_[0]
	);

	// 分割された画像を読み込む
	LoadDivGraph("Image/Player/arrow3.png",
		SHOT_NUM,
		SHOT_NUM_X,
		SHOT_NUM_Y,
		SHOT_SIZE_X,
		SHOT_SIZE_Y,
		&imgs3_[0]
	);

	// 分割された画像を読み込む
	LoadDivGraph("Image/Player/arrow4.png",
		SHOT_NUM,
		SHOT_NUM_X,
		SHOT_NUM_Y,
		SHOT_SIZE_X,
		SHOT_SIZE_Y,
		&imgs4_[0]
	);

	// 分割された画像を読み込む
	LoadDivGraph("Image/Player/arrow5.png",
		SHOT_NUM,
		SHOT_NUM_X,
		SHOT_NUM_Y,
		SHOT_SIZE_X,
		SHOT_SIZE_Y,
		&imgs5_[0]
	);

	// 爆発エフェクト読み込み
	LoadDivGraph("Image/Player/Blast1.png",
		BLAST_ANIM_NUM,
		4,
		1,
		BLAST_SIZE_X,
		BLAST_SIZE_Y,
		blastImgs_
	);

	// 爆発エフェクト読み込み
	LoadDivGraph("Image/Player/Blast2.png",
		BLAST_ANIM_NUM,
		4,
		1,
		BLAST2_SIZE_X,
		BLAST2_SIZE_Y,
		blastImgs2_
	);

	// 爆発エフェクト読み込み
	LoadDivGraph("Image/Player/Blast3.png",
		BLAST_ANIM_NUM,
		4,
		1,
		BLAST3_SIZE_X,
		BLAST3_SIZE_Y,
		blastImgs3_
	);

	// 爆発エフェクト読み込み
	LoadDivGraph("Image/Player/Blast4.png",
		BLAST_ANIM_NUM,
		4,
		1,
		BLAST4_SIZE_X,
		BLAST4_SIZE_Y,
		blastImgs4_
	);

	// 爆発エフェクト読み込み
	LoadDivGraph("Image/Player/Blast5.png",
		BLAST_ANIM_NUM,
		4,
		1,
		BLAST5_SIZE_X,
		BLAST5_SIZE_Y,
		blastImgs5_
	);

	// 弾の生存時間
	cntAlive_ = 0;

	// 弾のスピード
	speed_ = 10.0f;

	// 爆発のアニメーション速度
	blastSpeedAnim_ = 0.2f;

	// 爆発アニメーション用カウンタ
	blastCntAnim_ = 0;

	// 状態の初期化
	state_ = STATE::NONE;

	// 打撃音1のSE
	SE1Hit_ = LoadSoundMem("Music/打撃レベル1.mp3");

	// 打撃音2のSE
	SE2Hit_ = LoadSoundMem("Music/打撃レベル2.mp3");

	// 打撃音3のSE
	SE3Hit_ = LoadSoundMem("Music/打撃レベル3.mp3");

	// 打撃音4のSE
	SE4Hit_ = LoadSoundMem("Music/打撃レベル4.mp3");

	// 打撃音5のSE
	SE5Hit_ = LoadSoundMem("Music/打撃レベル5.mp3");

}

void Shot::Update(void)
{

	// 弾とステージの衝突判定
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

	// 弾の移動
	// 移動量とは、方向×スピード(力、スカラー)
	int movePowX = dir_.x * speed_;
	int movePowY = dir_.y * speed_;

	// 移動とは、座標＋移動量
	pos_.x += movePowX;
	pos_.y += movePowY;

	// レベル
	Player* player = gameScene_->GetPlayer();

	int level = player->GetLevel();

	// 弾の生存カウンタ制御
	// (一旦、生存時間が過ぎたら、END状態へ遷移)
	cntAlive_--;
	if (cntAlive_ < 0)
	{
		cntAlive_ = 0;

		// 爆発させる
		Blast(pos_);

		if (level == 1)
		{
			// 打撃音
			PlaySoundMem(SE1Hit_, DX_PLAYTYPE_BACK, true);
		}

		if (level == 2)
		{
			// 打撃音
			PlaySoundMem(SE2Hit_, DX_PLAYTYPE_BACK, true);
		}

		if (level == 3)
		{
			// 打撃音
			PlaySoundMem(SE3Hit_, DX_PLAYTYPE_BACK, true);
		}

		if (level == 4)
		{
			// 打撃音
			PlaySoundMem(SE4Hit_, DX_PLAYTYPE_BACK, true);
		}

		if (level == 5)
		{
			// 打撃音
			PlaySoundMem(SE5Hit_, DX_PLAYTYPE_BACK, true);
		}
	}

}

void Shot::UpdateBlast(void)
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

void Shot::UpdateEnd(void)
{

	// 弾の消失判定
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

	// カメラ座標
	Vector2 cameraPos = gameScene_->GetCameraPos();

	// プレイヤーの取得
	Player* player = gameScene_->GetPlayer();

	// レベルの取得
	int level = player->GetLevel();

	// 矢の座標
	Vector2 pos = pos_.ToVector2();

	// 矢の描画
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

	// カメラ座標
	Vector2 cameraPos = gameScene_->GetCameraPos();

	// プレイヤーの取得
	Player* player = gameScene_->GetPlayer();

	// レベルの取得
	int level = player->GetLevel();

	// エフェクトの座標
	Vector2 pos = blastPos_.ToVector2();

	// エフェクトの描画
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

	// 読み込んだ画像の開放
	for (int i = 0; i < SHOT_NUM; i++)
	{
		DeleteGraph(imgs_[i]);
	}

	// 読み込んだ画像の開放
	for (int i = 0; i < SHOT_NUM; i++)
	{
		DeleteGraph(imgs2_[i]);
	}

	// 読み込んだ画像の開放
	for (int i = 0; i < BLAST_ANIM_NUM; i++)
	{
		DeleteGraph(blastImgs_[i]);
	}

}

void Shot::Create(Vector2F pos, AsoUtility::DIR dir)
{

	// 生存時間の設定
	cntAlive_ = SHOT_CNT_ALIVE;

	// 弾の発射位置
	pos_ = pos;

	shotDir_ = dir;


	// 移動
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

	// 状態の更新
	state_ = state;

	// 状態遷移時の初期化
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

	// 弾情報
	Vector2 shotPos = pos_;

	// ステージの衝突判定
	if (gameScene_->IsCollisionStage(shotPos) == true
		|| gameScene_->IsCollisionDoor(shotPos) == true)
	{

		Stage* stage = gameScene_->GetStage();

		Vector2 mapPos1 = gameScene_->World2MapPos(shotPos);

		int chipNo1 = stage->GetDoorNo(mapPos1);

		if ((stage->IsDoor1(chipNo1))&& gameScene_->GetKey1())
		{
			// 移動可能と判断できたので、現座標を更新
			pos_ = shotPos;
			return;
		}

		if ((stage->IsDoor2(chipNo1))&& gameScene_->GetKey2())
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
