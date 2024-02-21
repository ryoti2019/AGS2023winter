#include<string>
#include <fstream>
#include <sstream>
#include <DxLib.h>
#include "AsoUtility.h"
#include "Application.h"
#include "GameScene.h"
#include "Stage.h"
#include "Player.h"

Stage::Stage(void)
{
}

Stage::~Stage(void)
{
}

void Stage::Init(GameScene* scene)
{

	// ゲームシーンの機能をいつでも使えるようにメンバ変数に格納
	gameScene_ = scene;

	// 分割された画像を読み込む
	LoadDivGraph("Image/Stage/tile.png",
		NUM_MAP_CHIPS,
		NUM_MAP_CHIPS_X,
		NUM_MAP_CHIPS_Y,
		CHIP_SIZE_X,
		CHIP_SIZE_Y,
		&imgMapChips_[0]
	);
	// マップのサイズを設定する
	usedMapSize_.x = MAP_MAX_SIZE_X;
	usedMapSize_.y = MAP_MAX_SIZE_Y;

	// 外部ファイルから床・壁ステージデータを読み込む
	LoadCsvWallData();

	// 外部ファイルからドアのステージデータを読み込む
	LoadCsvDoorData();

	// 外部ファイルからドアの衝突のステージデータを読み込む
	LoadCsvCollisionDoorData();

	// 外部ファイルからオブジェクトステージデータを読み込む
	LoadCsvObjectData();

	// 外部ファイルから衝突ステージデータを読み込む
	LoadCsvCollisionStageData();

	// 外部ファイルから脱出ゲートステージデータを読み込む
	LoadCsvGateData();

	// 外部ファイルからスイッチ1データを読み込む
	LoadCsvSwitch1Data();

	// 外部ファイルからスイッチ2データを読み込む
	LoadCsvSwitch2Data();

	// 外部ファイルからスイッチ3データを読み込む
	LoadCsvSwitch3Data();

	// 外部ファイルからスイッチ4データを読み込む
	LoadCsvSwitch4Data();

	// 外部ファイルからスイッチ5データを読み込む
	LoadCsvSwitch5Data();

	// 外部ファイルからスイッチ6データを読み込む
	LoadCsvSwitch6Data();

	// 外部ファイルからスイッチ7データを読み込む
	LoadCsvSwitch7Data();

	// 外部ファイルからスイッチ8データを読み込む
	LoadCsvSwitch8Data();

}

void Stage::Update(void)
{
}

