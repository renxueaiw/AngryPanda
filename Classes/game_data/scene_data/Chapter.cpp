//
//  Chapter.cpp
//  AngryPanda
//
//  Created by renxueaiw on 13-12-6.
//
//

#include "Chapter.h"

USING_NS_CC;

Chapter::~Chapter()
{
    CC_SAFE_RELEASE(_name);
}

bool Chapter::init()
{
    bool bRet = false;
    do {
        _name = CCString::create("");
        _name->retain();
        bRet = true;
    } while (0);
    return bRet;
}

bool Chapter::initWithName(CCString* name, int number, bool unlocked, CCString* image, CCString* intro)
{
    bool bRet = false;
    do {
        setName(name);
        setNumber(number);
        setUnlocked(unlocked);
        setImage(image);
        setIntro(intro);
        bRet = true;
    } while (0);
    return bRet;
}

// 访问与设置器
CCString* Chapter::getName()
{
    return _name;
}
void Chapter::setName(CCString* name)
{
    if (_name != name) {
        CC_SAFE_RETAIN(name);
        CC_SAFE_RELEASE(_name);
        _name = name;
    }
}

int Chapter::getNumber()
{
    return _number;
}
void Chapter::setNumber(int number)
{
    _number = number;
}

bool Chapter::getUnlocked()
{
    return _unlocked;
}
void Chapter::setUnlocked(bool unlocked)
{
    _unlocked = unlocked;
}

CCString* Chapter::getImage()
{
    return _image;
}
void Chapter::setImage(CCString* image)
{
    if (_image != image) {
        CC_SAFE_RETAIN(image);
        CC_SAFE_RELEASE(_image);
        _image = image;
    }
}

CCString* Chapter::getIntro()
{
    return _intro;
}
void Chapter::setIntro(CCString* intro)
{
    if (_intro != intro) {
        CC_SAFE_RETAIN(intro);
        CC_SAFE_RELEASE(_intro);
        _intro = intro;
    }
}