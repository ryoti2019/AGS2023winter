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

	// �Q�[���V�[���̋@�\�����ł��g����悤�Ƀ����o�ϐ��Ɋi�[
	gameScene_ = scene;

	// �������ꂽ�摜��ǂݍ���
	LoadDivGraph("Image/Stage/tile.png",
		NUM_MAP_CHIPS,
		NUM_MAP_CHIPS_X,
		NUM_MAP_CHIPS_Y,
		CHIP_SIZE_X,
		CHIP_SIZE_Y,
		&imgMapChips_[0]
	);
	// �}�b�v�̃T�C�Y��ݒ肷��
	usedMapSize_.x = MAP_MAX_SIZE_X;
	usedMapSize_.y = MAP_MAX_SIZE_Y;

	// �O���t�@�C�����珰�E�ǃX�e�[�W�f�[�^��ǂݍ���
	LoadCsvWallData();

	// �O���t�@�C������h�A�̃X�e�[�W�f�[�^��ǂݍ���
	LoadCsvDoorData();

	// �O���t�@�C������h�A�̏Փ˂̃X�e�[�W�f�[�^��ǂݍ���
	LoadCsvCollisionDoorData();

	// �O���t�@�C������I�u�W�F�N�g�X�e�[�W�f�[�^��ǂݍ���
	LoadCsvObjectData();

	// �O���t�@�C������Փ˃X�e�[�W�f�[�^��ǂݍ���
	LoadCsvCollisionStageData();

	// �O���t�@�C������E�o�Q�[�g�X�e�[�W�f�[�^��ǂݍ���
	LoadCsvGateData();

	// �O���t�@�C������X�C�b�`1�f�[�^��ǂݍ���
	LoadCsvSwitch1Data();

	// �O���t�@�C������X�C�b�`2�f�[�^��ǂݍ���
	LoadCsvSwitch2Data();

	// �O���t�@�C������X�C�b�`3�f�[�^��ǂݍ���
	LoadCsvSwitch3Data();

	// �O���t�@�C������X�C�b�`4�f�[�^��ǂݍ���
	LoadCsvSwitch4Data();

	// �O���t�@�C������X�C�b�`5�f�[�^��ǂݍ���
	LoadCsvSwitch5Data();

	// �O���t�@�C������X�C�b�`6�f�[�^��ǂݍ���
	LoadCsvSwitch6Data();

	// �O���t�@�C������X�C�b�`7�f�[�^��ǂݍ���
	LoadCsvSwitch7Data();

	// �O���t�@�C������X�C�b�`8�f�[�^��ǂݍ���
	LoadCsvSwitch8Data();

}

void Stage::Update(void)
{
}

