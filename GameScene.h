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

	// �J�����𓮂����͈�
	static constexpr int CAMERA_WIDTH = 400;
	static constexpr int CAMERA_HEIGHT = 300;

	// �G���J�E���g�l(�l���傫���Əo���Ԋu�������Ȃ�)
	// 30�t���[����1�́A�G�����܂��B
	static constexpr int ENCOUNT = 60;

	// �R���X�g���N�^
	GameScene(void);

	// �f�X�g���N�^
	~GameScene(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void DrawUI(void);
	void Release(void);

	// �J�������W�̎擾(�Q�b�^�[)
	Vector2 GetCameraPos(void);

	// ���[���h(�X�N���[��)���W���}�b�v���W�ɕϊ�����
	Vector2 World2MapPos(Vector2 worldPos);

	// �}�b�v�`�b�v���g�p�����Փ˔���
	bool IsCollisionStage(Vector2 worldPos);

	// �h�A�̏Փ˔���
	bool IsCollisionDoor(Vector2 worldPos);

	// �h�A�̏Փ˔���
	bool IsCollisionGate(Vector2 worldPos);

	// �v���C���[���W�̎擾
	Vector2 GetPlayerPos(void);

	// ��1�̃Q�b�^�[
	bool GetKey1(void);

	// ��2�̃Q�b�^�[
	bool GetKey2(void);

	// ��3�̃Q�b�^�[
	bool GetKey3(void);

	// ��4�̃Q�b�^�[
	bool GetKey4(void);

	// ���̃Q�b�^�[
	int GetMinute(void);

	// �b�̃Q�b�^�[
	int GetSecond(void);

	bool IsCollisionRectCenter
	(Vector2 centerPos1, Vector2 size1,
		Vector2 centerPos2, Vector2 size2);

	/// <summary>
	/// ��`���m�̏Փ˔���
	/// </summary>
	/// <param name="stPos1">��`�P�̒��S���W</param>
	/// <param name="edPos1">��`�P�̃T�C�Y</param>
	/// <param name="stPos2">��`�Q�̒��S���W</param>
	/// <param name="edPos2">��`�Q�̃T�C�Y</param>

	// �X�e�[�W�̎擾
	Stage* GetStage(void);

	// �v���C���[�̎擾
	Player* GetPlayer(void);

private:

	// �^�C�g���摜
	int imgGame_;

	// �X�^�[�g�摜
	int imgStart_;

	// �̗̓Q�[�W�̉摜
	int hpImage_;

	// �A�N�^�[�摜
	int Actorimg_;

	// ��1�̉摜
	int keyImage1_;

	// ��2�̉摜
	int keyImage2_;

	// ��3�̉摜
	int keyImage3_;

	// ��4�̉摜
	int keyImage4_;

	// UI�̖�̉摜�̔w�i
	int ArrowBack_;

	// UI�̖�̉摜
	int UIimgs_;

	// UI�̖�̉摜
	int UIimgs2_;

	// UI�̖�̉摜
	int UIimgs3_;

	// UI�̖�̉摜
	int UIimgs4_;

	// UI�̖�̉摜
	int UIimgs5_;

	// ���x��1�̉摜
	int Level1_;

	// ���x��2�̉摜
	int Level2_;

	// ���x��3�̉摜
	int Level3_;

	// ���x��4�̉摜
	int Level4_;

	// ���x��5�̉摜
	int Level5_;

	// ���x���摜�̔w�i
	int LevelBack_;

	// �Q�[���N���A�V�[���̉摜
	int imgGameClear_;

	// �X�e�[�W�̃|�C���^
	Stage* stage_;

	// �v���C���[�̃|�C���^
	Player* player_;

	// �G�l�~�[�{�X�̃|�C���^
	EnemyBoss* enemyBoss_;

	// �G�l�~�[�̃|�C���^
	EnemyShot* enemyShot_;

	// �V���b�g�̃|�C���^
	Shot* shot_;

	// �����̓G�𓮓I�ɊǗ�
	std::vector<EnemyBase*> enemys_;

	// �������W�̏��������Ƀ\�[�g
	std::list<EnemyBase*> sortEnemys_;

	// �X�^�[�g���b�Z�[�W
	StartMes* startMes_;

	// �G�̔����p�x
	int enCounter;

	// �J�������W
	Vector2 cameraPos_;

	// �e�����L�[�̏��
	bool isShotKeyNew_;

	// �e�����L�[�̏��(1�t���[���O�̏��)
	bool isShotKeyOld_;

	// �e���ˌ�̍d�����Ԍv�Z�p
	float stepShotDelay_;

	// �󔠍��W
	Vector2 boxPos_;

	// �A�N�^�[�摜�̏��
	bool isActor1_;

	// �A�N�^�[�摜�̏��
	bool isActor2_;

	// �A�N�^�[�摜�̏��
	bool isActor3_;

	// �A�N�^�[�摜�̏��
	bool isActor4_;

	// �A�N�^�[�摜�̕⏕
	bool isActor1a_;

	// �A�N�^�[�摜�̕⏕
	bool isActor2a_;

	// �A�N�^�[�摜�̕⏕
	bool isActor3a_;

	// �A�N�^�[�摜�̕⏕
	bool isActor4a_;

	// ��1�̏��
	bool isKey1_;

	// ��2�̏��
	bool isKey2_;

	// ��3�̏��
	bool isKey3_;

	// ��4�̏��
	bool isKey4_;

	// �h�A1�̏��
	bool openDoor1_;
	
	// �h�A2�̏��
	bool openDoor2_;

	// �h�A3�̏��
	bool openDoor3_;

	// �h�A4�̏��
	bool openDoor4_;

	// �q�b�g�X�g�b�v
	int hitStopCnt_;

	// �X�N���[��
	int tmpScreen_;

	// �X���[�J�E���g
	int slowCnt_;

	// ���Ԃ̃J�E���g
	int timecnt_;

	// �b��
	int second_;

	// ����
	int minute_;

	// �Q�[���N���A�V�[��
	int gameClear_;

	// ���ŗp�̃J�E���^
	int blinkCnt_;

	// �t�F�[�h�p�̃J�E���^
	int fadeCnt_;

	// �Q�[���V�[����BGM
	int bgmGameScene_;

	// ����{�^����SE
	int SEBotton_;

	// �A�N�^�[��SE
	int SEActor_;

	// �U���{�^����SE
	int SEAttack_;

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

	// �{�X�̑Ō�����SE
	int SEBossHit_;

	// �h�A��SE
	int SEDoor_;

	// �J�����ړ�
	void CameraMove(void);

	// �J�����ړ�(�f�o�b�O�p)
	void CameraMoveDebug(void);

	// �Փ˔���
	void Collision(void);

	bool IsCollisionRect
	(Vector2 stPos1, Vector2 edPos1,
		Vector2 stPos2, Vector2 edPos2);

	/// <summary>
	/// ��`���m�̏Փ˔���
	/// </summary>
	/// <param name="stPos1">��`�P�̍�����W</param>
	/// <param name="edPos1">��`�P�̉E�����W</param>
	/// <param name="stPos2">��`�Q�̉E����W</param>
	/// <param name="edPos2">��`�Q�̉E�����W</param>

	//bool IsCollisionRectCenter
	//(Vector2 centerPos1, Vector2 size1,
	//Vector2 centerPos2, Vector2 size2);

	/// <summary>
	/// ��`���m�̏Փ˔���
	/// </summary>
	/// <param name="stPos1">��`�P�̒��S���W</param>
	/// <param name="edPos1">��`�P�̃T�C�Y</param>
	/// <param name="stPos2">��`�Q�̒��S���W</param>
	/// <param name="edPos2">��`�Q�̃T�C�Y</param>

	// �G�̃N���A
	void ClearEnemys(void);

	// �`�揇�p:�������W(Y)�̏��������Ƀ\�[�g���Ă���
	void SortEnemys(void);

	// �󔠂̔���
	void TreasureChest(void);

	// �A�N�^�[�摜�̊Ǘ�
	void Actor(void);

	// �Q�[���N���A�p
	void GameClear(void);

	// BGM
	void BGM(void);

};



