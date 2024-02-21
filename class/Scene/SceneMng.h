#pragma once
#include "TitleScene.h"
#include "SelectScene.h"
#include "GameScene.h"
#include "ResultScene.h"

#include "ScnID.h"

class SceneMng
{
public:
	SceneMng();
	~SceneMng();
	void Run(void);
	void DrawScene(void);
private:
	bool Init(void);
	bool Release(void);
	void Update(void);
	void Draw(void);
	bool SysInit(void);
	bool SetupScene(ScnID scnID);
	bool ReleaseScene(ScnID scnID);

	ScnID scnID_;
	ScnID nextScnID_;

	TitleScene titleScene;
	SelectScene selectScene;
	GameScene gameScene;
	ResultScene resultScene;
};

