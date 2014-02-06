//
//  Chapter.h
//  AngryPanda
//
//  Created by renxueaiw on 13-12-6.
//
//

#ifndef __AngryPanda__Chapter__
#define __AngryPanda__Chapter__

#include "cocos2d.h"

class Chapter: public cocos2d::CCObject
{
    CC_PROPERTY(cocos2d::CCString*, _name, Name);
    CC_PROPERTY(int, _number, Number);
    CC_PROPERTY(bool, _unlocked, Unlocked);
    CC_PROPERTY(cocos2d::CCString*, _image, Image);
    CC_PROPERTY(cocos2d::CCString*, _intro, Intro);
public:
    CREATE_FUNC(Chapter);
    virtual ~Chapter(void);
    virtual bool init(void);
    bool initWithName(cocos2d::CCString* name, int number, bool unlocked, cocos2d::CCString* image, cocos2d::CCString* intro);
};

#endif /* defined(__AngryPanda__Chapter__) */
