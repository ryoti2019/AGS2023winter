#pragma once
#include "Vector2.h"
#include "Vector2F.h"
#include "AsoUtility.h"
class GameScene;

class EnemyShot
{

public:

    // 弾のサイズ
    static constexpr int E_SHOT_SIZE_X = 32;
    static constexpr int E_SHOT_SIZE_Y = 32;

    // 弾のアニメーション数
    static constexpr int E_SHOT_ANIM_NUM = 2;

    // 弾の生存カウント
    static constexpr int SHOT_CNT_ALIVE = 60;

    // 爆発のサイズ
    static constexpr int BLAST_SIZE_X = 32;
    static constexpr int BLAST_SIZE_Y = 32;

    // 爆発のアニメーション数
    static constexpr int BLAST_ANIM_NUM = 16;

    // 弾の状態
    enum class STATE
    {
        NONE,
        SHOT,
        BLAST,
        END
    };

    // コンストラクタ
    EnemyShot(void);

    // デストラクタ
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

    // 弾の生成
    void Create(Vector2F pos, Vector2F dir);

    // 弾の生成が可能か判定(NONE or END)
    bool IsEnableCreate(void);

    // 爆発開始
    void Blast(Vector2F pos);

    // 座標の取得
    Vector2F GetPos(void);

    // 
    bool IsShotState(void);

private:

    GameScene* gameScene_;

    // 弾の状態
    STATE state_;

    // 弾の画像
    int imgs_[E_SHOT_ANIM_NUM];

    // 弾の座標
    Vector2F pos_;

    // 弾の移動方向
    Vector2F dir_;

    // 弾の移動速度
    float speed_;

    // 弾の生存時間(カウンタ)
    int cntAlive_;

    // 弾のアニメーション用カウンタ
    int cntAnim_;

    // 弾のアニメーション速度
    float speedAnim_;

    // 弾のアニメーション番号
    int idxAnim_;

    // 爆発の画像
    int blastImgs_[BLAST_ANIM_NUM];

    // 弾の座標
    Vector2F blastPos_;

    // 爆発のアニメーションカウンタ
    int blastCntAnim_;

    // 爆発のアニメーション速度
    float blastSpeedAnim_;

    // 爆発のアニメーション番号
    int blastIdxAnim_;

    // ボスの打撃音の音SE
    int SEBossHit_;

    // 状態遷移
    void ChangeState(STATE state);

    // ステージの衝突
    void StageCollision(void);

};