void Stage::Draw(void)
{

	Vector2 cameraPos = gameScene_->GetCameraPos();

	// �}�b�v�\��
	for (int y = 0; y < usedMapSize_.y; y++)
	{
		for (int x = 0; x < usedMapSize_.x; x++)
		{

			// ���E��
			int chipNo = StageMap_[y][x];
			int imgHandle = imgMapChips_[chipNo];

			DrawGraph(x * CHIP_SIZE_X - cameraPos.x, y * CHIP_SIZE_Y - cameraPos.y, imgHandle, true);

			// �h�A
			chipNo = DoorMap_[y][x];
			imgHandle = imgMapChips_[chipNo];

			if (!(IsDoor1(chipNo) && gameScene_->GetKey1())
			 && !(IsDoor2(chipNo) && gameScene_->GetKey2())
			 && !(IsDoor3(chipNo) && gameScene_->GetKey3())
			 && !(IsDoor4(chipNo) && gameScene_->GetKey4()))
			{
				DrawGraph(x * CHIP_SIZE_X - cameraPos.x, y * CHIP_SIZE_Y - cameraPos.y, imgHandle, true);
			}

			// �I�u�W�F�N�g
			chipNo = ObjectMap_[y][x];
			imgHandle = imgMapChips_[chipNo];

			DrawGraph(x * CHIP_SIZE_X - cameraPos.x, y * CHIP_SIZE_Y - cameraPos.y, imgHandle, true);

			// �X�C�b�`1
			chipNo = Switch1Map_[y][x];
			imgHandle = imgMapChips_[chipNo];

			if (!(gameScene_->GetKey1()))
			{
				DrawGraph(x * CHIP_SIZE_X - cameraPos.x, y * CHIP_SIZE_Y - cameraPos.y, imgHandle, true);
			}

			// �X�C�b�`2
			chipNo = Switch2Map_[y][x];
			imgHandle = imgMapChips_[chipNo];

			if (!(gameScene_->GetKey2()))
			{
				DrawGraph(x * CHIP_SIZE_X - cameraPos.x, y * CHIP_SIZE_Y - cameraPos.y, imgHandle, true);
			}

			// �X�C�b�`3
			chipNo = Switch3Map_[y][x];
			imgHandle = imgMapChips_[chipNo];

			if (!(gameScene_->GetKey3()))
			{
				DrawGraph(x * CHIP_SIZE_X - cameraPos.x, y * CHIP_SIZE_Y - cameraPos.y, imgHandle, true);
			}

			// �X�C�b�`4
			chipNo = Switch4Map_[y][x];
			imgHandle = imgMapChips_[chipNo];

			if (!(gameScene_->GetKey4()))
			{
				DrawGraph(x * CHIP_SIZE_X - cameraPos.x, y * CHIP_SIZE_Y - cameraPos.y, imgHandle, true);
			}

			// �X�C�b�`5
			chipNo = Switch5Map_[y][x];
			imgHandle = imgMapChips_[chipNo];

			if (gameScene_->GetKey1())
			{
				DrawGraph(x * CHIP_SIZE_X - cameraPos.x, y * CHIP_SIZE_Y - cameraPos.y, imgHandle, true);
			}

			// �X�C�b�`6
			chipNo = Switch6Map_[y][x];
			imgHandle = imgMapChips_[chipNo];

			if (gameScene_->GetKey2())
			{
				DrawGraph(x * CHIP_SIZE_X - cameraPos.x, y * CHIP_SIZE_Y - cameraPos.y, imgHandle, true);
			}

			// �X�C�b�`7
			chipNo = Switch7Map_[y][x];
			imgHandle = imgMapChips_[chipNo];

			if (gameScene_->GetKey3())
			{
				DrawGraph(x * CHIP_SIZE_X - cameraPos.x, y * CHIP_SIZE_Y - cameraPos.y, imgHandle, true);
			}

			// �X�C�b�`8
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

	// �ǂݍ��񂾉摜�̊J��
	for (int i = 0; i < NUM_MAP_CHIPS; i++)
	{
		DeleteGraph(imgMapChips_[i]);
	}

}

void Stage::LoadCsvWallData(void)
{

	std::ifstream ifs = std::ifstream("Data/�X�e�[�W1_���E��.csv");
	if (!ifs)
	{
		// �G���[������
		return;
	}

	// �n��f�[�^�̏�����
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			StageMap_[y][x] = -1;
		}
	}

	// �t�@�C����1�s���ǂݍ���ŁAline�Ɋi�[����
	std::string line;					// �P�s�̕�������
	std::vector < std::string> split;	// �P�s�̕�������
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// �t�@�C�����P�s���ǂݍ���
	while (getline(ifs, line))
	{

		// 1�s���̕�������J���}��؂�ŕ���
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string�^����int�^�ɕϊ�
			chipNo = stoi(split[x]);

			// �Q�����z��Ƀ}�b�v�`�b�v�ԍ����i�[
			StageMap_[y][x] = chipNo;

		}

		y++;
	}

}

