//
//  Level.cpp
//  AngryPanda
//
//  Created by renxueaiw on 13-12-9.
//
//

#include "Level.h"

USING_NS_CC;

Level::~Level()
{
    CC_SAFE_RELEASE(_name);
    CC_SAFE_RELEASE(_data);
}

bool Level::init()
{
    bool bRet = false;
    do {
        _name = CCString::create("");
        _name->retain();
        _data = CCString::create("");
        _data->retain();
        
        bRet = true;
    } while (0);
    
    return bRet;
}

bool Level::initWithName(int chapterNumber, CCString* name, int number, int unlocked, int stars, CCString* data, bool levelClear)
{
    bool bRet = false;
    do {
        setChapterNumber(chapterNumber);
        setName(name);
        setNumber(number);
        setUnlocked(unlocked);
        setStars(stars);
        setData(data);
        setLevelClear(levelClear);
        
        bRet = true;
    } while (0);
    return bRet;
}

#pragma mark 访问器和设置器
CCString* Level::getName()
{
    return _name;
}
void Level::setName(CCString* name)
{
    if (_name != name) {
        CC_SAFE_RETAIN(name);
        CC_SAFE_RELEASE(_name);
        _name = name;
    }
}

int Level::getChapterNumber()
{
    return _chapterNumber;
}
void Level::setChapterNumber(int chapterNumber)
{
    _chapterNumber = chapterNumber;
}

int Level::getNumber()
{
    return _number;
}
void Level::setNumber(int number)
{
    _number = number;
}

bool Level::getUnlocked()
{
    return _unlocked;
}
void Level::setUnlocked(bool unlocked)
{
    _unlocked = unlocked;
}

int Level::getStars()
{
    return _stars;
}
void Level::setStars(int stars)
{
    _stars = stars;
}

CCString* Level::getData()
{
    return _data;
}
void Level::setData(CCString* data)
{
    if (_data != data) {
        CC_SAFE_RETAIN(data);
        CC_SAFE_RELEASE(_data);
        _data = data;
    }
}

bool Level::getLevelClear()
{
    return _levelClear;
}
void Level::setLevelClear(bool levelClear)
{
    _levelClear = levelClear;
}