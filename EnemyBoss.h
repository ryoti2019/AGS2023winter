#pragma once
#include "GameScene.h"
#include "AsoUtility.h"
#include "Vector2.h"
class EnemyShot;

class EnemyBoss
{
public:

	// �������Ƃ̃A�j���[�V������
	static constexpr int NUM_ANIM = 8;

	// ���̃T�C�Y
	static constexpr int SIZE_X = 64;

	// �c�̃T�C�Y
	static constexpr int SIZE_Y = 64;

	// �ړ����x
	static constexpr int SPEED_DEFAULT = 1;

	// �A�j���[�V�������x
	static constexpr float ANIM_SPEED_DEFAULT = 0.1f;

	// �R���X�g���N�^
	EnemyBoss(void);

	// �f�X�g���N�^
	~EnemyBoss(void);

	void Init(GameScene* scene);
	void Update(void);
	void Draw(void);
	void Release(void);

	// ���W�擾(�Q�b�^�[)
	Vector2 GetPos(void);

	// �e�̍��W�̎擾(�Q�b�^�[)
	EnemyShot* GetEnemyShot(void);

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
	bool IsGetAlive(void);

	// ��������̐ݒ�(�Z�b�^�[)
	void IsSetAlive(bool alive);

private:

	// �Q�[���V�[���̃|�C���^�ϐ�
	GameScene* gameScene_;

	// �V���b�g�̃|�C���^�ϐ�
	EnemyShot* enemyShot_;

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

	// �{�X�̍U������SE
	int SEBossAttack_;

	// �G�̃X�e�[�W�̏Փ�
	void StageCollision(void);

	// �G�̃X�e�[�W�̏Փ˔���
	bool IsStageCollision(Vector2F movedPos);

	// �G�̓���
	Vector2F Move(Vector2F dir);

};