void Stage::LoadCsvDoorData(void)
{


	std::ifstream ifs = std::ifstream("Data/�X�e�[�W1_�h�A.csv");
	if (!ifs)
	{
		// �G���[������
		return;
	}

	// �h�A�̔w�i�f�[�^�̏�����
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			DoorMap_[y][x] = -1;
		}
	}

	// �t�@�C����1�s���ǂݍ���ŁAline�Ɋi�[����
	std::string line;					// �P�s�̕�������
	std::vector < std::string> split;	// �P�s�̕�������
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// �t�@�C�����P�s���ǂݍ���
	while (getline(ifs, line))
	{

		// 1�s���̕�������J���}��؂�ŕ���
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string�^����int�^�ɕϊ�
			chipNo = stoi(split[x]);

			// �Q�����z��Ƀ}�b�v�`�b�v�ԍ����i�[
			DoorMap_[y][x] = chipNo;

		}

		y++;
	}


}

void Stage::LoadCsvCollisionDoorData(void)
{

	std::ifstream ifs = std::ifstream("Data/�X�e�[�W1_�h�A�̏Փ�.csv");
	if (!ifs)
	{
		// �G���[������
		return;
	}

	// �n��f�[�^�̏�����
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			CollisionDoorMap_[y][x] = -1;
		}
	}

	// �t�@�C����1�s���ǂݍ���ŁAline�Ɋi�[����
	std::string line;					// �P�s�̕�������
	std::vector < std::string> split;	// �P�s�̕�������
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// �t�@�C�����P�s���ǂݍ���
	while (getline(ifs, line))
	{

		// 1�s���̕�������J���}��؂�ŕ���
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string�^����int�^�ɕϊ�
			chipNo = stoi(split[x]);

			// �Q�����z��Ƀ}�b�v�`�b�v�ԍ����i�[
			CollisionDoorMap_[y][x] = chipNo;

		}

		y++;
	}

}

void Stage::LoadCsvObjectData(void)
{

	std::ifstream ifs = std::ifstream("Data/�X�e�[�W1_�I�u�W�F�N�g.csv");
	if (!ifs)
	{
		// �G���[������
		return;
	}

	// �n��f�[�^�̏�����
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			ObjectMap_[y][x] = -1;
		}
	}

	// �t�@�C����1�s���ǂݍ���ŁAline�Ɋi�[����
	std::string line;					// �P�s�̕�������
	std::vector < std::string> split;	// �P�s�̕�������
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// �t�@�C�����P�s���ǂݍ���
	while (getline(ifs, line))
	{

		// 1�s���̕�������J���}��؂�ŕ���
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string�^����int�^�ɕϊ�
			chipNo = stoi(split[x]);

			// �Q�����z��Ƀ}�b�v�`�b�v�ԍ����i�[
			ObjectMap_[y][x] = chipNo;

		}

		y++;
	}

}

void Stage::LoadCsvCollisionStageData(void)
{

	std::ifstream ifs = std::ifstream("Data/�X�e�[�W1_���E�ǂ̏Փ�.csv");
	if (!ifs)
	{
		// �G���[������
		return;
	}

	// �n��f�[�^�̏�����
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			CollisionStageMap_[y][x] = -1;
		}
	}

	// �t�@�C����1�s���ǂݍ���ŁAline�Ɋi�[����
	std::string line;					// �P�s�̕�������
	std::vector < std::string> split;	// �P�s�̕�������
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// �t�@�C�����P�s���ǂݍ���
	while (getline(ifs, line))
	{

		// 1�s���̕�������J���}��؂�ŕ���
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string�^����int�^�ɕϊ�
			chipNo = stoi(split[x]);

			// �Q�����z��Ƀ}�b�v�`�b�v�ԍ����i�[
			CollisionStageMap_[y][x] = chipNo;

		}

		y++;
	}

}

