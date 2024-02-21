#include <sstream>
#include "AsoUtility.h"

std::vector<std::string> AsoUtility::Split(std::string line, char delimiter)
{

    // �ϒ��z��̕Ԃ�l������
    std::vector <std::string> result;

    // string���t�@�C���X�g���[���ɕϊ�
    std::istringstream stream(line);

    // �ǂݍ��񂾕�������i�[����p�ϐ�
    std::string field;

    // stream�����Ԃɓǂݍ���
    // ��R�����Ŏw�肳�ꂽ�����܂ł��Q�����ɕԂ�
    while (getline(stream, field, delimiter))
    {
        // �ϔz��ɒǉ�
        result.push_back(field);
    }

    // ��: line "aaa,bbb,ccc"
    //     ��result

    return result;
}

int AsoUtility::Round(float value)
{
    return static_cast<int>(round(value));;
}

Vector2 AsoUtility::Round(Vector2F value)
{
    Vector2 ret;
    ret.x = Round(value.x);
    ret.y = Round(value.y);
    return ret;
}

Vector2 AsoUtility::Round(float x, float y)
{
    Vector2 ret;
    ret.x = Round(x);
    ret.y = Round(y);
    return ret;
}

