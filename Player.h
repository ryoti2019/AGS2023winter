#pragma once
#include "GameScene.h"
#include "AsoUtility.h"
#include "Vector2.h"

class Player
{

public:

	// �������Ƃ̃A�j���[�V������
	static constexpr int NUM_ANIM = 3;

	// ���̃T�C�Y
	static constexpr int SIZE_X = 48;

	// �c�̃T�C�Y
	static constexpr int SIZE_Y = 48;

	// �ړ����x
	static constexpr int SPEED_DEFAULT = 5;

	// �A�j���[�V�������x
	static constexpr float ANIM_SPEED_DEFAULT = 0.1f;

	// �R���X�g���N�^
	Player(void);

	// �f�X�g���N�^
	~Player(void);

	void Init(GameScene* scene);
	void Update(void);
	void Draw(void);
	void Release(void);

	// ���W�擾(�Q�b�^�[)
	Vector2 GetPos(void);

	// ���W�̐ݒ�(�Z�b�^�[)
	void SetPos(Vector2 pos);

	// �ړ������̎擾(�Q�b�^�[)
	AsoUtility::DIR GetDir(void);

	// �_���[�W��^����
	void Damage(int damage);

	// HP�̎擾(�Q�b�^�[)
	int GetHP(void);

	// HPMAX�̎擾
	int GetHPMax(void);

	// ��������̎擾(�Q�b�^�[)
	bool IsAlive(void);

	// ��������̐ݒ�(�Z�b�^�[)
	void IsSetAlive(bool alive);

	// ���x���̎擾(�Q�b�^�[)
	int GetLevel(void);

	// �o���l
	void Exp(int exp);

private:

	// �Q�[���V�[���̃|�C���^�ϐ�
	GameScene* gameScene_;

	// �摜
	int imgs_[static_cast<int>(AsoUtility::DIR::MAX)][NUM_ANIM];

	// �\�����W
	Vector2 pos_;

	// �ړ����x
	int speed_;

	// �ړ�����
	AsoUtility::DIR dir_;

	// �A�j���[�V�����J�E���^
	int cntAnim_;

	// �A�j���[�V�������x
	float speedAnim_;

	// �A�j���[�V�����f�[�^
	int AnimData_[4];

	// �̗�
	int hp_;

	// �̗͍ő�l
	int hpMax_;

	// ��������
	bool isAlive_;

	// ���x��
	int level_;

	// ���x���ő�l
	int levelMax_;

	// �o���l
	int exp_;

	// ������SE
	int SEFoot_;

	// �v���C���[�̃f�o�b�O�`��
	void DrawDebug(void);

	// �v���C���[�̃X�e�[�W�̏Փ�
	void StageCollision(void);

	// ���x��
	void Level(void);

};


