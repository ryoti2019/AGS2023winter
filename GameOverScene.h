#pragma once

class GameOverScene
{

public:

	// �R���X�g���N�^
	GameOverScene(void);

	// �f�X�g���N�^
	~GameOverScene(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

	// �Q�[���I�[�o�[�摜
	int imgGameOver_;

	// �X�^�[�g�摜
	int imgStart_;

	// ���ŗp�̃J�E���^
	int blinkCnt_;

	// BGM
	int bgm_;

	// ����{�^����SE
	int SEbotton_;

};



