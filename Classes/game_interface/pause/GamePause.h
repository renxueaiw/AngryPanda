//
//  GamePause.h
//  AngryPanda
//
//  Created by renxueaiw on 13-12-24.
//
//

#ifndef __AngryPanda__GamePause__
#define __AngryPanda__GamePause__

#include "cocos2d.h"

class PauseLayerProtocol: public cocos2d::CCNode
{
public:
//    CREATE_FUNC(PauseLayerProtocol);
    
    void pauseLayerDidPause(void){};
    void pauseLayerDidUnPause(void){};
};

class GamePause: public cocos2d::CCLayerColor
{
    CC_PROPERTY(PauseLayerProtocol*, _delegate, Delegate);
private:
    cocos2d::CCSize _screenSize;
    cocos2d::CCSprite *_bg;
public:
    virtual ~GamePause(void);
    
    static GamePause* createWithColor(cocos2d::ccColor4B color, PauseLayerProtocol *delegate);
    bool initWithColor(cocos2d::ccColor4B color, PauseLayerProtocol *delegate);
    
    void pauseDelegate(void);
    void addBg(void);
    void createPausedMenu(void);
    
    void resumeCurrentLevel(cocos2d::CCObject *pSender);
    void goLevelSelection(cocos2d::CCObject *pSender);
    void replayCurrentLevel(cocos2d::CCObject *pSender);
    
    void doResume(cocos2d::CCNode *pSender);
};

#endif /* defined(__AngryPanda__GamePause__) */