void Stage::Draw(void)
{

	Vector2 cameraPos = gameScene_->GetCameraPos();

	// マップ表示
	for (int y = 0; y < usedMapSize_.y; y++)
	{
		for (int x = 0; x < usedMapSize_.x; x++)
		{

			// 床・壁
			int chipNo = StageMap_[y][x];
			int imgHandle = imgMapChips_[chipNo];

			DrawGraph(x * CHIP_SIZE_X - cameraPos.x, y * CHIP_SIZE_Y - cameraPos.y, imgHandle, true);

			// ドア
			chipNo = DoorMap_[y][x];
			imgHandle = imgMapChips_[chipNo];

			if (!(IsDoor1(chipNo) && gameScene_->GetKey1())
			 && !(IsDoor2(chipNo) && gameScene_->GetKey2())
			 && !(IsDoor3(chipNo) && gameScene_->GetKey3())
			 && !(IsDoor4(chipNo) && gameScene_->GetKey4()))
			{
				DrawGraph(x * CHIP_SIZE_X - cameraPos.x, y * CHIP_SIZE_Y - cameraPos.y, imgHandle, true);
			}

			// オブジェクト
			chipNo = ObjectMap_[y][x];
			imgHandle = imgMapChips_[chipNo];

			DrawGraph(x * CHIP_SIZE_X - cameraPos.x, y * CHIP_SIZE_Y - cameraPos.y, imgHandle, true);

			// スイッチ1
			chipNo = Switch1Map_[y][x];
			imgHandle = imgMapChips_[chipNo];

			if (!(gameScene_->GetKey1()))
			{
				DrawGraph(x * CHIP_SIZE_X - cameraPos.x, y * CHIP_SIZE_Y - cameraPos.y, imgHandle, true);
			}

			// スイッチ2
			chipNo = Switch2Map_[y][x];
			imgHandle = imgMapChips_[chipNo];

			if (!(gameScene_->GetKey2()))
			{
				DrawGraph(x * CHIP_SIZE_X - cameraPos.x, y * CHIP_SIZE_Y - cameraPos.y, imgHandle, true);
			}

			// スイッチ3
			chipNo = Switch3Map_[y][x];
			imgHandle = imgMapChips_[chipNo];

			if (!(gameScene_->GetKey3()))
			{
				DrawGraph(x * CHIP_SIZE_X - cameraPos.x, y * CHIP_SIZE_Y - cameraPos.y, imgHandle, true);
			}

			// スイッチ4
			chipNo = Switch4Map_[y][x];
			imgHandle = imgMapChips_[chipNo];

			if (!(gameScene_->GetKey4()))
			{
				DrawGraph(x * CHIP_SIZE_X - cameraPos.x, y * CHIP_SIZE_Y - cameraPos.y, imgHandle, true);
			}

			// スイッチ5
			chipNo = Switch5Map_[y][x];
			imgHandle = imgMapChips_[chipNo];

			if (gameScene_->GetKey1())
			{
				DrawGraph(x * CHIP_SIZE_X - cameraPos.x, y * CHIP_SIZE_Y - cameraPos.y, imgHandle, true);
			}

			// スイッチ6
			chipNo = Switch6Map_[y][x];
			imgHandle = imgMapChips_[chipNo];

			if (gameScene_->GetKey2())
			{
				DrawGraph(x * CHIP_SIZE_X - cameraPos.x, y * CHIP_SIZE_Y - cameraPos.y, imgHandle, true);
			}

			// スイッチ7
			chipNo = Switch7Map_[y][x];
			imgHandle = imgMapChips_[chipNo];

			if (gameScene_->GetKey3())
			{
				DrawGraph(x * CHIP_SIZE_X - cameraPos.x, y * CHIP_SIZE_Y - cameraPos.y, imgHandle, true);
			}

			// スイッチ8
			chipNo = Switch8Map_[y][x];
			imgHandle = imgMapChips_[chipNo];

			if (gameScene_->GetKey4())
			{
				DrawGraph(x * CHIP_SIZE_X - cameraPos.x, y * CHIP_SIZE_Y - cameraPos.y, imgHandle, true);
			}
		}

	}
}

void Stage::Release(void)
{

	// 読み込んだ画像の開放
	for (int i = 0; i < NUM_MAP_CHIPS; i++)
	{
		DeleteGraph(imgMapChips_[i]);
	}

}

void Stage::LoadCsvWallData(void)
{

	std::ifstream ifs = std::ifstream("Data/ステージ1_床・壁.csv");
	if (!ifs)
	{
		// エラーが発生
		return;
	}

	// 地上データの初期化
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			StageMap_[y][x] = -1;
		}
	}

	// ファイルを1行ずつ読み込んで、lineに格納する
	std::string line;					// １行の文字列情報
	std::vector < std::string> split;	// １行の文字列情報
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// ファイルを１行ずつ読み込む
	while (getline(ifs, line))
	{

		// 1行分の文字列をカンマ区切りで分割
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string型からint型に変換
			chipNo = stoi(split[x]);

			// ２次元配列にマップチップ番号を格納
			StageMap_[y][x] = chipNo;

		}

		y++;
	}

}

void Stage::LoadCsvDoorData(void)
{


	std::ifstream ifs = std::ifstream("Data/ステージ1_ドア.csv");
	if (!ifs)
	{
		// エラーが発生
		return;
	}

	// ドアの背景データの初期化
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			DoorMap_[y][x] = -1;
		}
	}

	// ファイルを1行ずつ読み込んで、lineに格納する
	std::string line;					// １行の文字列情報
	std::vector < std::string> split;	// １行の文字列情報
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// ファイルを１行ずつ読み込む
	while (getline(ifs, line))
	{

		// 1行分の文字列をカンマ区切りで分割
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string型からint型に変換
			chipNo = stoi(split[x]);

			// ２次元配列にマップチップ番号を格納
			DoorMap_[y][x] = chipNo;

		}

		y++;
	}


}

