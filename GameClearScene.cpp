#include "GameClearScene.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "Application.h"
#include "InputManager.h"




GameClearScene::GameClearScene(void)
{
}

GameClearScene::~GameClearScene(void)
{
}

void GameClearScene::Init(GameScene* scene)
{

	// 画像の読み込み
	imgGameClear_ = LoadGraph("Image/UI/GameClear.png");
	imgStart_ = LoadGraph("Image/UI/HitStartKey.png");

	// BGM
	bgm_ = LoadSoundMem("Music/ゲームクリア.ogg");

	// BGM
	PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP, true);


}

void GameClearScene::Update(void)
{

	SceneManager& sceneIns = SceneManager::GetInstance();
	auto& ins = InputManager::GetInstance();
	auto pad = InputManager::JOYPAD_NO::PAD1;
	auto input = ins.IsPadBtnTrgDown(pad, InputManager::JOYPAD_BTN::RIGHT);
	// タイトル画面に戻る
	if (CheckHitKey(KEY_INPUT_SPACE) || input)
	{
		// スペースキーが押下されたら、ゲームシーンへ遷移する
		sceneIns.GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE, true);
		StopSoundMem(bgm_);
	}
}

void GameClearScene::Draw(void)
{

	int minute = gameScene_->GetMinute();
	int second = gameScene_->GetSecond();
	DrawFormatString(Application::SCREEN_SIZE_X / 2, 0, 0xffffff, "タイム:%d分%d秒", minute, second);

	blinkCnt_++;
	if ((blinkCnt_ / 30) % 2)
	{
		DrawGraph(
			(Application::SCREEN_SIZE_X / 2) - (337 / 2),
			(Application::SCREEN_SIZE_Y / 2) - (53 / 2) + 100,
			imgStart_,
			true
		);
	}
	DrawGraph(0, 0, imgGameClear_, true);

}

void GameClearScene::Release(void)
{
}
