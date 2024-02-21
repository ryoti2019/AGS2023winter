#include <DxLib.h>
#include "SceneMng.h"
#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"

#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 600

SceneMng::SceneMng()
{
	TRACE("SceneMngの生成\n");
	Init();
}

SceneMng::~SceneMng()
{
	TRACE("SceneMngの破棄\n");
	Release();
}

void SceneMng::Run(void)
{
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		_dbgStartDraw();
		if (nextScnID_ != scnID_)
		{
			SetupScene(nextScnID_);
			scnID_ = nextScnID_;
		}
		Update();
		Draw();
	}
}

void SceneMng::DrawScene(void)
{
}

bool SceneMng::Init(void)
{
	if (SysInit() == false)
	{
		return false;
	}
	scnID_ = ScnID::Non;
	nextScnID_ = ScnID::Title;
	//titleScene.Init();
	return true;
}

bool SceneMng::Release(void)
{
	TRACE("SceneMngのRelease()の呼び出し\n");
	DxLib_End();
    return true;
}

void SceneMng::Update(void)
{
	switch (scnID_)
	{
	case ScnID::Title:
		nextScnID_ = titleScene.Update();
		break;
	case ScnID::Select:
		nextScnID_ = selectScene.Update();
		break;
	case ScnID::Game:
		nextScnID_ = gameScene.Update();
		break;
	case ScnID::Result:
		nextScnID_ = resultScene.Update();
		break;
	case ScnID::Transition:
		break;
	case ScnID::Non:
		// 何もしない
		break;
	default:
		TRACE("未知のScnID:%d\n", scnID_);
		break;
	}
}

void SceneMng::Draw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();
	switch (scnID_)
	{
	case ScnID::Title:
		titleScene.Draw();
		break;
	case ScnID::Select:
		selectScene.Draw();
		break;
	case ScnID::Game:
		gameScene.Draw();
		break;
	case ScnID::Result:
		resultScene.Draw();
		break;
	case ScnID::Transition:
		break;
	case ScnID::Non:
		// 何もしない
		break;
	default:
		TRACE("未知のScnID:%d\n", scnID_);
		break;
	}
	_dbgDraw();
	ScreenFlip();
}

bool SceneMng::SysInit(void)
{TRACE("SysInitの呼び出し\n");
	SetWindowText("2216008_寺師 遼");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)
	{
		return false;
	}
	_dbgSetup(SCREEN_SIZE_X, SCREEN_SIZE_Y, 255);

	srand((unsigned int)time(NULL));
	return true;
}

bool SceneMng::SetupScene(ScnID scnID)
{
	ReleaseScene(scnID_);
	switch (scnID)
	{
	case ScnID::Title:
		titleScene.Init();
		break;
	case ScnID::Select:
		selectScene.Init();
		break;
	case ScnID::Game:
		gameScene.Init();
		break;
	case ScnID::Result:
		resultScene.Init();
		break;
	case ScnID::Transition:
		break;
	case ScnID::Non:
		// 何もしない
		break;
	default:
		TRACE("未知のScnID:%d\n", scnID);
		break;
	}
	return false;
}

bool SceneMng::ReleaseScene(ScnID scnID)
{
	switch (scnID)
	{
	case ScnID::Title:
		titleScene.Release();
		break;
	case ScnID::Select:
		selectScene.Release();
		break;
	case ScnID::Game:
		gameScene.Release();
		break;
	case ScnID::Result:
		resultScene.Release();
		break;
	case ScnID::Transition:
		break;
	case ScnID::Non:
		// 何もしない
		break;
	default:
		TRACE("未知のScnID:%d\n", scnID);
		break;
	}
	return false;
}
