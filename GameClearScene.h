#pragma once
class GameScene;

class GameClearScene
{

public:

	// コンストラクタ
	GameClearScene(void);

	// デストラクタ
	~GameClearScene(void);

	void Init(GameScene* scene);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

	GameScene* gameScene_;

	// ゲームクリア画像
	int imgGameClear_;

	// スタート画像
	int imgStart_;

	// 明滅用のカウンタ
	int blinkCnt_;

	// BGM
	int bgm_;

};

