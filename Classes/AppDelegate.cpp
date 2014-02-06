//
//  AngryPandaAppDelegate.cpp
//  AngryPanda
//
//  Created by renxueaiw on 13-11-27.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
//#include "IntroLayer.h"
#include "game_interface/resource_load/LoadingScreen.h"
#include "Utilities/LZDBUtils.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{
    
    LZDBUtils::sharedDBUtils()->createSqlite3Database("angry_panda_v_1_0.db");
    bool create_table_ok;
    // 章节数据
    create_table_ok = LZDBUtils::sharedDBUtils()->createTable("CREATE TABLE chapter (id integer primary key autoincrement, name text, number integer, unlocked integer, image text, intro text);");
    if (create_table_ok) {
        LZDBUtils::sharedDBUtils()->insertData("insert into chapter values (NULL, '迷雾岛', 1, 1, 'arts/scene_choice/mini1_bg.png', '迷雾重重，熊猫人喜欢在这里探索神秘的世界。');");
        LZDBUtils::sharedDBUtils()->insertData("insert into chapter values (NULL, '竹子林 ', 2, 0, 'arts/scene_choice/mini2_bg.png', '在海滩上生长着一片郁郁葱葱的竹林，是熊猫人嬉戏玩耍的乐土。');");
        LZDBUtils::sharedDBUtils()->insertData("insert into chapter values (NULL, '五风谷', 3, 0, 'arts/scene_choice/mini3_bg.png', '透过那挂满葡萄的枝条间隐约可以看见星星点点的繁华农场和集市。');");
        LZDBUtils::sharedDBUtils()->insertData("insert into chapter values (NULL, '昆仑山', 4, 0, 'arts/scene_choice/mini4_bg.png', '昆仑山脉北部陡峭的山峰之巅，传说中神仙聚集之地。');");
        LZDBUtils::sharedDBUtils()->insertData("insert into chapter values (NULL, '欢乐谷', 5, 0, 'arts/scene_choice/mini5_bg.png', '这里升腾着迷离的浓雾，周围群山环绕。');");
    }
    
    // 关卡数据
    create_table_ok = LZDBUtils::sharedDBUtils()->createTable("CREATE TABLE level (id integer primary key autoincrement, chapter_number integer, name text, number integer, unlocked integer, stars integer, data text, level_clear integer);");
    if (create_table_ok) {
        // 第一章
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 1, 'Chapter1Level1', 1, 1, 0, 'Some chapter 1 level 1 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 1, 'Chapter1Level2', 2, 0, 0, 'Some chapter 1 level 2 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 1, 'Chapter1Level3', 3, 0, 0, 'Some chapter 1 level 3 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 1, 'Chapter1Level4', 4, 0, 0, 'Some chapter 1 level 4 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 1, 'Chapter1Level5', 5, 0, 0, 'Some chapter 1 level 5 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 1, 'Chapter1Level6', 6, 0, 0, 'Some chapter 1 level 6 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 1, 'Chapter1Level7', 7, 0, 0, 'Some chapter 1 level 7 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 1, 'Chapter1Level8', 8, 0, 0, 'Some chapter 1 level 8 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 1, 'Chapter1Level9', 9, 0, 0, 'Some chapter 1 level 9 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 1, 'Chapter1Level10', 10, 0, 0, 'Some chapter 1 level 10 data.', 0);");
        
        // 第二章
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 2, 'Chapter2Level1', 1, 0, 0, 'Some chapter 2 level 1 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 2, 'Chapter2Level2', 2, 0, 0, 'Some chapter 2 level 2 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 2, 'Chapter2Level3', 3, 0, 0, 'Some chapter 2 level 3 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 2, 'Chapter2Level4', 4, 0, 0, 'Some chapter 2 level 4 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 2, 'Chapter2Level5', 5, 0, 0, 'Some chapter 2 level 5 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 2, 'Chapter2Level6', 6, 0, 0, 'Some chapter 2 level 6 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 2, 'Chapter2Level7', 7, 0, 0, 'Some chapter 2 level 7 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 2, 'Chapter2Level8', 8, 0, 0, 'Some chapter 2 level 8 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 2, 'Chapter2Level9', 9, 0, 0, 'Some chapter 2 level 9 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 2, 'Chapter2Level10', 10, 0, 0, 'Some chapter 2 level 10 data.', 0);");
        
        // 第三章
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 3, 'Chapter3Level1', 1, 0, 0, 'Some chapter 3 level 1 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 3, 'Chapter3Level2', 2, 0, 0, 'Some chapter 3 level 2 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 3, 'Chapter3Level3', 3, 0, 0, 'Some chapter 3 level 3 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 3, 'Chapter3Level4', 4, 0, 0, 'Some chapter 3 level 4 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 3, 'Chapter3Level5', 5, 0, 0, 'Some chapter 3 level 5 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 3, 'Chapter3Level6', 6, 0, 0, 'Some chapter 3 level 6 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 3, 'Chapter3Level7', 7, 0, 0, 'Some chapter 3 level 7 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 3, 'Chapter3Level8', 8, 0, 0, 'Some chapter 3 level 8 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 3, 'Chapter3Level9', 9, 0, 0, 'Some chapter 3 level 9 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 3, 'Chapter3Level10', 10, 0, 0, 'Some chapter 3 level 10 data.', 0);");
        
        // 第四章
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 4, 'Chapter4Level1', 1, 0, 0, 'Some chapter 4 level 1 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 4, 'Chapter4Level2', 2, 0, 0, 'Some chapter 4 level 2 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 4, 'Chapter4Level3', 3, 0, 0, 'Some chapter 4 level 3 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 4, 'Chapter4Level4', 4, 0, 0, 'Some chapter 4 level 4 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 4, 'Chapter4Level5', 5, 0, 0, 'Some chapter 4 level 5 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 4, 'Chapter4Level6', 6, 0, 0, 'Some chapter 4 level 6 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 4, 'Chapter4Level7', 7, 0, 0, 'Some chapter 4 level 7 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 4, 'Chapter4Level8', 8, 0, 0, 'Some chapter 4 level 8 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 4, 'Chapter4Level9', 9, 0, 0, 'Some chapter 4 level 9 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 4, 'Chapter4Level10', 10, 0, 0, 'Some chapter 4 level 10 data.', 0);");
        
        // 第五章
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 5, 'Chapter5Level1', 1, 0, 0, 'Some chapter 5 level 1 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 5, 'Chapter5Level2', 2, 0, 0, 'Some chapter 5 level 2 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 5, 'Chapter5Level3', 3, 0, 0, 'Some chapter 5 level 3 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 5, 'Chapter5Level4', 4, 0, 0, 'Some chapter 5 level 4 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 5, 'Chapter5Level5', 5, 0, 0, 'Some chapter 5 level 5 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 5, 'Chapter5Level6', 6, 0, 0, 'Some chapter 5 level 6 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 5, 'Chapter5Level7', 7, 0, 0, 'Some chapter 5 level 7 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 5, 'Chapter5Level8', 8, 0, 0, 'Some chapter 5 level 8 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 5, 'Chapter5Level9', 9, 0, 0, 'Some chapter 5 level 9 data.', 0);");
        LZDBUtils::sharedDBUtils()->insertData("insert into level values(NULL, 5, 'Chapter5Level10', 10, 0, 0, 'Some chapter 5 level 10 data.', 0);");
    }
}

AppDelegate::~AppDelegate()
{
    LZDBUtils::sharedDBUtils()->closeDatabase();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    
    CCSize designSize = CCSizeMake(480, 320);
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionShowAll);

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
//    CCScene *pScene = IntroLayer::scene();
    CCScene *pScene = LoadingScreen::scene();

    // run
    pDirector->runWithScene(CCTransitionFade::create(1.0f, pScene));

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
