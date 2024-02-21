#pragma once
#include "Vector2.h"
class GameScene;

class Stage
{

public:

	// �X�e�[�W�摜�̉��̕�����
	static constexpr int NUM_MAP_CHIPS_X = 24;

	// �X�e�[�W�摜�̏c�̕�����
	static constexpr int NUM_MAP_CHIPS_Y = 8;

	// �X�e�[�W�摜�̕�������
	static constexpr int
		NUM_MAP_CHIPS = NUM_MAP_CHIPS_X * NUM_MAP_CHIPS_Y;

	// �}�b�v�`�b�v�T�C�Y
	static constexpr int CHIP_SIZE_X = 32;
	static constexpr int CHIP_SIZE_Y = 32;

	// �}�b�v�̍ő�T�C�Y
	static constexpr int MAP_MAX_SIZE_X = 69;
	static constexpr int MAP_MAX_SIZE_Y = 70;

	// �}�b�v�̎��
	enum class TYPE
	{
		NONE,
		GROUND,
	};

	// �R���X�g���N�^
	Stage(void);

	// �f�X�g���N�^
	~Stage(void);

	void Init(GameScene* scene);
	void Update(void);
	void Draw(void);
	void Release(void);

	// �O���t�@�C�����珰�E�ǂ̃X�e�[�W�f�[�^��ǂݍ���
	void LoadCsvWallData(void);

	// �O���t�@�C������h�A�̃X�e�[�W�f�[�^��ǂݍ���
	void LoadCsvDoorData(void);

	// �O���t�@�C������h�A�̏Փ˂̃X�e�[�W�f�[�^��ǂݍ���
	void LoadCsvCollisionDoorData(void);

	// �O���t�@�C������I�u�W�F�N�g�̃X�e�[�W�f�[�^��ǂݍ���
	void LoadCsvObjectData(void);

	// �O���t�@�C�����珰�E�ǂ̏Փ˂̃X�e�[�W�f�[�^��ǂݍ���
	void LoadCsvCollisionStageData(void);

	// �O���t�@�C������E�o�Q�[�g�̃X�e�[�W�f�[�^��ǂݍ���
	void LoadCsvGateData(void);

	// �O���t�@�C������X�C�b�`1�̃X�e�[�W�f�[�^��ǂݍ���
	void LoadCsvSwitch1Data(void);

	// �O���t�@�C������X�C�b�`2�̃X�e�[�W�f�[�^��ǂݍ���
	void LoadCsvSwitch2Data(void);

	// �O���t�@�C������X�C�b�`3�̃X�e�[�W�f�[�^��ǂݍ���
	void LoadCsvSwitch3Data(void);

	// �O���t�@�C������X�C�b�`4�̃X�e�[�W�f�[�^��ǂݍ���
	void LoadCsvSwitch4Data(void);

	// �O���t�@�C������X�C�b�`5�̃X�e�[�W�f�[�^��ǂݍ���
	void LoadCsvSwitch5Data(void);

	// �O���t�@�C������X�C�b�`6�̃X�e�[�W�f�[�^��ǂݍ���
	void LoadCsvSwitch6Data(void);

	// �O���t�@�C������X�C�b�`7�̃X�e�[�W�f�[�^��ǂݍ���
	void LoadCsvSwitch7Data(void);

	// �O���t�@�C������X�C�b�`8�̃X�e�[�W�f�[�^��ǂݍ���
	void LoadCsvSwitch8Data(void);

	// �X�e�[�W�̏Փ˗p�̃`�b�v�ԍ����擾����
	int GetCollisionStageNo(Vector2 mapPos);

	// �h�A�̏Փ˗p�̃`�b�v�ԍ����擾����
	int GetCollisionDoorNo(Vector2 mapPos);

	// �E�o�Q�[�g�̃`�b�v�ԍ����擾����
	int GetGateNo(Vector2 mapPos);

	// �󔠂̃}�b�v�`�b�v�ԍ����擾����
	int GetSwitch1No(Vector2 mapPos);

	// �󔠂̃}�b�v�`�b�v�ԍ����擾����
	int GetSwitch2No(Vector2 mapPos);

	// �󔠂̃}�b�v�`�b�v�ԍ����擾����
	int GetSwitch3No(Vector2 mapPos);

	// �󔠂̃}�b�v�`�b�v�ԍ����擾����
	int GetSwitch4No(Vector2 mapPos);

	// �h�A�̃}�b�v�`�b�v�ԍ����擾����
	int GetDoorNo(Vector2 mapPos);

	// �h�A1���ǂ���
	bool IsDoor1(int mapChipNo);

	// �h�A2���ǂ���
	bool IsDoor2(int mapChuipNo);

	// �h�A3���ǂ���
	bool IsDoor3(int mapChipNo);

	// �h�A4���ǂ���
	bool IsDoor4(int mapChipNo);

	// �E�o�Q�[�g���ǂ���
	bool IsGate(int mapChipNo);

private:

	// �Q�[���V�[���̃|�C���^�ϐ�
	GameScene* gameScene_;

	// �}�b�v�摜
	int imgMapChips_[NUM_MAP_CHIPS];

	//// �g�p���Ă���}�b�v
	//int usedMap_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// �g�p���Ă���}�b�v�̎��
	TYPE type_;

	// �g�p���Ă���}�b�v�̃T�C�Y
	Vector2 usedMapSize_;

	// �h�A1�̏��
	bool isOpenDoor1_;

	// �h�A2�̏��
	bool isOpenDoor2_;

	// �h�A3�̏��
	bool isOpenDoor3_;

	// �h�A4�̏��
	bool isOpenDoor4_;

	// ���E�ǂ̃}�b�v
	int StageMap_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];
	
	// �h�A�̔w�i�̃}�b�v
	int DoorBackMap_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// �h�A�̃}�b�v
	int DoorMap_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// �h�A�̏Փ˃}�b�v
	int CollisionDoorMap_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// �I�u�W�F�N�g�̃}�b�v
	int ObjectMap_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// ���E�ǂ̏Փ˂̃}�b�v
	int CollisionStageMap_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// �E�o�Q�[�g�̃}�b�v
	int GateMap_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// �X�C�b�`1�̃}�b�v
	int Switch1Map_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// �X�C�b�`2�̃}�b�v
	int Switch2Map_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// �X�C�b�`3�̃}�b�v
	int Switch3Map_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// �X�C�b�`4�̃}�b�v
	int Switch4Map_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// �X�C�b�`5�̃}�b�v
	int Switch5Map_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// �X�C�b�`6�̃}�b�v
	int Switch6Map_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// �X�C�b�`7�̃}�b�v
	int Switch7Map_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// �X�C�b�`8�̃}�b�v
	int Switch8Map_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

};



