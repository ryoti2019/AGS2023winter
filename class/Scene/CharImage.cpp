#include <string>
#include <DxLib.h>
#include "CharImage.h"

CharImage::CharImage()
{
}

CharImage::~CharImage()
{
}

bool CharImage::Init(CharID charID)
{
    if (charID >= CharID::DRAW || charID < CharID::MAN)
    {
        return false;
    }

    std

    if (LoadDivGraph() == -1)
    {
        return false;
    }

    charID_ = charID;

    return false;
}

bool CharImage::Release(void)
{
    return false;
}
