//
//  StartGameScene.h
//  AngryPanda
//
//  Created by renxueaiw on 13-12-1.
//
//

#ifndef __AngryPanda__StartGameScene__
#define __AngryPanda__StartGameScene__

#include "cocos2d.h"

//#define IS_IPHONE (!IS_IPAD)
//#define IS_IPAD (UI_USER_INTERFACE_IDIOM() != UIUserInterfaceIdiomPhone)

class StartGameScene: public cocos2d::CCLayer
{
private:
    // 添加背景图片
    cocos2d::CCSprite *_bgGameStart;
    cocos2d::CCSprite *_gameTitle;
    cocos2d::CCMenuItem *_playItem;
    cocos2d::CCSize _screenSize;
    cocos2d::CCMenuItem *_aboutItem;
    
    // 音效设置
    cocos2d::CCMenu *_soundEffectMenu;
    cocos2d::CCMenu *_backgroundMusicMenu;
    
    cocos2d::CCPoint _soundEffectMenuLocation;
    cocos2d::CCPoint _backgroundMusicMenuLocation;
    cocos2d::CCPoint _aboutMenuLocation;
    
    // 设备类型
//    int deviceType;
  
public:
    static cocos2d::CCScene* scene(void);
    virtual ~StartGameScene(void);
    CREATE_FUNC(StartGameScene);
    virtual bool init(void);
    
    // 逻辑部分
    
    void addGameTitle(void);
    void addBackground(void);
    void addPlayItem(void);
    void startGame(cocos2d::CCObject *pSender);
    
    // 添加背景音乐
    void playBacgroundMusic(void);
    // 音效开关选项
    void createSoundEffectMenuOn(void);
    void createSoundEffectMenuOff(void);
    void createBackgroundMusicMenuOn(void);
    void createBackgroundMusicMenuOff(void);
    void createSoundSettingMenu(void);
    
    void turnSoundEffectOff(cocos2d::CCObject *pSender);
    void turnSoundEffectOn(cocos2d::CCObject *pSender);
    void turnBackgroundMusicOff(cocos2d::CCObject *pSender);
    void turnBackgroundMusicOn(cocos2d::CCObject *pSender);
    //设置菜单按钮的位置
    void setMenuLocation(void);
    //添加about按钮
    void addAboutItem(void);
    void about(cocos2d::CCObject *pSender);
};

#endif /* defined(__AngryPanda__StartGameScene__) */
