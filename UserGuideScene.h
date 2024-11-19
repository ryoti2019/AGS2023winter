#pragma once
class UserGuideScene
{

public:

	// コンストラクタ
	UserGuideScene(void);

	// デストラクタ
	~UserGuideScene(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

	// 操作説明画像
	int imgUserGuide_;

	// スタート画像
	int imgStart_;

	// 明滅用のカウンタ
	int blinkCnt_;

	// BGM
	int bgm_;

	// 決定ボタンのSE
	int SEbotton_;

};

