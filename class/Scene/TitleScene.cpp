#include <DxLib.h>
#include "TitleScene.h"
#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"

TitleScene::TitleScene()
{
	TRACE("TitleScene�̃R���X�g���N�^�[�̌Ăяo��\n");
}

TitleScene::~TitleScene()
{
	TRACE("TitleScene�̃f�X�g���N�^�[�̌Ăяo��\n");
}

bool TitleScene::Init(void)
{
	 screenID_ = MakeScreen(800, 600, true);
	TRACE("TitleScene��Init()�̌Ăяo��\n");
	titleImage_ = LoadGraph("./Resource/image/title.png");
	if (titleImage_ == -1)
	{
		TRACE("title.png�̓ǂݍ��ݎ��s\n");
		return false;
	}
	return true;
}

bool TitleScene::Release(void)
{
	TRACE("TitleScene��Release()�̌Ăяo��\n");
	DeleteGraph(screenID_);
	DeleteGraph(titleImage_);
	screenID_ = 0;
	titleImage_ = 0;
	return false;
}

ScnID TitleScene::Update(void)
{
	_TRACE_S(0x00ff00, "TitleScene", 0);
	//TRACE("TitleScene��Update()�̌Ăяo��\n");
	TitleDraw();
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		return ScnID::Select;
	}
	return ScnID::Title;
}

void TitleScene::Draw(void)
{
	//TRACE("TitleScene��Draw()�̌Ăяo��\n");
	DrawGraph(0, 0, screenID_, true);
}

void TitleScene::TitleDraw(void)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawGraph(0, 0, titleImage_, true);
}
