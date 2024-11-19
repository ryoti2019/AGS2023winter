#pragma once
#include "ScnID.h"
class GameScene
{
public:
	GameScene();
	~GameScene();
	bool Init(void);
	bool Release(void);
	ScnID Update(void);
	void Draw(void);
	void GameDraw(void);
private:
	int screenID_;
};

