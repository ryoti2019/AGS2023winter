#pragma once
#include "ScnID.h"

class ResultScene
{
public:
	ResultScene();
	~ResultScene();
	bool Init(void);
	bool Release(void);
	ScnID Update(void);
	void Draw(void);
	void ResultDraw(void);
private:
	int screenID_;
};

