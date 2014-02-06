//
//  LevelResult.cpp
//  AngryPanda
//
//  Created by renxueaiw on 13-12-16.
//
//

#include "LevelResult.h"
#include "../../game_data/game_state/GameData.h"
#include "SimpleAudioEngine.h"
//#include "../level_selection/LevelSelection.h"
#include "../../game_data/level_data/LevelParser.h"
#include "../../game_data/level_data/Levels.h"
#include "../../game_data/level_data/Level.h"
//#include "../chapter_select/ChpaterSelect.h"
#include "../../game_assist/game_scene_unify_switch_manager/SceneManager.h"

USING_NS_CC;

CCScene* LevelResult::scene()
{
    CCScene *pScene = CCScene::create();
    LevelResult *layer = LevelResult::create();
    pScene->addChild(layer);
    return pScene;
}

LevelResult::~LevelResult()
{
    CC_SAFE_RELEASE(_levelName);
    CC_SAFE_RELEASE(_resultBg);
}

bool LevelResult::init()
{
    if (!CCLayer::init())
        return false;
    
    // 读取数据
    readData();
    
    // 获取游戏关卡背景并设置透明度
    addResultBg();
    
    // 显示关卡名称
    addLevelTitle();
    
    // 显示上方方框
    addToBar();
    
    // 显示下方方框
    addDownBar();
    
    // 显示菜单选项
    addMenuItems();
    
    // 显示游戏结果
    addResult();
    
    // 播放背景音乐
    playBgMusic();
    
    return true;
}

// 读取LevelManager中的数据
void LevelResult::readData()
{
    GameData *data = GameData::sharedData();
    _levelScore = data->getCurrentLevelScore()->getValue();
    _levelNumber = data->getSelectedLevel()->getValue();
    _chapterNumber = data->getSelectedChapter()->getNumber();
    
    _levelSolved = data->getLevelsCompleted()->getValue();
    _highScore = data->returnHighScoreForCurrentLevel();
    _levelClear = data->getCurrentLevelToSolved();
}

// 添加背景并设置透明度
void LevelResult::addResultBg()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    _resultBg = CCSprite::create("arts/level_result_interfaces/bg_levelresult.png");
    _resultBg->retain();
    
    _resultBg->setOpacity(100);
    _resultBg->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(_resultBg);
}

// 显示上面的方框
void LevelResult::addToBar()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    // add tobar
    CCSprite *tobar = CCSprite::create("arts/generally_buttons/levelbox1.png");
    
    tobar->setPosition(ccp(winSize.width/2, winSize.height*0.7));
    this->addChild(tobar);
}

// 显示下面的方框
void LevelResult::addDownBar()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    // add downbar
    CCSprite *downbar = CCSprite::create("arts/generally_buttons/levelbox2.png");
    downbar->setPosition(ccp(winSize.width/2, winSize.height*0.3));
    this->addChild(downbar);
}

// 显示关卡名称和历史最高得分
void LevelResult::addLevelTitle()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    // 显示关卡名称
    CCString *name = CCString::createWithFormat("第%d关",_levelNumber);
    CCLabelTTF *level = CCLabelTTF::create(name->getCString(), "Courier-Bold", 25);
    level->setPosition(ccp(winSize.width*0.4, winSize.height*0.65));
    this->addChild(level, 1);
    
    // 显示文本
    CCLabelTTF *text = CCLabelTTF::create("历史最高记录", "Courier", 20);
    text->setPosition(ccp(winSize.width*0.5, winSize.height*0.8));
    this->addChild(text, 1);
    
    // 显示历史最高得分
    CCString *highScore = CCString::createWithFormat("%d", _highScore);
    CCLabelTTF *showScore = CCLabelTTF::create(highScore->getCString(), "Courier", 25);
    showScore->setPosition(ccp(winSize.width*0.58, winSize.height*0.65));
    this->addChild(showScore, 2);
}

