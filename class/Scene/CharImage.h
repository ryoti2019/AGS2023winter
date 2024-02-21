#pragma once


// �L�����̎��
enum class CharID
{
	MAN,
	GIRL,
	CAT,
	DRAW,
	MAX
};
enum class Dir
{
	Down,
	Left,
	Right,
	Up,
	Max
};

#define ANIME_IMAGE_MAX 3		// �A�j���[�V��������

class CharImage
{
public:
	CharImage();
	~CharImage();
	bool Init(CharID charID);
	bool Release(void);
	int chipImage_[static_cast<int>(Dir::Max)][ANIME_IMAGE_MAX];
private:
	CharID charID_;
};

