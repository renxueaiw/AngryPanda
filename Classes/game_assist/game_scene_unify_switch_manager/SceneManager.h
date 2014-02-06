//
//  SceneManager.h
//  AngryPanda
//
//  Created by renxueaiw on 13-12-24.
//
//

#ifndef __AngryPanda__SceneManager__
#define __AngryPanda__SceneManager__

#include "cocos2d.h"

#include "../../game_interface/start/StartGameScene.h"
#include "../../game_interface/chapter_select/ChpaterSelect.h"
#include "../../game_interface/game_main/MainScene.h"
#include "../../game_interface/about/About.h"
#include "../../game_interface/level_result/LevelResult.h"
#include "../../game_interface/level_selection/LevelSelection.h"

class SceneManager:public cocos2d::CCObject
{
protected:
    static cocos2d::CCScene* wrap(cocos2d::CCLayer *layer);
    static void go(cocos2d::CCLayer *layer);
public:
    static void goStartGame(void);
    static void goAboutScene(void);
    static void goChapterSelect(void);
    static void goLevelSelect(void);
    static void goGameScene(void);
    static void goLevelResult(void);
};

#endif /* defined(__AngryPanda__SceneManager__) */
