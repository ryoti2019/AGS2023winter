#pragma once
class UserGuideScene
{

public:

	// �R���X�g���N�^
	UserGuideScene(void);

	// �f�X�g���N�^
	~UserGuideScene(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

	// ��������摜
	int imgUserGuide_;

	// �X�^�[�g�摜
	int imgStart_;

	// ���ŗp�̃J�E���^
	int blinkCnt_;

	// BGM
	int bgm_;

	// ����{�^����SE
	int SEbotton_;

};