void Stage::LoadCsvCollisionDoorData(void)
{

	std::ifstream ifs = std::ifstream("Data/ステージ1_ドアの衝突.csv");
	if (!ifs)
	{
		// エラーが発生
		return;
	}

	// 地上データの初期化
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			CollisionDoorMap_[y][x] = -1;
		}
	}

	// ファイルを1行ずつ読み込んで、lineに格納する
	std::string line;					// １行の文字列情報
	std::vector < std::string> split;	// １行の文字列情報
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// ファイルを１行ずつ読み込む
	while (getline(ifs, line))
	{

		// 1行分の文字列をカンマ区切りで分割
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string型からint型に変換
			chipNo = stoi(split[x]);

			// ２次元配列にマップチップ番号を格納
			CollisionDoorMap_[y][x] = chipNo;

		}

		y++;
	}

}

void Stage::LoadCsvObjectData(void)
{

	std::ifstream ifs = std::ifstream("Data/ステージ1_オブジェクト.csv");
	if (!ifs)
	{
		// エラーが発生
		return;
	}

	// 地上データの初期化
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			ObjectMap_[y][x] = -1;
		}
	}

	// ファイルを1行ずつ読み込んで、lineに格納する
	std::string line;					// １行の文字列情報
	std::vector < std::string> split;	// １行の文字列情報
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// ファイルを１行ずつ読み込む
	while (getline(ifs, line))
	{

		// 1行分の文字列をカンマ区切りで分割
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string型からint型に変換
			chipNo = stoi(split[x]);

			// ２次元配列にマップチップ番号を格納
			ObjectMap_[y][x] = chipNo;

		}

		y++;
	}

}

void Stage::LoadCsvCollisionStageData(void)
{

	std::ifstream ifs = std::ifstream("Data/ステージ1_床・壁の衝突.csv");
	if (!ifs)
	{
		// エラーが発生
		return;
	}

	// 地上データの初期化
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			CollisionStageMap_[y][x] = -1;
		}
	}

	// ファイルを1行ずつ読み込んで、lineに格納する
	std::string line;					// １行の文字列情報
	std::vector < std::string> split;	// １行の文字列情報
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// ファイルを１行ずつ読み込む
	while (getline(ifs, line))
	{

		// 1行分の文字列をカンマ区切りで分割
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string型からint型に変換
			chipNo = stoi(split[x]);

			// ２次元配列にマップチップ番号を格納
			CollisionStageMap_[y][x] = chipNo;

		}

		y++;
	}

}

void Stage::LoadCsvGateData(void)
{

	std::ifstream ifs = std::ifstream("Data/ステージ1_脱出ゲート.csv");
	if (!ifs)
	{
		// エラーが発生
		return;
	}

	// 地上データの初期化
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			GateMap_[y][x] = -1;
		}
	}

	// ファイルを1行ずつ読み込んで、lineに格納する
	std::string line;					// １行の文字列情報
	std::vector < std::string> split;	// １行の文字列情報
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// ファイルを１行ずつ読み込む
	while (getline(ifs, line))
	{

		// 1行分の文字列をカンマ区切りで分割
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string型からint型に変換
			chipNo = stoi(split[x]);

			// ２次元配列にマップチップ番号を格納
			GateMap_[y][x] = chipNo;

		}
		y++;
	}

}

void Stage::LoadCsvSwitch1Data(void)
{

	std::ifstream ifs = std::ifstream("Data/ステージ1_スイッチ1.csv");
	if (!ifs)
	{
		// エラーが発生
		return;
	}

	// 地上データの初期化
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			Switch1Map_[y][x] = -1;
		}
	}

	// ファイルを1行ずつ読み込んで、lineに格納する
	std::string line;					// １行の文字列情報
	std::vector < std::string> split;	// １行の文字列情報
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// ファイルを１行ずつ読み込む
	while (getline(ifs, line))
	{

		// 1行分の文字列をカンマ区切りで分割
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string型からint型に変換
			chipNo = stoi(split[x]);

			// ２次元配列にマップチップ番号を格納
			Switch1Map_[y][x] = chipNo;

		}

		y++;
	}

}

