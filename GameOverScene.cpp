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

	// �摜�̓ǂݍ���
	imgGameOver_ = LoadGraph("Image/UI/GameOver.png");
	imgStart_ = LoadGraph("Image/UI/HitStartKey.png");

	// BGM
	bgm_ = LoadSoundMem("Music/�Q�[���I�[�o�[.ogg");

	// BGM
	PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP, true);

	// ����{�^����SE�̓ǂݍ���
	SEbotton_ = LoadSoundMem("Music/����{�^��.mp3");

}

void GameOverScene::Update(void)
{

	SceneManager& sceneIns = SceneManager::GetInstance();
	auto& ins = InputManager::GetInstance();
	auto pad = InputManager::JOYPAD_NO::PAD1;
	auto input = ins.IsPadBtnTrgDown(pad, InputManager::JOYPAD_BTN::RIGHT);
	// �^�C�g����ʂɖ߂�
	if (CheckHitKey(KEY_INPUT_SPACE) || input)
	{
		PlaySoundMem(SEbotton_, DX_PLAYTYPE_BACK, false);
		// �X�y�[�X�L�[���������ꂽ��A�^�C�g���V�[���֑J�ڂ���
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
