//
//  Levels.cpp
//  AngryPanda
//
//  Created by renxueaiw on 13-12-9.
//
//

#include "Levels.h"

USING_NS_CC;

Levels::~Levels()
{
    CC_SAFE_RELEASE(_levels);
}

bool Levels::init()
{
    bool bRet = false;
    do {
        _levels = CCArray::create();
        _levels->retain();
        
        bRet = true;
    } while (0);
    return bRet;
}

#pragma mark getter && setter
CCArray* Levels::getLevels()
{
    return _levels;
}
void Levels::setLevels(CCArray* levels)
{
    if (_levels != levels) {
        CC_SAFE_RETAIN(levels);
        CC_SAFE_RELEASE(_levels);
        _levels = levels;
    }
}