void Stage::LoadCsvSwitch2Data(void)
{

	std::ifstream ifs = std::ifstream("Data/ステージ1_スイッチ2.csv");
	if (!ifs)
	{
		// エラーが発生
		return;
	}

	// 地上データの初期化
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			Switch2Map_[y][x] = -1;
		}
	}

	// ファイルを1行ずつ読み込んで、lineに格納する
	std::string line;					// １行の文字列情報
	std::vector < std::string> split;	// １行の文字列情報
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// ファイルを１行ずつ読み込む
	while (getline(ifs, line))
	{

		// 1行分の文字列をカンマ区切りで分割
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string型からint型に変換
			chipNo = stoi(split[x]);

			// ２次元配列にマップチップ番号を格納
			Switch2Map_[y][x] = chipNo;

		}

		y++;
	}

}

void Stage::LoadCsvSwitch3Data(void)
{

	std::ifstream ifs = std::ifstream("Data/ステージ1_スイッチ3.csv");
	if (!ifs)
	{
		// エラーが発生
		return;
	}

	// 地上データの初期化
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			Switch3Map_[y][x] = -1;
		}
	}

	// ファイルを1行ずつ読み込んで、lineに格納する
	std::string line;					// １行の文字列情報
	std::vector < std::string> split;	// １行の文字列情報
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// ファイルを１行ずつ読み込む
	while (getline(ifs, line))
	{

		// 1行分の文字列をカンマ区切りで分割
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string型からint型に変換
			chipNo = stoi(split[x]);

			// ２次元配列にマップチップ番号を格納
			Switch3Map_[y][x] = chipNo;

		}

		y++;
	}

}

void Stage::LoadCsvSwitch4Data(void)
{

	std::ifstream ifs = std::ifstream("Data/ステージ1_スイッチ4.csv");
	if (!ifs)
	{
		// エラーが発生
		return;
	}

	// 地上データの初期化
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			Switch4Map_[y][x] = -1;
		}
	}

	// ファイルを1行ずつ読み込んで、lineに格納する
	std::string line;					// １行の文字列情報
	std::vector < std::string> split;	// １行の文字列情報
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// ファイルを１行ずつ読み込む
	while (getline(ifs, line))
	{

		// 1行分の文字列をカンマ区切りで分割
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string型からint型に変換
			chipNo = stoi(split[x]);

			// ２次元配列にマップチップ番号を格納
			Switch4Map_[y][x] = chipNo;

		}

		y++;
	}

}

void Stage::LoadCsvSwitch5Data(void)
{

	std::ifstream ifs = std::ifstream("Data/ステージ1_スイッチ5.csv");
	if (!ifs)
	{
		// エラーが発生
		return;
	}

	// 地上データの初期化
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			Switch5Map_[y][x] = -1;
		}
	}

	// ファイルを1行ずつ読み込んで、lineに格納する
	std::string line;					// １行の文字列情報
	std::vector < std::string> split;	// １行の文字列情報
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// ファイルを１行ずつ読み込む
	while (getline(ifs, line))
	{

		// 1行分の文字列をカンマ区切りで分割
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string型からint型に変換
			chipNo = stoi(split[x]);

			// ２次元配列にマップチップ番号を格納
			Switch5Map_[y][x] = chipNo;

		}

		y++;
	}

}

void Stage::LoadCsvSwitch6Data(void)
{

	std::ifstream ifs = std::ifstream("Data/ステージ1_スイッチ6.csv");
	if (!ifs)
	{
		// エラーが発生
		return;
	}

	// 地上データの初期化
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			Switch6Map_[y][x] = -1;
		}
	}

	// ファイルを1行ずつ読み込んで、lineに格納する
	std::string line;					// １行の文字列情報
	std::vector < std::string> split;	// １行の文字列情報
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// ファイルを１行ずつ読み込む
	while (getline(ifs, line))
	{

		// 1行分の文字列をカンマ区切りで分割
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string型からint型に変換
			chipNo = stoi(split[x]);

			// ２次元配列にマップチップ番号を格納
			Switch6Map_[y][x] = chipNo;

		}

		y++;
	}

}

