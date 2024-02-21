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

	// �V�[���Ǘ��p
	enum class SCENE_ID
	{
		NONE,
		TITLE,
		USERGUIDESCENE,
		GAME,
		GAMEOVER,
	};

	// �ÓI�C���X�^���X�̐���
	static void CreateInstance(void);
	static SceneManager& GetInstance(void);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	// �V�[���J�ږ���
	// isToFade��true�̏ꍇ�A�t�F�[�h�A�E�g�E�C�������s����
	void ChangeScene(SCENE_ID nextId, bool isToFade);

	// �f���^�^�C���̎擾
	float GetDeltaTime(void);

private:

	// �ÓI�C���X�^���X
	static SceneManager* instance_;

	SCENE_ID sceneId_;
	SCENE_ID waitSceneId_;

	// �t�F�[�h
	Fader* fader_;

	// �e��V�[��
	TitleScene* titleScene_;
	UserGuideScene* userGuideScene_;
	GameScene* gameScene_;
	GameOverScene* gameOverScene_;

	// �R���X�g���N�^
	SceneManager(void);

	// �f�X�g���N�^
	~SceneManager(void);

	// �V�[���J�ڒ�����
	bool isSceneChanging_;

	// �f���^�^�C��
	std::chrono::system_clock::time_point preTime_;
	float deltaTime_;

	void ResetDeltaTime(void);

	// �V�[���J��
	void DoChangeScene(void);

	// �V�[���̉��
	void ReleaseScene(SCENE_ID sceneId);

	// �t�F�[�h����
	void Fade(void);


};
