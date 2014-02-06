//
//  Chapters.h
//  AngryPanda
//
//  Created by renxueaiw on 13-12-6.
//
//

#ifndef __AngryPanda__Chapters__
#define __AngryPanda__Chapters__

#include "cocos2d.h"

class Chapters: public cocos2d::CCObject
{
    CC_PROPERTY(cocos2d::CCArray*, _chapters, Chapters);
public:
    CREATE_FUNC(Chapters);
    ~Chapters(void);
    virtual bool init(void);
};

#endif /* defined(__AngryPanda__Chapters__) */
