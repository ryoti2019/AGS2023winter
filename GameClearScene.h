#pragma once
class GameScene;

class GameClearScene
{

public:

	// �R���X�g���N�^
	GameClearScene(void);

	// �f�X�g���N�^
	~GameClearScene(void);

	void Init(GameScene* scene);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

	GameScene* gameScene_;

	// �Q�[���N���A�摜
	int imgGameClear_;

	// �X�^�[�g�摜
	int imgStart_;

	// ���ŗp�̃J�E���^
	int blinkCnt_;

	// BGM
	int bgm_;

};

