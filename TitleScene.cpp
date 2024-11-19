#include <DxLib.h>
#include "Application.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "TitleScene.h"

TitleScene::TitleScene(void)
{
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{

	imgTitle_ = LoadGraph("Image/UI/Title.png");
	imgStart_ = LoadGraph("Image/UI/HitStartKey.png");

	// タイトルのBGM読み込み
	bgm_ = LoadSoundMem("Music/タイトル.ogg");

	// タイトルのBGM再生
	PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP, true);

	// 決定ボタンのSEの読み込み
	SEbotton_ = LoadSoundMem("Music/決定ボタン.mp3");

}

void TitleScene::Update(void)
{
	SceneManager& sceneIns = SceneManager::GetInstance();
	auto& ins = InputManager::GetInstance();
	auto pad = InputManager::JOYPAD_NO::PAD1;
	auto input = ins.IsPadBtnTrgDown(pad, InputManager::JOYPAD_BTN::RIGHT);
	if (CheckHitKey(KEY_INPUT_SPACE) || input)
	{
		PlaySoundMem(SEbotton_, DX_PLAYTYPE_BACK, false);
		// スペースキーが押下されたら、ゲームシーンへ遷移する
		sceneIns.GetInstance().ChangeScene(SceneManager::SCENE_ID::USERGUIDESCENE, true);
		StopSoundMem(bgm_);
	}
}

void TitleScene::Draw(void)
{

	// タイトル画像のサイズ 800×600
	// 画面真ん中のちょっと上
	DrawGraph(0, 0, imgTitle_, true);

}

void TitleScene::Release(void)
{
	DeleteGraph(imgTitle_);
	DeleteGraph(imgStart_);
}
