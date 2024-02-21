#pragma once
#include "ScnID.h"

class SelectScene
{
public:
	SelectScene();
	~SelectScene();
	bool Init(void);
	bool Release(void);
	ScnID Update(void);
	void Draw(void);
	void SelectDraw(void);
private:
	int screenID_;
};

