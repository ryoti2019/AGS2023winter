#include "GameScene.h"
#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"

GameScene::GameScene()
{
	TRACE("GameScene�̃R���X�g���N�^�[�̌Ăяo��\n");
}

GameScene::~GameScene()
{
	TRACE("GameScene�̃f���X�g���N�^�[�̌Ăяo��\n");
}

bool GameScene::Init(void)
{
	screenID_ = MakeScreen(800, 600, true);
	TRACE("GameScene��Init()�̌Ăяo��\n");
	return true;
}

bool GameScene::Release(void)
{
	DeleteGraph(screenID_);
	screenID_ = 0;
	return false;
}

ScnID GameScene::Update(void)
{
	_TRACE_S(0x00ff00, "GameScene", 0);
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		return ScnID::Result;
	}
	return ScnID::Game;
}

void GameScene::Draw(void)
{
	DrawGraph(0, 0, screenID_, true);
}

void GameScene::GameDraw(void)
{
}
