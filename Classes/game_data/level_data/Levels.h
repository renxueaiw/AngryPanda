//
//  Levels.h
//  AngryPanda
//
//  Created by renxueaiw on 13-12-9.
//
//

#ifndef __AngryPanda__Levels__
#define __AngryPanda__Levels__

#include "cocos2d.h"

class Levels: public cocos2d::CCObject
{
    CC_PROPERTY(cocos2d::CCArray*, _levels, Levels);
public:
    CREATE_FUNC(Levels);
    ~Levels(void);
    virtual bool init(void);
};

#endif /* defined(__AngryPanda__Levels__) */
