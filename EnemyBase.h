#pragma once
#include <string>
#include "Vector2.h"
#include "Vector2F.h"
#include "AsoUtility.h"
class GameScene;

class EnemyBase
{
public:

	// �������Ƃ̃A�j���[�V������
	static constexpr int NUM_ANIM = 4;

	// �G�̎��
	enum class TYPE
	{
		AcidOoze,
		BlindedGrimlock,
		BloodshotEye,
		MAX
	};

	// �R���X�g���N�^
	EnemyBase(void);

	// �f�X�g���N�^
	virtual ~EnemyBase(void);

	virtual void Init(GameScene* scene);

	// �p�����[�^�ݒ�
	virtual void SetParam(void) = 0;

	virtual void Update(void);
	virtual void Draw(void);
	virtual void Release(void);

	// ���W�擾(�Q�b�^�[)
	Vector2F GetPos(void);

	// ���W�̐ݒ�(�Z�b�^�[)
	void SetPos(Vector2F pos);

	// ��������̎擾(�Q�b�^�[)
	bool IsGetAlive(void);

	// ��������̎擾(�Z�b�^�[)
	void IsSetAlive(bool alive);

	// �摜�T�C�Y�̎擾
	Vector2 GetSize(void);

	// �_���[�W��^����
	void Damage(int damage);

	// �o���l
	int GetExp(void);

	// �������W
	int GetFootPosY(void);

protected:

	// �Q�[���V�[���̃|�C���^�ϐ�
	GameScene* gameScene_;

	// �摜�̃t�@�C����
	std::string imgFileName_;

	// �摜[����][�A�j���[�V����]
	int imgs_[static_cast<int>(AsoUtility::DIR::MAX)][NUM_ANIM];

	// �\�����W
	Vector2F pos_;

	// �摜�̃T�C�Y
	Vector2 size_;

	// �ړ����x
	float speed_;

	// �ړ�����
	AsoUtility::DIR dir_;

	// �A�j���[�V�����J�E���^
	int cntAnim_;

	// �A�j���[�V�������x
	float speedAnim_;

	// �̗�
	int hp_;

	// �̗͂̍ő�l
	int hpMax_;

	// ��������
	bool isAlive_;

	// �o���l
	int exp_;

	// �G�̃X�e�[�W�̏Փ�
	void StageCollision(void);

	// �G�̃X�e�[�W�̏Փ˔���
	bool IsStageCollision(Vector2F movedPos);

	// �G�̓���
	Vector2F Move(Vector2F dir);
};

