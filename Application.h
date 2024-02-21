#pragma once
class Application
{

public:

	// �X�N���[���T�C�Y
	static constexpr int SCREEN_SIZE_X = 800;
	static constexpr int SCREEN_SIZE_Y = 600;

	// �R���X�g���N�^
	Application(void);

	// �f�X�g���N�^
	~Application(void);

	// ������
	void Init(void);

	// �Q�[�����[�v�̊J�n
	void Run(void);

	// ���\�[�X�̉��
	void Release(void);

	// �G���[����
	bool IsError(void);

private:

	// �G���[����
	bool isError_;

};

