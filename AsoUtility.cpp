#include <sstream>
#include "AsoUtility.h"

std::vector<std::string> AsoUtility::Split(std::string line, char delimiter)
{

    // 可変長配列の返り値を準備
    std::vector <std::string> result;

    // stringをファイルストリームに変換
    std::istringstream stream(line);

    // 読み込んだ文字列を格納する用変数
    std::string field;

    // streamを順番に読み込み
    // 第３引数で指定された文字までを第２引数に返す
    while (getline(stream, field, delimiter))
    {
        // 可変配列に追加
        result.push_back(field);
    }

    // 例: line "aaa,bbb,ccc"
    //     ⇒result

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

