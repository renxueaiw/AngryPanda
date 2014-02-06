//
//  IntroLayer.h
//  AngryPanda
//
//  Created by renxueaiw on 13-12-1.
//
//

#ifndef __AngryPanda__IntroLayer__
#define __AngryPanda__IntroLayer__

#include "cocos2d.h"

class IntroLayer: public cocos2d::CCLayer
{
public:
    static cocos2d::CCScene* scene();
    CREATE_FUNC(IntroLayer);
    virtual bool init(void);
    virtual void onEnter();
};

#endif /* defined(__AngryPanda__IntroLayer__) */