void Stage::LoadCsvSwitch7Data(void)
{

	std::ifstream ifs = std::ifstream("Data/ステージ1_スイッチ7.csv");
	if (!ifs)
	{
		// エラーが発生
		return;
	}

	// 地上データの初期化
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			Switch7Map_[y][x] = -1;
		}
	}

	// ファイルを1行ずつ読み込んで、lineに格納する
	std::string line;					// １行の文字列情報
	std::vector < std::string> split;	// １行の文字列情報
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// ファイルを１行ずつ読み込む
	while (getline(ifs, line))
	{

		// 1行分の文字列をカンマ区切りで分割
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string型からint型に変換
			chipNo = stoi(split[x]);

			// ２次元配列にマップチップ番号を格納
			Switch7Map_[y][x] = chipNo;

		}

		y++;
	}

}

void Stage::LoadCsvSwitch8Data(void)
{

	std::ifstream ifs = std::ifstream("Data/ステージ1_スイッチ8.csv");
	if (!ifs)
	{
		// エラーが発生
		return;
	}

	// 地上データの初期化
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			Switch8Map_[y][x] = -1;
		}
	}

	// ファイルを1行ずつ読み込んで、lineに格納する
	std::string line;					// １行の文字列情報
	std::vector < std::string> split;	// １行の文字列情報
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// ファイルを１行ずつ読み込む
	while (getline(ifs, line))
	{

		// 1行分の文字列をカンマ区切りで分割
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string型からint型に変換
			chipNo = stoi(split[x]);

			// ２次元配列にマップチップ番号を格納
			Switch8Map_[y][x] = chipNo;

		}

		y++;
	}

}

int Stage::GetCollisionStageNo(Vector2 mapPos)
{

	int ret = CollisionStageMap_[mapPos.y][mapPos.x];

	return ret;

}

int Stage::GetCollisionDoorNo(Vector2 mapPos)
{

	int ret = CollisionDoorMap_[mapPos.y][mapPos.x];

	return ret;

}

int Stage::GetGateNo(Vector2 mapPos)
{

	int ret = GateMap_[mapPos.y][mapPos.x];

	return ret;

}

int Stage::GetSwitch1No(Vector2 mapPos)
{

	int ret = Switch1Map_[mapPos.y][mapPos.x];

	return ret;

}

int Stage::GetSwitch2No(Vector2 mapPos)
{

	int ret = Switch2Map_[mapPos.y][mapPos.x];

	return ret;

}

int Stage::GetSwitch3No(Vector2 mapPos)
{

	int ret = Switch3Map_[mapPos.y][mapPos.x];

	return ret;

}

int Stage::GetSwitch4No(Vector2 mapPos)
{

	int ret = Switch4Map_[mapPos.y][mapPos.x];

	return ret;

}

int Stage::GetDoorNo(Vector2 mapPos)
{

	int ret = DoorMap_[mapPos.y][mapPos.x];

	return ret;

}

bool Stage::IsDoor1(int mapChipNo)
{

	if (mapChipNo == 144
		|| mapChipNo == 145
		|| mapChipNo == 146
		|| mapChipNo == 147
		|| mapChipNo == 148
		|| mapChipNo == 149)
	{
		return true;
	}

	return false;

}

bool Stage::IsDoor2(int mapChipNo)
{
	
	if (mapChipNo == 162
		|| mapChipNo == 163
		|| mapChipNo == 164
		|| mapChipNo == 165
		|| mapChipNo == 166
		|| mapChipNo == 167)
	{
		return true;
	}

	return false;

}

bool Stage::IsDoor3(int mapChipNo)
{

	if (mapChipNo == 150
		|| mapChipNo == 151
		|| mapChipNo == 152
		|| mapChipNo == 153
		|| mapChipNo == 154
		|| mapChipNo == 155)
	{
		return true;
	}

	return false;

}

bool Stage::IsDoor4(int mapChipNo)
{

	if (mapChipNo == 156
		|| mapChipNo == 157
		|| mapChipNo == 158
		|| mapChipNo == 159
		|| mapChipNo == 160
		|| mapChipNo == 161)
	{
		return true;
	}

	return false;

}

bool Stage::IsGate(int mapChipNo)
{
	if (mapChipNo == 15)
	{
		return true;
	}

	return false;
}

