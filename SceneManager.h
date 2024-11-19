#pragma once
#include <chrono>
#include <DxLib.h>
class Fader;
class TitleScene;
class UserGuideScene;
class GameScene;
class GameOverScene;

class SceneManager
{

public:

	static constexpr float DEFAULT_FPS = 60.0f;

	// シーン管理用
	enum class SCENE_ID
	{
		NONE,
		TITLE,
		USERGUIDESCENE,
		GAME,
		GAMEOVER,
	};

	// 静的インスタンスの生成
	static void CreateInstance(void);
	static SceneManager& GetInstance(void);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	// シーン遷移命令
	// isToFadeがtrueの場合、フェードアウト・インを実行する
	void ChangeScene(SCENE_ID nextId, bool isToFade);

	// デルタタイムの取得
	float GetDeltaTime(void);

private:

	// 静的インスタンス
	static SceneManager* instance_;

	SCENE_ID sceneId_;
	SCENE_ID waitSceneId_;

	// フェード
	Fader* fader_;

	// 各種シーン
	TitleScene* titleScene_;
	UserGuideScene* userGuideScene_;
	GameScene* gameScene_;
	GameOverScene* gameOverScene_;

	// コンストラクタ
	SceneManager(void);

	// デストラクタ
	~SceneManager(void);

	// シーン遷移中判定
	bool isSceneChanging_;

	// デルタタイム
	std::chrono::system_clock::time_point preTime_;
	float deltaTime_;

	void ResetDeltaTime(void);

	// シーン遷移
	void DoChangeScene(void);

	// シーンの解放
	void ReleaseScene(SCENE_ID sceneId);

	// フェード処理
	void Fade(void);


};
