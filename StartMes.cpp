#include <DxLib.h>
#include "StartMes.h"

StartMes::StartMes()
{
}

StartMes::~StartMes()
{
}

void StartMes::Init(GameScene* scene)
{
	LoadDivGraph("Image/UI/StartMes.png",
		static_cast<int>(Mes::Max),
		1,
		static_cast<int>(Mes::Max),
		SIZE_X,
		SIZE_Y,
		&imageHdl_[0]);

	count_ = 0;
}

void StartMes::Update(void)
{
	if (count_ >= 300)
	{
		return;
	}
	count_++;
}

void StartMes::Release(void)
{
	for (int j = 0; j < static_cast<int>(Mes::Max); j++)
	{
		DeleteGraph(imageHdl_[j]);
	}
}

void StartMes::Draw(void)
{
	if (count_ >= 300)
	{
		return;
	}
	if (count_<= 60)
	{
		DrawGraph(
			(800 - SIZE_X) / 2,
			(600 - SIZE_Y) / 2,
			imageHdl_[0],
			true);
	}
	if (count_ >= 61 && count_ <= 120)
	{
		DrawGraph(
			(800 - SIZE_X) / 2,
			(600 - SIZE_Y) / 2,
			imageHdl_[1],
			true);
	}
	if (count_ >= 121 && count_ <= 180)
	{
		DrawGraph(
			(800 - SIZE_X) / 2,
			(600 - SIZE_Y) / 2,
			imageHdl_[2],
			true);
	}
	if (count_ >= 181 && count_ <= 240)
	{
		DrawGraph(
			(800 - SIZE_X) / 2,
			(600 - SIZE_Y) / 2,
			imageHdl_[3],
			true);
	}
	if (count_ >= 241 || count_ >= 300)
	{
		DrawGraph(
			(800 - SIZE_X) / 2,
			(600 - SIZE_Y) / 2,
			imageHdl_[4],
			true);
	}

}

int StartMes::GetCnt(void)
{
	return count_;
}
