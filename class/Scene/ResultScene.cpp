#include "ResultScene.h"
#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"

ResultScene::ResultScene()
{
	TRACE("ResultScene�̃R���X�g���N�^�[�̌Ăяo��\n");
}

ResultScene::~ResultScene()
{
	TRACE("ResultScene�̃f�X�g���N�^�[�̌Ăяo��\n");
}

bool ResultScene::Init(void)
{
	screenID_ = MakeScreen(800, 600, true);
	TRACE("ResultScene��Init()�̌Ăяo��\n");
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