void Stage::LoadCsvGateData(void)
{

	std::ifstream ifs = std::ifstream("Data/�X�e�[�W1_�E�o�Q�[�g.csv");
	if (!ifs)
	{
		// �G���[������
		return;
	}

	// �n��f�[�^�̏�����
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			GateMap_[y][x] = -1;
		}
	}

	// �t�@�C����1�s���ǂݍ���ŁAline�Ɋi�[����
	std::string line;					// �P�s�̕�������
	std::vector < std::string> split;	// �P�s�̕�������
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// �t�@�C�����P�s���ǂݍ���
	while (getline(ifs, line))
	{

		// 1�s���̕�������J���}��؂�ŕ���
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string�^����int�^�ɕϊ�
			chipNo = stoi(split[x]);

			// �Q�����z��Ƀ}�b�v�`�b�v�ԍ����i�[
			GateMap_[y][x] = chipNo;

		}
		y++;
	}

}

void Stage::LoadCsvSwitch1Data(void)
{

	std::ifstream ifs = std::ifstream("Data/�X�e�[�W1_�X�C�b�`1.csv");
	if (!ifs)
	{
		// �G���[������
		return;
	}

	// �n��f�[�^�̏�����
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			Switch1Map_[y][x] = -1;
		}
	}

	// �t�@�C����1�s���ǂݍ���ŁAline�Ɋi�[����
	std::string line;					// �P�s�̕�������
	std::vector < std::string> split;	// �P�s�̕�������
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// �t�@�C�����P�s���ǂݍ���
	while (getline(ifs, line))
	{

		// 1�s���̕�������J���}��؂�ŕ���
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string�^����int�^�ɕϊ�
			chipNo = stoi(split[x]);

			// �Q�����z��Ƀ}�b�v�`�b�v�ԍ����i�[
			Switch1Map_[y][x] = chipNo;

		}

		y++;
	}

}

void Stage::LoadCsvSwitch2Data(void)
{

	std::ifstream ifs = std::ifstream("Data/�X�e�[�W1_�X�C�b�`2.csv");
	if (!ifs)
	{
		// �G���[������
		return;
	}

	// �n��f�[�^�̏�����
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			Switch2Map_[y][x] = -1;
		}
	}

	// �t�@�C����1�s���ǂݍ���ŁAline�Ɋi�[����
	std::string line;					// �P�s�̕�������
	std::vector < std::string> split;	// �P�s�̕�������
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// �t�@�C�����P�s���ǂݍ���
	while (getline(ifs, line))
	{

		// 1�s���̕�������J���}��؂�ŕ���
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string�^����int�^�ɕϊ�
			chipNo = stoi(split[x]);

			// �Q�����z��Ƀ}�b�v�`�b�v�ԍ����i�[
			Switch2Map_[y][x] = chipNo;

		}

		y++;
	}

}

void Stage::LoadCsvSwitch3Data(void)
{

	std::ifstream ifs = std::ifstream("Data/�X�e�[�W1_�X�C�b�`3.csv");
	if (!ifs)
	{
		// �G���[������
		return;
	}

	// �n��f�[�^�̏�����
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			Switch3Map_[y][x] = -1;
		}
	}

	// �t�@�C����1�s���ǂݍ���ŁAline�Ɋi�[����
	std::string line;					// �P�s�̕�������
	std::vector < std::string> split;	// �P�s�̕�������
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// �t�@�C�����P�s���ǂݍ���
	while (getline(ifs, line))
	{

		// 1�s���̕�������J���}��؂�ŕ���
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string�^����int�^�ɕϊ�
			chipNo = stoi(split[x]);

			// �Q�����z��Ƀ}�b�v�`�b�v�ԍ����i�[
			Switch3Map_[y][x] = chipNo;

		}

		y++;
	}

}

void Stage::LoadCsvSwitch4Data(void)
{

	std::ifstream ifs = std::ifstream("Data/�X�e�[�W1_�X�C�b�`4.csv");
	if (!ifs)
	{
		// �G���[������
		return;
	}

	// �n��f�[�^�̏�����
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			Switch4Map_[y][x] = -1;
		}
	}

	// �t�@�C����1�s���ǂݍ���ŁAline�Ɋi�[����
	std::string line;					// �P�s�̕�������
	std::vector < std::string> split;	// �P�s�̕�������
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// �t�@�C�����P�s���ǂݍ���
	while (getline(ifs, line))
	{

		// 1�s���̕�������J���}��؂�ŕ���
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string�^����int�^�ɕϊ�
			chipNo = stoi(split[x]);

			// �Q�����z��Ƀ}�b�v�`�b�v�ԍ����i�[
			Switch4Map_[y][x] = chipNo;

		}

		y++;
	}

}

