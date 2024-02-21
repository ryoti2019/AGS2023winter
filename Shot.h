#pragma once
#include "Vector2.h"
#include "Vector2F.h"
#include "AsoUtility.h"
class GameScene;

class Shot

{

public:

    // ��̃T�C�Y
    static constexpr int SHOT_SIZE_X = 32;
    static constexpr int SHOT_SIZE_Y = 32;

    // ��̕�������
    static constexpr int SHOT_NUM = 4;

    // ��̉��̕�����
    static constexpr int SHOT_NUM_X = 1;

    // ��̏c�̕�����
    static constexpr int SHOT_NUM_Y = 4;

    // ��̐����J�E���g
    static constexpr int SHOT_CNT_ALIVE = 30;

    // �����̃T�C�Y
    static constexpr int BLAST_SIZE_X = 39;
    static constexpr int BLAST_SIZE_Y = 39;

    static constexpr int BLAST2_SIZE_X = 47;
    static constexpr int BLAST2_SIZE_Y = 40;

    static constexpr int BLAST3_SIZE_X = 39;
    static constexpr int BLAST3_SIZE_Y = 39;

    static constexpr int BLAST4_SIZE_X = 61;
    static constexpr int BLAST4_SIZE_Y = 53;

    static constexpr int BLAST5_SIZE_X = 53;
    static constexpr int BLAST5_SIZE_Y = 50;

    // �����̃A�j���[�V������
    static constexpr int BLAST_ANIM_NUM = 4;

    // �e�̏��
    enum class STATE
    {
        NONE,
        SHOT,
        BLAST,
        END
    };

    // �R���X�g���N�^
    Shot(void);

    // �f�X�g���N�^
    ~Shot(void);

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

    // ��̐���
    void Create(Vector2F pos, AsoUtility::DIR dir);

    // ��̐������\������(NONE or END)
    bool IsEnableCreate(void);

    // �����J�n
    void Blast(Vector2F pos);

    // ���W�̎擾
    Vector2F GetPos(void);

    bool IsShotState(void);

    // ��������
    bool IsAlive(void);

    // �������Ԃ̐ݒ�
    void SetAlive(float time);

private:

    GameScene* gameScene_;

    // ��̏��
    STATE state_;

    // ��̉摜
    int imgs_[SHOT_NUM];

    // ��̉摜
    int imgs2_[SHOT_NUM];

    // ��̉摜
    int imgs3_[SHOT_NUM];

    // ��̉摜
    int imgs4_[SHOT_NUM];

    // ��̉摜
    int imgs5_[SHOT_NUM];

    // ��̍��W
    Vector2F pos_;

    // ��̈ړ�����
    Vector2F dir_;

    AsoUtility::DIR shotDir_;

    // ��̈ړ����x
    float speed_;

    // ��̐�������(�J�E���^)
    int cntAlive_;

    // �����̉摜
    int blastImgs_[BLAST_ANIM_NUM];

    // �����̉摜
    int blastImgs2_[BLAST_ANIM_NUM];

    // �����̉摜
    int blastImgs3_[BLAST_ANIM_NUM];

    // �����̉摜
    int blastImgs4_[BLAST_ANIM_NUM];

    // �����̉摜
    int blastImgs5_[BLAST_ANIM_NUM];

    // ��̍��W
    Vector2F blastPos_;

    // �����̃A�j���[�V�����J�E���^
    int blastCntAnim_;

    // �����̃A�j���[�V�������x
    float blastSpeedAnim_;

    // �����̃A�j���[�V�����ԍ�
    int blastIdxAnim_;

    // �Ō���1��SE
    int SE1Hit_;

    // �Ō���2��SE
    int SE2Hit_;

    // �Ō���3��SE
    int SE3Hit_;

    // �Ō���4��SE
    int SE4Hit_;

    // �Ō���5��SE
    int SE5Hit_;

    // ��ԑJ��
    void ChangeState(STATE state);

    // �X�e�[�W�̏Փ�
    void StageCollision(void);

};
