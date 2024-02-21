#pragma once

class TitleScene
{

public:

	// コンストラクタ
	TitleScene(void);

	// デストラクタ
	~TitleScene(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

	// タイトル画像
	int imgTitle_;

	// スタート画像
	int imgStart_;

	// 明滅用のカウンタ
	int blinkCnt_;

	// タイトルシーンのBGM
	int bgm_;

	// 決定ボタンのSE
	int SEbotton_;

};



