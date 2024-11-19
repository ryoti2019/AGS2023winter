#pragma once
#include "Vector2.h"
#include "Vector2F.h"
#include "AsoUtility.h"
class GameScene;

class Shot

{

public:

    // 矢のサイズ
    static constexpr int SHOT_SIZE_X = 32;
    static constexpr int SHOT_SIZE_Y = 32;

    // 矢の分割総数
    static constexpr int SHOT_NUM = 4;

    // 矢の横の分割数
    static constexpr int SHOT_NUM_X = 1;

    // 矢の縦の分割数
    static constexpr int SHOT_NUM_Y = 4;

    // 矢の生存カウント
    static constexpr int SHOT_CNT_ALIVE = 30;

    // 爆発のサイズ
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

    // 爆発のアニメーション数
    static constexpr int BLAST_ANIM_NUM = 4;

    // 弾の状態
    enum class STATE
    {
        NONE,
        SHOT,
        BLAST,
        END
    };

    // コンストラクタ
    Shot(void);

    // デストラクタ
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

    // 矢の生成
    void Create(Vector2F pos, AsoUtility::DIR dir);

    // 矢の生成が可能か判定(NONE or END)
    bool IsEnableCreate(void);

    // 爆発開始
    void Blast(Vector2F pos);

    // 座標の取得
    Vector2F GetPos(void);

    bool IsShotState(void);

    // 生存判定
    bool IsAlive(void);

    // 生存時間の設定
    void SetAlive(float time);

private:

    GameScene* gameScene_;

    // 矢の状態
    STATE state_;

    // 矢の画像
    int imgs_[SHOT_NUM];

    // 矢の画像
    int imgs2_[SHOT_NUM];

    // 矢の画像
    int imgs3_[SHOT_NUM];

    // 矢の画像
    int imgs4_[SHOT_NUM];

    // 矢の画像
    int imgs5_[SHOT_NUM];

    // 矢の座標
    Vector2F pos_;

    // 矢の移動方向
    Vector2F dir_;

    AsoUtility::DIR shotDir_;

    // 矢の移動速度
    float speed_;

    // 矢の生存時間(カウンタ)
    int cntAlive_;

    // 爆発の画像
    int blastImgs_[BLAST_ANIM_NUM];

    // 爆発の画像
    int blastImgs2_[BLAST_ANIM_NUM];

    // 爆発の画像
    int blastImgs3_[BLAST_ANIM_NUM];

    // 爆発の画像
    int blastImgs4_[BLAST_ANIM_NUM];

    // 爆発の画像
    int blastImgs5_[BLAST_ANIM_NUM];

    // 矢の座標
    Vector2F blastPos_;

    // 爆発のアニメーションカウンタ
    int blastCntAnim_;

    // 爆発のアニメーション速度
    float blastSpeedAnim_;

    // 爆発のアニメーション番号
    int blastIdxAnim_;

    // 打撃音1のSE
    int SE1Hit_;

    // 打撃音2のSE
    int SE2Hit_;

    // 打撃音3のSE
    int SE3Hit_;

    // 打撃音4のSE
    int SE4Hit_;

    // 打撃音5のSE
    int SE5Hit_;

    // 状態遷移
    void ChangeState(STATE state);

    // ステージの衝突
    void StageCollision(void);

};
