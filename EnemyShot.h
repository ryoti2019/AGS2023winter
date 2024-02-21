#pragma once
#include "Vector2.h"
#include "Vector2F.h"
#include "AsoUtility.h"
class GameScene;

class EnemyShot
{

public:

    // �e�̃T�C�Y
    static constexpr int E_SHOT_SIZE_X = 32;
    static constexpr int E_SHOT_SIZE_Y = 32;

    // �e�̃A�j���[�V������
    static constexpr int E_SHOT_ANIM_NUM = 2;

    // �e�̐����J�E���g
    static constexpr int SHOT_CNT_ALIVE = 60;

    // �����̃T�C�Y
    static constexpr int BLAST_SIZE_X = 32;
    static constexpr int BLAST_SIZE_Y = 32;

    // �����̃A�j���[�V������
    static constexpr int BLAST_ANIM_NUM = 16;

    // �e�̏��
    enum class STATE
    {
        NONE,
        SHOT,
        BLAST,
        END
    };

    // �R���X�g���N�^
    EnemyShot(void);

    // �f�X�g���N�^
    ~EnemyShot(void);

    void Init(GameScene* scene);

    void Update(void);
    void UpdateShot(void);
    void UpdateBlast(void);
    void UpdateEnd(void);

    void Draw(void);
    void DrawShot(void);
    void DrawBlast(void);
    void DrawEnd(void);

    void Release(void);

    // �e�̐���
    void Create(Vector2F pos, Vector2F dir);

    // �e�̐������\������(NONE or END)
    bool IsEnableCreate(void);

    // �����J�n
    void Blast(Vector2F pos);

    // ���W�̎擾
    Vector2F GetPos(void);

    // 
    bool IsShotState(void);

private:

    GameScene* gameScene_;

    // �e�̏��
    STATE state_;

    // �e�̉摜
    int imgs_[E_SHOT_ANIM_NUM];

    // �e�̍��W
    Vector2F pos_;

    // �e�̈ړ�����
    Vector2F dir_;

    // �e�̈ړ����x
    float speed_;

    // �e�̐�������(�J�E���^)
    int cntAlive_;

    // �e�̃A�j���[�V�����p�J�E���^
    int cntAnim_;

    // �e�̃A�j���[�V�������x
    float speedAnim_;

    // �e�̃A�j���[�V�����ԍ�
    int idxAnim_;

    // �����̉摜
    int blastImgs_[BLAST_ANIM_NUM];

    // �e�̍��W
    Vector2F blastPos_;

    // �����̃A�j���[�V�����J�E���^
    int blastCntAnim_;

    // �����̃A�j���[�V�������x
    float blastSpeedAnim_;

    // �����̃A�j���[�V�����ԍ�
    int blastIdxAnim_;

    // �{�X�̑Ō����̉�SE
    int SEBossHit_;

    // ��ԑJ��
    void ChangeState(STATE state);

    // �X�e�[�W�̏Փ�
    void StageCollision(void);

};

