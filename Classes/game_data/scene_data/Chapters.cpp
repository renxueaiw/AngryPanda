//
//  Chapters.cpp
//  AngryPanda
//
//  Created by renxueaiw on 13-12-6.
//
//

#include "Chapters.h"

USING_NS_CC;

Chapters::~Chapters()
{
    CC_SAFE_RELEASE(_chapters);
}

bool Chapters::init()
{
    bool bRet = false;
    do {
        _chapters = CCArray::create();
        _chapters->retain();
        bRet = true;
    } while (0);
    return bRet;
}

// getter && setter
CCArray* Chapters::getChapters()
{
    return _chapters;
}
void Chapters::setChapters(CCArray* chapters)
{
    if (_chapters != chapters) {
        CC_SAFE_RETAIN(chapters);
        CC_SAFE_RELEASE(_chapters);
        _chapters = chapters;
    }
}
