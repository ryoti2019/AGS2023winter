#include <DxLib.h>
#include "Application.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "UserGuideScene.h"

UserGuideScene::UserGuideScene(void)
{
}

UserGuideScene::~UserGuideScene(void)
{
}

void UserGuideScene::Init(void)
{

	imgUserGuide_ = LoadGraph("Image/UI/UserGuide.png");
	imgStart_ = LoadGraph("Image/UI/HitStartKey.png");

	// BGM
	bgm_ = LoadSoundMem("Music/操作説明.ogg");

	// BGM
	PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP, true);

	// 決定ボタンのSEの読み込み
	SEbotton_ = LoadSoundMem("Music/決定ボタン.mp3");

}

void UserGuideScene::Update(void)
{
	SceneManager& sceneIns = SceneManager::GetInstance();
	auto& ins = InputManager::GetInstance();
	auto pad = InputManager::JOYPAD_NO::PAD1;
	auto input = ins.IsPadBtnTrgDown(pad, InputManager::JOYPAD_BTN::RIGHT);
	if (CheckHitKey(KEY_INPUT_SPACE) || input)
	{
		PlaySoundMem(SEbotton_, DX_PLAYTYPE_BACK, false);
		// スペースキーが押下されたら、ゲームシーンへ遷移する
		sceneIns.GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME, true);
		StopSoundMem(bgm_);
	}
}

void UserGuideScene::Draw(void)
{

	// タイトル画像のサイズ 800×600
	// 画面真ん中のちょっと上
	DrawGraph(0, 0, imgUserGuide_, true);
}

void UserGuideScene::Release(void)
{
	DeleteGraph(imgUserGuide_);
	DeleteGraph(imgStart_);
}
