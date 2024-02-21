#include <DxLib.h>
#include "Application.h"
#include "InputManager.h"
#include "SceneManager.h"

Application::Application(void)
{
	isError_ = false;
}

Application::~Application(void)
{
}

void Application::Init(void)
{

	// �A�v���P�[�V�����̏����ݒ�
	SetWindowText("2216008_���t��");

	// �E�B���h�E�T�C�Y
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)
	{
		isError_ = true;
		return;
	}

	// �L�[���䏉����
	SetUseDirectInputFlag(true);

	// �V�[���Ǘ��C���X�^���X������������
	SceneManager::CreateInstance();

	// ���͊Ǘ��C���X�^���X������������
	InputManager::CreateInstance();

}

void Application::Run(void)
{

	// �Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{

		InputManager::GetInstance().Update();

		SceneManager::GetInstance().Update();

		SceneManager::GetInstance().Draw();

		ScreenFlip();

	}

}

void Application::Release(void)
{

	if (DxLib_End() == -1)
	{
		isError_ = true;
		return;
	}

}

bool Application::IsError(void)
{
	return isError_;
}
