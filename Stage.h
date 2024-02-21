#pragma once
#include "Vector2.h"
class GameScene;

class Stage
{

public:

	// ステージ画像の横の分割数
	static constexpr int NUM_MAP_CHIPS_X = 24;

	// ステージ画像の縦の分割数
	static constexpr int NUM_MAP_CHIPS_Y = 8;

	// ステージ画像の分割総数
	static constexpr int
		NUM_MAP_CHIPS = NUM_MAP_CHIPS_X * NUM_MAP_CHIPS_Y;

	// マップチップサイズ
	static constexpr int CHIP_SIZE_X = 32;
	static constexpr int CHIP_SIZE_Y = 32;

	// マップの最大サイズ
	static constexpr int MAP_MAX_SIZE_X = 69;
	static constexpr int MAP_MAX_SIZE_Y = 70;

	// マップの種類
	enum class TYPE
	{
		NONE,
		GROUND,
	};

	// コンストラクタ
	Stage(void);

	// デストラクタ
	~Stage(void);

	void Init(GameScene* scene);
	void Update(void);
	void Draw(void);
	void Release(void);

	// 外部ファイルから床・壁のステージデータを読み込む
	void LoadCsvWallData(void);

	// 外部ファイルからドアのステージデータを読み込む
	void LoadCsvDoorData(void);

	// 外部ファイルからドアの衝突のステージデータを読み込む
	void LoadCsvCollisionDoorData(void);

	// 外部ファイルからオブジェクトのステージデータを読み込む
	void LoadCsvObjectData(void);

	// 外部ファイルから床・壁の衝突のステージデータを読み込む
	void LoadCsvCollisionStageData(void);

	// 外部ファイルから脱出ゲートのステージデータを読み込む
	void LoadCsvGateData(void);

	// 外部ファイルからスイッチ1のステージデータを読み込む
	void LoadCsvSwitch1Data(void);

	// 外部ファイルからスイッチ2のステージデータを読み込む
	void LoadCsvSwitch2Data(void);

	// 外部ファイルからスイッチ3のステージデータを読み込む
	void LoadCsvSwitch3Data(void);

	// 外部ファイルからスイッチ4のステージデータを読み込む
	void LoadCsvSwitch4Data(void);

	// 外部ファイルからスイッチ5のステージデータを読み込む
	void LoadCsvSwitch5Data(void);

	// 外部ファイルからスイッチ6のステージデータを読み込む
	void LoadCsvSwitch6Data(void);

	// 外部ファイルからスイッチ7のステージデータを読み込む
	void LoadCsvSwitch7Data(void);

	// 外部ファイルからスイッチ8のステージデータを読み込む
	void LoadCsvSwitch8Data(void);

	// ステージの衝突用のチップ番号を取得する
	int GetCollisionStageNo(Vector2 mapPos);

	// ドアの衝突用のチップ番号を取得する
	int GetCollisionDoorNo(Vector2 mapPos);

	// 脱出ゲートのチップ番号を取得する
	int GetGateNo(Vector2 mapPos);

	// 宝箱のマップチップ番号を取得する
	int GetSwitch1No(Vector2 mapPos);

	// 宝箱のマップチップ番号を取得する
	int GetSwitch2No(Vector2 mapPos);

	// 宝箱のマップチップ番号を取得する
	int GetSwitch3No(Vector2 mapPos);

	// 宝箱のマップチップ番号を取得する
	int GetSwitch4No(Vector2 mapPos);

	// ドアのマップチップ番号を取得する
	int GetDoorNo(Vector2 mapPos);

	// ドア1かどうか
	bool IsDoor1(int mapChipNo);

	// ドア2かどうか
	bool IsDoor2(int mapChuipNo);

	// ドア3かどうか
	bool IsDoor3(int mapChipNo);

	// ドア4かどうか
	bool IsDoor4(int mapChipNo);

	// 脱出ゲートかどうか
	bool IsGate(int mapChipNo);

private:

	// ゲームシーンのポインタ変数
	GameScene* gameScene_;

	// マップ画像
	int imgMapChips_[NUM_MAP_CHIPS];

	//// 使用しているマップ
	//int usedMap_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// 使用しているマップの種類
	TYPE type_;

	// 使用しているマップのサイズ
	Vector2 usedMapSize_;

	// ドア1の状態
	bool isOpenDoor1_;

	// ドア2の状態
	bool isOpenDoor2_;

	// ドア3の状態
	bool isOpenDoor3_;

	// ドア4の状態
	bool isOpenDoor4_;

	// 床・壁のマップ
	int StageMap_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];
	
	// ドアの背景のマップ
	int DoorBackMap_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// ドアのマップ
	int DoorMap_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// ドアの衝突マップ
	int CollisionDoorMap_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// オブジェクトのマップ
	int ObjectMap_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// 床・壁の衝突のマップ
	int CollisionStageMap_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// 脱出ゲートのマップ
	int GateMap_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// スイッチ1のマップ
	int Switch1Map_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// スイッチ2のマップ
	int Switch2Map_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// スイッチ3のマップ
	int Switch3Map_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// スイッチ4のマップ
	int Switch4Map_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// スイッチ5のマップ
	int Switch5Map_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// スイッチ6のマップ
	int Switch6Map_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// スイッチ7のマップ
	int Switch7Map_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// スイッチ8のマップ
	int Switch8Map_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

};



