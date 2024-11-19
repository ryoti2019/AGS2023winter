#include <DxLib.h>
#include "GameOverScene.h"
#include "SceneManager.h"
#include "Application.h"
#include "InputManager.h"

GameOverScene::GameOverScene(void)
{
}

GameOverScene::~GameOverScene(void)
{
}

void GameOverScene::Init(void)
{

	// 画像の読み込み
	imgGameOver_ = LoadGraph("Image/UI/GameOver.png");
	imgStart_ = LoadGraph("Image/UI/HitStartKey.png");

	// BGM
	bgm_ = LoadSoundMem("Music/ゲームオーバー.ogg");

	// BGM
	PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP, true);

	// 決定ボタンのSEの読み込み
	SEbotton_ = LoadSoundMem("Music/決定ボタン.mp3");

}

void GameOverScene::Update(void)
{

	SceneManager& sceneIns = SceneManager::GetInstance();
	auto& ins = InputManager::GetInstance();
	auto pad = InputManager::JOYPAD_NO::PAD1;
	auto input = ins.IsPadBtnTrgDown(pad, InputManager::JOYPAD_BTN::RIGHT);
	// タイトル画面に戻る
	if (CheckHitKey(KEY_INPUT_SPACE) || input)
	{
		PlaySoundMem(SEbotton_, DX_PLAYTYPE_BACK, false);
		// スペースキーが押下されたら、タイトルシーンへ遷移する
		sceneIns.GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE, true);
		StopSoundMem(bgm_);
	}

}

void GameOverScene::Draw(void)
{

	DrawGraph(0, 0, imgGameOver_, true);

}

void GameOverScene::Release(void)
{

	DeleteGraph(imgGameOver_);
	DeleteGraph(imgStart_);

}
