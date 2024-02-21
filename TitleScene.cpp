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

	// �^�C�g����BGM�ǂݍ���
	bgm_ = LoadSoundMem("Music/�^�C�g��.ogg");

	// �^�C�g����BGM�Đ�
	PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP, true);

	// ����{�^����SE�̓ǂݍ���
	SEbotton_ = LoadSoundMem("Music/����{�^��.mp3");

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
		// �X�y�[�X�L�[���������ꂽ��A�Q�[���V�[���֑J�ڂ���
		sceneIns.GetInstance().ChangeScene(SceneManager::SCENE_ID::USERGUIDESCENE, true);
		StopSoundMem(bgm_);
	}
}

void TitleScene::Draw(void)
{

	// �^�C�g���摜�̃T�C�Y 800�~600
	// ��ʐ^�񒆂̂�����Ə�
	DrawGraph(0, 0, imgTitle_, true);

}

void TitleScene::Release(void)
{
	DeleteGraph(imgTitle_);
	DeleteGraph(imgStart_);
}
