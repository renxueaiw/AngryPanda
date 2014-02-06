//
//  CustomAnimation.cpp
//  AngryPanda
//
//  Created by renxueaiw on 13-12-30.
//
//

#include "CustomAnimation.h"

USING_NS_CC;


CustomAnimation* CustomAnimation::createWithFile(std::string theFilenameToAnimate, int theFrameToStartWith, int theNumberOfFramesToAnimate, int theX, int theY, bool flipX, bool flipY, bool doesInLoop, bool doesItUseRandomFrameToLoop)
{
    CustomAnimation *ca = new CustomAnimation();
    ca->initWithFile(theFilenameToAnimate, theFrameToStartWith, theNumberOfFramesToAnimate, theX, theY, flipX, flipY, doesInLoop, doesItUseRandomFrameToLoop);
    ca->autorelease();
    
    return ca;
}

CustomAnimation::~CustomAnimation()
{
    CC_SAFE_RELEASE(_fileNameToAnimate);
    CC_SAFE_RELEASE(_someSprite);
}

// 初始化动画，并设置多种属性
void CustomAnimation::initWithFile(std::string theFilenameToAnimate, int theFrameToStartWith, int theNumberOfFramesToAnimate, int theX, int theY, bool flipX, bool flipY, bool doesInLoop, bool doesItUseRandomFrameToLoop)
{
    _fileNameToAnimate = CCString::create(theFilenameToAnimate.c_str());
    _fileNameToAnimate->retain();
    
    _framesToStartWith = theFrameToStartWith;
    _currentFrame = _framesToStartWith;
    
    _framesToAnimate = theNumberOfFramesToAnimate;
    
    _animationFlippedX = flipX;
    _animationFlippedY = flipY;
    
    _doesTheAnimationLoop = doesInLoop;
    _useRandomFrameToLoop = doesItUseRandomFrameToLoop;
    
    _someSprite = CCSprite::create(CCString::createWithFormat("arts/game_main_scenes/%s_000%d.png", _fileNameToAnimate->getCString(), _currentFrame)->getCString());
    _someSprite->retain();
    _someSprite->setPosition(ccp(theX, theY));
    
    _someSprite->setFlipX(_animationFlippedX);
    _someSprite->setFlipY(_animationFlippedY);
    
    schedule(schedule_selector(CustomAnimation::runMyAnimation), 1.0f/60.0f);
}

// 运行动画
void CustomAnimation::runMyAnimation(float delta)
{
    _currentFrame++;
    
    if (_currentFrame <= _framesToAnimate) {
        if (_currentFrame < 10) {
            _someSprite->setTexture(CCSprite::create(CCString::createWithFormat("arts/game_main_scenes/%s_000%d.png", _fileNameToAnimate->getCString(), _currentFrame)->getCString())->getTexture());
        } else if (_currentFrame < 100) {
            _someSprite->setTexture(CCSprite::create(CCString::createWithFormat("arts/game_main_scenes/%s_00%d.png", _fileNameToAnimate->getCString(), _currentFrame)->getCString())->getTexture());
        } else {
            _someSprite->setTexture(CCSprite::create(CCString::createWithFormat("arts/game_main_scenes/%s_0%d.png", _fileNameToAnimate->getCString(), _currentFrame)->getCString())->getTexture());
        }
    } else {
        if (_doesTheAnimationLoop == true && _useRandomFrameToLoop == false) {
            _currentFrame = _framesToStartWith;
        } else if (_doesTheAnimationLoop == true && _useRandomFrameToLoop == true) {
            _currentFrame = arc4random() % _framesToAnimate;
        } else {
            removeChild(_someSprite, true);
            unschedule(schedule_selector(CustomAnimation::runMyAnimation));
        }
    }
}

// 更改透明度
void CustomAnimation::changeOpacityTo(int theNewOpacity)
{
    _someSprite->setOpacity(theNewOpacity);
}

// 着色
void CustomAnimation::tintMe(cocos2d::ccColor3B theColor)
{
    _someSprite->setColor(theColor);
}


