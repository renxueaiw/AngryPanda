//
//  LevelSelection.h
//  AngryPanda
//
//  Created by renxueaiw on 13-12-3.
//
//

#ifndef __AngryPanda__LevelSelection__
#define __AngryPanda__LevelSelection__

#include "cocos2d.h"
#include "../../game_data/scene_data/Chapter.h"

class LevelSelection: public cocos2d::CCLayer
{
private:
    Chapter* _currentChapter;
    
    
    // 按钮的位置
    cocos2d::CCPoint _backButtonLocation;
    cocos2d::CCPoint _storeButtonLocation;
    
    // 场景文字描述的位置
    cocos2d::CCPoint _textLocation;
    
    // 章节的位置
    cocos2d::CCPoint _levelMenuLocation;
    
    // 背景图片的位置
    cocos2d::CCPoint _bgLocation;
    
    // 章节标题的位置
    cocos2d::CCPoint _chapterTitleLocation;
    
    // 章节简介的位置
    cocos2d::CCPoint _chapterIntroLocation;
    
    // 屏幕大小
    cocos2d::CCSize _screenSize;
    
    // 章节标题
    cocos2d::CCLabelTTF *_chapterTitle;
    
    // 章节简介
    cocos2d::CCLabelTTF *_chapterIntro;
    
public:
    static cocos2d::CCScene* scene();
    CREATE_FUNC(LevelSelection);
    virtual ~LevelSelection(void);
    virtual bool init(void);
    
    // logic handle
    // 获取屏幕大小
    void getScreenSize(void);
    // 设置各视觉元素的位置
    void setMenuLocation(void);
    // 添加章节介绍
    void addChapterIntro(void);
    // 从GameData中获取数据
    void readData(void);
    // 添加返回按钮
    void addBackButton(void);
    // 返回起始画面(章节选择);
    void backToStart(void);
    // 添加背景音乐
    void playBackgroundMusic(void);
    // 添加菜单背景
    void addLevelSelectBg(void);
    // 添加关卡选择菜单
    void addLevelMenu(void);
    // 选中关卡跳转到游戏主场景
    void onPlay(cocos2d::CCMenuItemImage *pSender);
    
};

#endif /* defined(__AngryPanda__LevelSelection__) */
