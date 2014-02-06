//
//  Level.h
//  AngryPanda
//
//  Created by renxueaiw on 13-12-9.
//
//

#ifndef __AngryPanda__Level__
#define __AngryPanda__Level__

#include "cocos2d.h"

class Level:public cocos2d::CCObject
{
    // 章节编号
    CC_PROPERTY(int, _chapterNumber, ChapterNumber);
    
    // 关卡名称
    CC_PROPERTY(cocos2d::CCString*, _name, Name);
    
    // 关卡编号
    CC_PROPERTY(int, _number, Number);
    
    // 关卡是否已解锁
    CC_PROPERTY(bool, _unlocked, Unlocked);
    
    // 关卡星级评价
    CC_PROPERTY(int, _stars, Stars);
    
    // 其它数据
    CC_PROPERTY(cocos2d::CCString*, _data, Data);
    
    // 关卡是否已通过
    CC_PROPERTY(bool, _levelClear, LevelClear);
public:
    CREATE_FUNC(Level);
    ~Level(void);
    virtual bool init(void);
    bool initWithName(int chapterNumber, cocos2d::CCString* name, int number, int unlocked, int stars, cocos2d::CCString* data, bool levelClear);
    
};

#endif /* defined(__AngryPanda__Level__) */
