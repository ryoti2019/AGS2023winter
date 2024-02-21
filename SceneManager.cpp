#include <DxLib.h>
#include "Application.h"
#include "Fader.h"
#include "TitleScene.h"
#include "UserGuideScene.h"
#include "GameScene.h"
#include "GameOverScene.h"
#include "SceneManager.h"

// ������
SceneManager* SceneManager::instance_ = nullptr;

SceneManager::SceneManager(void)
{

	sceneId_ = SCENE_ID::NONE;
	waitSceneId_ = SCENE_ID::NONE;

	isSceneChanging_ = false;

	// �f���^�^�C��
	deltaTime_ = 1.0f / 60.0f;

}

SceneManager::~SceneManager(void)
{
}

void SceneManager::CreateInstance(void)
{

	if (instance_ == nullptr)
	{
		instance_ = new SceneManager();
	}
	instance_->Init();

}

void SceneManager::Init(void)
{

	sceneId_ = SCENE_ID::TITLE;
	waitSceneId_ = SCENE_ID::NONE;

	fader_ = new Fader();
	fader_->Init();

	isSceneChanging_ = false;

	// �f���^�^�C��
	preTime_ = std::chrono::system_clock::now();

	// �����V�[���̐ݒ�
	ChangeScene(SCENE_ID::TITLE, false);

}

void SceneManager::Update(void)
{

	// �f���^�^�C��
	auto preTime = std::chrono::system_clock::now();
	deltaTime_ =
		std::chrono::duration_cast<std::chrono::nanoseconds>(preTime - preTime_).count() / 1000000000.0f;
	preTime_ = preTime;

	// �t�F�[�h�X�V
	fader_->Update();
	if (isSceneChanging_)
	{
		Fade();
	}
	else
	{

		// �X�V
		switch (sceneId_)
		{
		case SceneManager::SCENE_ID::TITLE:
			titleScene_->Update();
			break;
		case SceneManager::SCENE_ID::USERGUIDESCENE:
			userGuideScene_->Update();
			break;
		case SceneManager::SCENE_ID::GAME:
			gameScene_->Update();
			break;
		case SceneManager::SCENE_ID::GAMEOVER:
			gameOverScene_->Update();
			break;
		}

	}

}

void SceneManager::Draw(void)
{

	// �`���O���t�B�b�N�̈�̎w��
	// (�R�c�`��Ŏg�p����J�����̐ݒ�Ȃǂ����Z�b�g�����)
	SetDrawScreen(DX_SCREEN_BACK);

	// ��ʂ�������
	ClearDrawScreen();

	// �`��
	switch (sceneId_)
	{
	case SceneManager::SCENE_ID::TITLE:
		titleScene_->Draw();
		break;
	case SceneManager::SCENE_ID::USERGUIDESCENE:
		userGuideScene_->Draw();
		break;
	case SceneManager::SCENE_ID::GAME:
		gameScene_->Draw();
		break;
	case SceneManager::SCENE_ID::GAMEOVER:
		gameOverScene_->Draw();
		break;
	}

	// �Ō�
	fader_->Draw();

}

void SceneManager::Release(void)
{

	ReleaseScene(SCENE_ID::TITLE);
	ReleaseScene(SCENE_ID::USERGUIDESCENE);
	ReleaseScene(SCENE_ID::GAME);
	ReleaseScene(SCENE_ID::GAMEOVER);

	delete fader_;

}

void SceneManager::ChangeScene(SCENE_ID nextId, bool isToFade)
{

	// �t�F�[�h�������I����Ă���V�[����ς���ꍇ�����邽�߁A
	// �J�ڐ�V�[���������o�ϐ��ɕێ�
	waitSceneId_ = nextId;

	if (isToFade)
	{
		// �t�F�[�h�A�E�g(�Ó])���J�n����
		fader_->SetFade(Fader::STATE::FADE_OUT);
		isSceneChanging_ = true;
	}
	else
	{
		// ���̊֐��ŃV�[����ύX����
		DoChangeScene();
	}

}

float SceneManager::GetDeltaTime(void)
{
	//return 1.0f / DEFAULT_FPS;
	return deltaTime_;
}

SceneManager& SceneManager::GetInstance(void)
{
	return *instance_;
}

void SceneManager::ResetDeltaTime(void)
{
	deltaTime_ = 1.0f / DEFAULT_FPS;
	preTime_ = std::chrono::system_clock::now();
}

void SceneManager::DoChangeScene(void)
{

	// ���݂̃V�[�������
	ReleaseScene(sceneId_);

	// �V�[����ύX����
	sceneId_ = waitSceneId_;

	switch (sceneId_)
	{
	case SCENE_ID::TITLE:
		titleScene_ = new TitleScene();
		titleScene_->Init();
		break;
	case SCENE_ID::USERGUIDESCENE:
		userGuideScene_ = new UserGuideScene();
		userGuideScene_->Init();
		break;
	case SCENE_ID::GAME:
		gameScene_ = new GameScene();
		gameScene_->Init();
		break;
	case SCENE_ID::GAMEOVER:
		gameOverScene_ = new GameOverScene();
		gameOverScene_->Init();
		break;
	}

	// �f���^�^�C�������Z�b�g����
	ResetDeltaTime();

	waitSceneId_ = SCENE_ID::NONE;

}

void SceneManager::ReleaseScene(SCENE_ID sceneId)
{

	switch (sceneId)
	{
	case SCENE_ID::TITLE:
		if (titleScene_ != nullptr)
		{
			titleScene_->Release();
			delete titleScene_;
		}
		break;
	case SCENE_ID::USERGUIDESCENE:
		if (userGuideScene_ != nullptr)
		{
			userGuideScene_->Release();
			delete userGuideScene_;
		}
		break;
	case SCENE_ID::GAME:
		if (gameScene_ != nullptr)
		{
			gameScene_->Release();
			delete gameScene_;
		}
		break;
	case SCENE_ID::GAMEOVER:
		if (gameOverScene_ != nullptr)
		{
			gameOverScene_->Release();
			delete gameOverScene_;
		}
		break;
	}

}

void SceneManager::Fade(void)
{

	Fader::STATE fState = fader_->GetState();
	switch (fState)
	{
	case Fader::STATE::FADE_OUT:
		if (fader_->IsEnd())
		{
			// �Ó]��A�V�[���ύX
			DoChangeScene();
			fader_->SetFade(Fader::STATE::FADE_IN);
		}
		break;
	case Fader::STATE::FADE_IN:
		if (fader_->IsEnd())
		{
			// ���]��A�V�[���J�ڏI��
			fader_->SetFade(Fader::STATE::NONE);
			isSceneChanging_ = false;
		}
		break;
	}

}