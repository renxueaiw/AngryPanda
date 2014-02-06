//
//  CustomAnimation.h
//  AngryPanda
//
//  Created by renxueaiw on 13-12-30.
//
//

#ifndef __AngryPanda__CustomAnimation__
#define __AngryPanda__CustomAnimation__

/*
  该类用于创建寶你给的动画效果
 */
#include "cocos2d.h"

class CustomAnimation: public cocos2d::CCNode
{
private:
    cocos2d::CCString *_fileNameToAnimate;
    int _currentFrame;
    int _framesToAnimate;
    int _framesToStartWith;
    
    cocos2d::CCSprite *_someSprite;

    bool _animationFlippedX;
    bool _animationFlippedY;
    bool _doesTheAnimationLoop;
    bool _useRandomFrameToLoop;
    
public:
    virtual ~CustomAnimation(void);
    static CustomAnimation* createWithFile(std::string theFilenameToAnimate, int theFrameToStartWith, int theNumberOfFramesToAnimate, int theX, int theY, bool flipX, bool flipY, bool doesInLoop, bool doesItUseRandomFrameToLoop);
    void initWithFile(std::string theFilenameToAnimate, int theFrameToStartWith, int theNumberOfFramesToAnimate, int theX, int theY, bool flipX, bool flipY, bool doesInLoop, bool doesItUseRandomFrameToLoop);
    
    
    // 运行动画
    void runMyAnimation(float delta);
    // 着色
    void tintMe(cocos2d::ccColor3B theColor);
    // 理性透明度 
    void changeOpacityTo(int theNewOpacity);
    
};


#endif /* defined(__AngryPanda__CustomAnimation__) */