// 显示游戏结果
void LevelResult::addResult()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    if (_levelClear == false) {
        const char *failure = "当前关卡失败!";
        CCLabelTTF *showFailure = CCLabelTTF::create(failure, "ArialMT", 20);
        showFailure->setPosition(ccp(winSize.width*0.5, winSize.height*0.35));
        this->addChild(showFailure);
    } else if (_levelClear == true) {
        const char *clear = "当前关卡胜利!";
        CCLabelTTF *showClear = CCLabelTTF::create(clear,"ArialMT", 20);
        showClear->setPosition(ccp(winSize.width*0.45, winSize.height*0.4));
        this->addChild(showClear, 2);
        
        CCLabelTTF *text = CCLabelTTF::create("得分", "ArailMT", 20);
        text->setPosition(ccp(winSize.width*0.35, winSize.height*0.3));
        this->addChild(text, 2);
        
        CCString *score = CCString::createWithFormat("%d", _levelScore);
        CCLabelTTF *showScore = CCLabelTTF::create(score->getCString(), "ArialMT", 20);
        showScore->setPosition(ccp(winSize.width*0.55, winSize.height*0.3));
        this->addChild(showScore, 2);
    }
}

// 返回关卡选择界面
void LevelResult::backToLevelSelection(CCObject *pSender)
{
    // 停止播放音乐
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
    
    // 切换场景
//    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0, LevelSelection::scene()));
    SceneManager::goLevelSelect();
}

// 重玩当前关卡
void LevelResult::replayCurrentLevel(CCObject *pSender)
{
    // 停止播放音乐
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
    
    // 根据关卡编号进入不同的场景
    GameData::sharedData()->setSelectedLevel(CCInteger::create(_levelNumber));
    
    // 进入游戏界面
    SceneManager::goGameScene();
}

// 进入一个关卡
void LevelResult::playNextLevel(CCObject *pSender)
{
    // 停止播放音乐
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
    
    GameData *gameData = GameData::sharedData();
    
    // 判断下一个关卡是否已解锁
    int currentLevel = gameData->getSelectedLevel()->getValue();
    if (_levelClear == true &&  currentLevel < 10) {
        gameData->setSelectedLevel(CCInteger::create(currentLevel+1));
        // 进入游戏界面
        SceneManager::goGameScene();
    } else if (currentLevel == 10 && gameData->getSelectedChapter()->getNumber() < 5 && _levelClear) {
        gameData->getSelectedChapter()->setNumber((gameData->getSelectedChapter()->getNumber()+1));
        gameData->setSelectedLevel(CCInteger::create(1));
        
        Levels *selectLevels = LevelParser::loadLevelsForChapter(gameData->getSelectedChapter()->getNumber());
        
        // Iterate through the array of levels
        Level *level;
        CCObject *obj;
        CCARRAY_FOREACH(selectLevels->getLevels(), obj) {
            level = dynamic_cast<Level*>(obj);
            // look for currently selected lebel
            if (level->getNumber() == gameData->getSelectedLevel()->getValue()) {
                // 新章节的关卡1解锁
                level->setUnlocked(true);
            } else {
                level->setUnlocked(false);
            }
        }
        
        // save the new data
        LevelParser::saveDataForChapter(selectLevels, gameData->getSelectedChapter()->getNumber());
        
        // 进入新场景
        SceneManager::goLevelSelect();
    } else if (_chapterNumber >= 5) {
//        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, ChapterSelect::scene()));
        SceneManager::goChapterSelect();
    }
}

// 显示三个菜单选项
void LevelResult::addMenuItems()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCString *nextItemImage = CCString::create("arts/generally_buttons/button_nextlevel.png");
    if (_levelClear == false) {
        nextItemImage = CCString::create("arts/generally_buttons/button_panda.png");
    }
    
    CCMenuItemImage *backItem = CCMenuItemImage::create("arts/generally_buttons/button_menu.png", "arts/generally_buttons/button_menu.png", this, menu_selector(LevelResult::backToLevelSelection));
    CCMenuItemImage *replayItem = CCMenuItemImage::create("arts/generally_buttons/button_replay.png", "arts/generally_buttons/button_replay.png", this, menu_selector(LevelResult::replayCurrentLevel));
    CCMenuItemImage *nextItem = CCMenuItemImage::create(nextItemImage->getCString(), nextItemImage->getCString(),this, menu_selector(LevelResult::playBgMusic));
    
    backItem->setPosition(ccp(winSize.width*0.3, winSize.height*0.15));
    replayItem->setPosition(ccp(winSize.width*0.5, winSize.height*0.15));
    nextItem->setPosition(ccp(winSize.width*0.7, winSize.height*0.15));
    
    CCMenu *menu = CCMenu::create(backItem, replayItem, nextItem, NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
}

void LevelResult::playBgMusic()
{
    if (_levelClear) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("audio/gamewin.mp3", true);
    } else {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("audio/fail.mp3", true);
    }
}