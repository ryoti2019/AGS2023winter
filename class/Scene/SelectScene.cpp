#include <DxLib.h>
#include "SelectScene.h"
#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"

SelectScene::SelectScene()
{
	TRACE("SelectScene�̃R���X�g���N�^�[�̌Ăяo��\n");
}

SelectScene::~SelectScene()
{
	TRACE("SelectScene�̃f���X�g���N�^�[�̌Ăяo��\n");
}

bool SelectScene::Init(void)
{
	screenID_ = MakeScreen(800, 600, true);
	TRACE("SelectScene��Init()�̌Ăяo��\n");
	return false;
}

bool SelectScene::Release(void)
{
	DeleteGraph(screenID_);
	screenID_ = 0;
	return true;
}

ScnID SelectScene::Update(void)
{
	_TRACE_S(0x00ff00, "SelectScene", 0);
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		return ScnID::Game;
	}
	return ScnID::Select;
}

void SelectScene::Draw(void)
{
	DrawGraph(0, 0, screenID_, true);
}

void SelectScene::SelectDraw(void)
{

}
