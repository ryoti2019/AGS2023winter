#pragma once

class TitleScene
{

public:

	// �R���X�g���N�^
	TitleScene(void);

	// �f�X�g���N�^
	~TitleScene(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

	// �^�C�g���摜
	int imgTitle_;

	// �X�^�[�g�摜
	int imgStart_;

	// ���ŗp�̃J�E���^
	int blinkCnt_;

	// �^�C�g���V�[����BGM
	int bgm_;

	// ����{�^����SE
	int SEbotton_;

};



