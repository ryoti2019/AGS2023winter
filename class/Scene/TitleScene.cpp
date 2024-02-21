#include <DxLib.h>
#include "TitleScene.h"
#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"

TitleScene::TitleScene()
{
	TRACE("TitleSceneのコンストラクターの呼び出し\n");
}

TitleScene::~TitleScene()
{
	TRACE("TitleSceneのデストラクターの呼び出し\n");
}

bool TitleScene::Init(void)
{
	 screenID_ = MakeScreen(800, 600, true);
	TRACE("TitleSceneのInit()の呼び出し\n");
	titleImage_ = LoadGraph("./Resource/image/title.png");
	if (titleImage_ == -1)
	{
		TRACE("title.pngの読み込み失敗\n");
		return false;
	}
	return true;
}

bool TitleScene::Release(void)
{
	TRACE("TitleSceneのRelease()の呼び出し\n");
	DeleteGraph(screenID_);
	DeleteGraph(titleImage_);
	screenID_ = 0;
	titleImage_ = 0;
	return false;
}

ScnID TitleScene::Update(void)
{
	_TRACE_S(0x00ff00, "TitleScene", 0);
	//TRACE("TitleSceneのUpdate()の呼び出し\n");
	TitleDraw();
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		return ScnID::Select;
	}
	return ScnID::Title;
}

void TitleScene::Draw(void)
{
	//TRACE("TitleSceneのDraw()の呼び出し\n");
	DrawGraph(0, 0, screenID_, true);
}

void TitleScene::TitleDraw(void)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawGraph(0, 0, titleImage_, true);
}
