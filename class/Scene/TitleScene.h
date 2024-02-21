#pragma once
#include "ScnID.h"
class TitleScene
{
public:
	TitleScene();
	~TitleScene();
	bool Init(void);
	bool Release(void);
	ScnID Update(void);
	void Draw(void);
	void TitleDraw(void);
private:
	int titleImage_;
	int screenID_;
};

