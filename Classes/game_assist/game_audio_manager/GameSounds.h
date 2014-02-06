//
//  GameSounds.h
//  AngryPanda
//
//  Created by renxueaiw on 13-11-30.
//
//

#ifndef __AngryPanda__GameSounds__
#define __AngryPanda__GameSounds__

#include "cocos2d.h"

class GameSounds : public cocos2d::CCNode
{
public:
    static GameSounds* sharedGameSounds(void);
    virtual bool init(void);
    // 启用或禁用音效
    void disableSoundEffect(void);
    void enableSoundEffect(void);
    
    // 播放或关闭背景音乐
    void playBackgroundMusic(void);
    void stopBackGroundMusic(void);
    
    // 以下方法用于播放不同界面中不同音效
//    void playSoundEffect(cocos2d::CCString* fileName);
//    void playSoundEffectWithDelay(cocos2d::CCString fileName, float delay);
//    
//    void playStretchSlignshotSound(void);
//    void playReleaseSlingshotSound(void);
//    void playImpactSound(void);
//    void playBreakSound(void);
//    void playIntroSound(void);
//    
//    void restartBackgroundMusic(void);
//    void playAboutSceneMusic(void);
//
//    void preloadSounds(void);
//
//    void levelClear(void);  // 通关
//    void levelLose(void);   // 闯关失败

};

#endif /* defined(__AngryPanda__GameSounds__) */
