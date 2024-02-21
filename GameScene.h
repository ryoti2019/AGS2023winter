#pragma once
#include <vector>
#include <list>
#include "Vector2.h"
class Stage;
class Player;
class EnemyBoss;
class EnemyBase;
class EnemyShot;
class Shot;
class StartMes;


class GameScene
{

public:

	// カメラを動かす範囲
	static constexpr int CAMERA_WIDTH = 400;
	static constexpr int CAMERA_HEIGHT = 300;

	// エンカウント値(値が大きいと出現間隔が長くなる)
	// 30フレームに1体、敵を作ります。
	static constexpr int ENCOUNT = 60;

	// コンストラクタ
	GameScene(void);

	// デストラクタ
	~GameScene(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void DrawUI(void);
	void Release(void);

	// カメラ座標の取得(ゲッター)
	Vector2 GetCameraPos(void);

	// ワールド(スクリーン)座標をマップ座標に変換する
	Vector2 World2MapPos(Vector2 worldPos);

	// マップチップを使用した衝突判定
	bool IsCollisionStage(Vector2 worldPos);

	// ドアの衝突判定
	bool IsCollisionDoor(Vector2 worldPos);

	// ドアの衝突判定
	bool IsCollisionGate(Vector2 worldPos);

	// プレイヤー座標の取得
	Vector2 GetPlayerPos(void);

	// 鍵1のゲッター
	bool GetKey1(void);

	// 鍵2のゲッター
	bool GetKey2(void);

	// 鍵3のゲッター
	bool GetKey3(void);

	// 鍵4のゲッター
	bool GetKey4(void);

	// 分のゲッター
	int GetMinute(void);

	// 秒のゲッター
	int GetSecond(void);

	bool IsCollisionRectCenter
	(Vector2 centerPos1, Vector2 size1,
		Vector2 centerPos2, Vector2 size2);

	/// <summary>
	/// 矩形同士の衝突判定
	/// </summary>
	/// <param name="stPos1">矩形１の中心座標</param>
	/// <param name="edPos1">矩形１のサイズ</param>
	/// <param name="stPos2">矩形２の中心座標</param>
	/// <param name="edPos2">矩形２のサイズ</param>

	// ステージの取得
	Stage* GetStage(void);

	// プレイヤーの取得
	Player* GetPlayer(void);

private:

	// タイトル画像
	int imgGame_;

	// スタート画像
	int imgStart_;

	// 体力ゲージの画像
	int hpImage_;

	// アクター画像
	int Actorimg_;

	// 鍵1の画像
	int keyImage1_;

	// 鍵2の画像
	int keyImage2_;

	// 鍵3の画像
	int keyImage3_;

	// 鍵4の画像
	int keyImage4_;

	// UIの矢の画像の背景
	int ArrowBack_;

	// UIの矢の画像
	int UIimgs_;

	// UIの矢の画像
	int UIimgs2_;

	// UIの矢の画像
	int UIimgs3_;

	// UIの矢の画像
	int UIimgs4_;

	// UIの矢の画像
	int UIimgs5_;

	// レベル1の画像
	int Level1_;

	// レベル2の画像
	int Level2_;

	// レベル3の画像
	int Level3_;

	// レベル4の画像
	int Level4_;

	// レベル5の画像
	int Level5_;

	// レベル画像の背景
	int LevelBack_;

	// ゲームクリアシーンの画像
	int imgGameClear_;

	// ステージのポインタ
	Stage* stage_;

	// プレイヤーのポインタ
	Player* player_;

	// エネミーボスのポインタ
	EnemyBoss* enemyBoss_;

	// エネミーのポインタ
	EnemyShot* enemyShot_;

	// ショットのポインタ
	Shot* shot_;

	// 複数の敵を動的に管理
	std::vector<EnemyBase*> enemys_;

	// 足元座標の小さい順にソート
	std::list<EnemyBase*> sortEnemys_;

	// スタートメッセージ
	StartMes* startMes_;

	// 敵の発生頻度
	int enCounter;

	// カメラ座標
	Vector2 cameraPos_;

	// 弾を撃つキーの状態
	bool isShotKeyNew_;

	// 弾を撃つキーの状態(1フレーム前の状態)
	bool isShotKeyOld_;

	// 弾発射後の硬直時間計算用
	float stepShotDelay_;

	// 宝箱座標
	Vector2 boxPos_;

	// アクター画像の状態
	bool isActor1_;

	// アクター画像の状態
	bool isActor2_;

	// アクター画像の状態
	bool isActor3_;

	// アクター画像の状態
	bool isActor4_;

	// アクター画像の補助
	bool isActor1a_;

	// アクター画像の補助
	bool isActor2a_;

	// アクター画像の補助
	bool isActor3a_;

	// アクター画像の補助
	bool isActor4a_;

	// 鍵1の状態
	bool isKey1_;

	// 鍵2の状態
	bool isKey2_;

	// 鍵3の状態
	bool isKey3_;

	// 鍵4の状態
	bool isKey4_;

	// ドア1の状態
	bool openDoor1_;
	
	// ドア2の状態
	bool openDoor2_;

	// ドア3の状態
	bool openDoor3_;

	// ドア4の状態
	bool openDoor4_;

	// ヒットストップ
	int hitStopCnt_;

	// スクリーン
	int tmpScreen_;

	// スローカウント
	int slowCnt_;

	// 時間のカウント
	int timecnt_;

	// 秒数
	int second_;

	// 分数
	int minute_;

	// ゲームクリアシーン
	int gameClear_;

	// 明滅用のカウンタ
	int blinkCnt_;

	// フェード用のカウンタ
	int fadeCnt_;

	// ゲームシーンのBGM
	int bgmGameScene_;

	// 決定ボタンのSE
	int SEBotton_;

	// アクターのSE
	int SEActor_;

	// 攻撃ボタンのSE
	int SEAttack_;

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

	// ボスの打撃音のSE
	int SEBossHit_;

	// ドアのSE
	int SEDoor_;

	// カメラ移動
	void CameraMove(void);

	// カメラ移動(デバッグ用)
	void CameraMoveDebug(void);

	// 衝突判定
	void Collision(void);

	bool IsCollisionRect
	(Vector2 stPos1, Vector2 edPos1,
		Vector2 stPos2, Vector2 edPos2);

	/// <summary>
	/// 矩形同士の衝突判定
	/// </summary>
	/// <param name="stPos1">矩形１の左上座標</param>
	/// <param name="edPos1">矩形１の右下座標</param>
	/// <param name="stPos2">矩形２の右上座標</param>
	/// <param name="edPos2">矩形２の右下座標</param>

	//bool IsCollisionRectCenter
	//(Vector2 centerPos1, Vector2 size1,
	//Vector2 centerPos2, Vector2 size2);

	/// <summary>
	/// 矩形同士の衝突判定
	/// </summary>
	/// <param name="stPos1">矩形１の中心座標</param>
	/// <param name="edPos1">矩形１のサイズ</param>
	/// <param name="stPos2">矩形２の中心座標</param>
	/// <param name="edPos2">矩形２のサイズ</param>

	// 敵のクリア
	void ClearEnemys(void);

	// 描画順用:足元座標(Y)の小さい順にソートしていく
	void SortEnemys(void);

	// 宝箱の判定
	void TreasureChest(void);

	// アクター画像の管理
	void Actor(void);

	// ゲームクリア用
	void GameClear(void);

	// BGM
	void BGM(void);

};



