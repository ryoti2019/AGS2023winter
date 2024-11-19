#include "ResultScene.h"
#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"

ResultScene::ResultScene()
{
	TRACE("ResultSceneのコンストラクターの呼び出し\n");
}

ResultScene::~ResultScene()
{
	TRACE("ResultSceneのデストラクターの呼び出し\n");
}

bool ResultScene::Init(void)
{
	screenID_ = MakeScreen(800, 600, true);
	TRACE("ResultSceneのInit()の呼び出し\n");
	return true;
}

bool ResultScene::Release(void)
{
	DeleteGraph(screenID_);
	screenID_ = 0;
	return false;
}

ScnID ResultScene::Update(void)
{
	_TRACE_S(0x00ff00, "ResultScene", 0);
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		return ScnID::Title;
	}
	return ScnID::Result;
}

void ResultScene::Draw(void)
{
	DrawGraph(0, 0, screenID_, true);
}

void ResultScene::ResultDraw(void)
{
}