void Stage::LoadCsvSwitch5Data(void)
{

	std::ifstream ifs = std::ifstream("Data/�X�e�[�W1_�X�C�b�`5.csv");
	if (!ifs)
	{
		// �G���[������
		return;
	}

	// �n��f�[�^�̏�����
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			Switch5Map_[y][x] = -1;
		}
	}

	// �t�@�C����1�s���ǂݍ���ŁAline�Ɋi�[����
	std::string line;					// �P�s�̕�������
	std::vector < std::string> split;	// �P�s�̕�������
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// �t�@�C�����P�s���ǂݍ���
	while (getline(ifs, line))
	{

		// 1�s���̕�������J���}��؂�ŕ���
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string�^����int�^�ɕϊ�
			chipNo = stoi(split[x]);

			// �Q�����z��Ƀ}�b�v�`�b�v�ԍ����i�[
			Switch5Map_[y][x] = chipNo;

		}

		y++;
	}

}

void Stage::LoadCsvSwitch6Data(void)
{

	std::ifstream ifs = std::ifstream("Data/�X�e�[�W1_�X�C�b�`6.csv");
	if (!ifs)
	{
		// �G���[������
		return;
	}

	// �n��f�[�^�̏�����
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			Switch6Map_[y][x] = -1;
		}
	}

	// �t�@�C����1�s���ǂݍ���ŁAline�Ɋi�[����
	std::string line;					// �P�s�̕�������
	std::vector < std::string> split;	// �P�s�̕�������
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// �t�@�C�����P�s���ǂݍ���
	while (getline(ifs, line))
	{

		// 1�s���̕�������J���}��؂�ŕ���
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string�^����int�^�ɕϊ�
			chipNo = stoi(split[x]);

			// �Q�����z��Ƀ}�b�v�`�b�v�ԍ����i�[
			Switch6Map_[y][x] = chipNo;

		}

		y++;
	}

}

void Stage::LoadCsvSwitch7Data(void)
{

	std::ifstream ifs = std::ifstream("Data/�X�e�[�W1_�X�C�b�`7.csv");
	if (!ifs)
	{
		// �G���[������
		return;
	}

	// �n��f�[�^�̏�����
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			Switch7Map_[y][x] = -1;
		}
	}

	// �t�@�C����1�s���ǂݍ���ŁAline�Ɋi�[����
	std::string line;					// �P�s�̕�������
	std::vector < std::string> split;	// �P�s�̕�������
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// �t�@�C�����P�s���ǂݍ���
	while (getline(ifs, line))
	{

		// 1�s���̕�������J���}��؂�ŕ���
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string�^����int�^�ɕϊ�
			chipNo = stoi(split[x]);

			// �Q�����z��Ƀ}�b�v�`�b�v�ԍ����i�[
			Switch7Map_[y][x] = chipNo;

		}

		y++;
	}

}

void Stage::LoadCsvSwitch8Data(void)
{

	std::ifstream ifs = std::ifstream("Data/�X�e�[�W1_�X�C�b�`8.csv");
	if (!ifs)
	{
		// �G���[������
		return;
	}

	// �n��f�[�^�̏�����
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			Switch8Map_[y][x] = -1;
		}
	}

	// �t�@�C����1�s���ǂݍ���ŁAline�Ɋi�[����
	std::string line;					// �P�s�̕�������
	std::vector < std::string> split;	// �P�s�̕�������
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// �t�@�C�����P�s���ǂݍ���
	while (getline(ifs, line))
	{

		// 1�s���̕�������J���}��؂�ŕ���
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string�^����int�^�ɕϊ�
			chipNo = stoi(split[x]);

			// �Q�����z��Ƀ}�b�v�`�b�v�ԍ����i�[
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

