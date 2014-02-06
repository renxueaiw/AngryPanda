//
//  LevelSelection.cpp
//  AngryPanda
//
//  Created by renxueaiw on 13-12-3.
//
//

#include "LevelSelection.h"
#include "../../game_data/game_state/GameData.h"
//#include "../chapter_select/ChpaterSelect.h"
#include "../../game_assist/game_scene_unify_switch_manager/SceneManager.h"
#include "SimpleAudioEngine.h"
#include "../../game_data/game_constants/Constants.h"
#include "../../game_data/level_data/Levels.h"
#include "../../game_data/level_data/Level.h"
#include "../../game_data/level_data/LevelParser.h"

USING_NS_CC;

CCScene* LevelSelection::scene()
{
    CCScene* scene = CCScene::create();
    LevelSelection *layer = LevelSelection::create();
    scene->addChild(layer);
    return scene;
}

LevelSelection::~LevelSelection()
{
    CC_SAFE_RELEASE(_currentChapter);
    
    CC_SAFE_RELEASE(_chapterTitle);
    CC_SAFE_RELEASE(_chapterIntro);
}

bool LevelSelection::init()
{
    if (!CCLayer::init())
        return false;
    // 读取场景数据
    readData();
    
    // 设置位置
    setMenuLocation();
    
    // 添加关卡选择菜单
    addLevelMenu();
    
    // 添加返回按钮
    addBackButton();
    
    // 播放背景音乐
    playBackgroundMusic();
    
    // 添加背景
    addLevelSelectBg();
    
    // 添加场景简介
    addChapterIntro();
    
    return true;
}

// 获取屏幕大小
void LevelSelection::getScreenSize()
{
    _screenSize = CCDirector::sharedDirector()->getWinSize();
}

// 设置各视觉元素的位置
void LevelSelection::setMenuLocation()
{
    getScreenSize();
    _backButtonLocation = ccp(_screenSize.width*0.15, _screenSize.height*0.85);
    
    _levelMenuLocation = ccp(_screenSize.width*0.5, _screenSize.height*0.45);
    _bgLocation = ccp(_screenSize.width*0.5, _screenSize.height*0.5);
    
    _chapterIntroLocation = ccp(_screenSize.width*0.5, _screenSize.height*0.75);
    _chapterTitleLocation = ccp(_screenSize.width*0.5, _screenSize.height*0.85);
}

// 添加章节的文字介绍
void LevelSelection::addChapterIntro()
{
    _chapterTitle = CCLabelTTF::create(_currentChapter->getName()->getCString(), "ArialMT", 16);
    _chapterTitle->retain();
    _chapterIntro = CCLabelTTF::create(_currentChapter->getIntro()->getCString(), "ArialMt", 12);
    _chapterIntro->retain();
    
    _chapterTitle->setPosition(_chapterTitleLocation);
    _chapterIntro->setPosition(_chapterIntroLocation);
    
    this->addChild(_chapterTitle);
    this->addChild(_chapterIntro);
}

// 从GameData类获取数据
void LevelSelection::readData()
{
    Chapter* currentChapter = GameData::sharedData()->getSelectedChapter();
    if (_currentChapter != currentChapter) {
        CC_SAFE_RETAIN(currentChapter);
        CC_SAFE_RELEASE(_currentChapter);
        _currentChapter = currentChapter;
    }
}

// 返回起始画面
void LevelSelection::addBackButton()
{
    getScreenSize();
    
    CCMenuItemImage* backButton = CCMenuItemImage::create("arts/generally_buttons/back.png", "arts/generally_buttons/back.png", this, menu_selector(LevelSelection::backToStart));
    CCMenu *menu = CCMenu::create(backButton, NULL);
    menu->setPosition(_backButtonLocation);
    this->addChild(menu, 1);
}

// 返回起始界面
void LevelSelection::backToStart()
{
//   CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, ChapterSelect::scene()));
    SceneManager::goChapterSelect();
}

// 添加背景音乐
void LevelSelection::playBackgroundMusic()
{
    GameData *data = GameData::sharedData();
    if (data->getBackgroundMusicMuted()->getValue() == false) {
        if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying() == false) {
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background_music/bg_startgamescene.mp3", true);
        }
    }
}

#pragma mark 添加关卡选择的背景
// 添加菜单背景
void LevelSelection::addLevelSelectBg()
{
    CCSprite *background = CCSprite::create("arts/level_choise/menu_background.png");
    background->setPosition(_bgLocation);
    this->addChild(background, zOrderLevelBg);
}

#pragma mark 添加关卡选择菜单
// 添加关卡选择菜单
void LevelSelection::addLevelMenu()
{
    // Read in selected Chapter levels
    CCMenu *levelMenu = CCMenu::create();
    CCArray *overlay = CCArray::create();
    
    Levels *selectLevels = LevelParser::loadLevelsForChapter(_currentChapter->getNumber());
    
    // create a button for every level
    Level *level;
    CCObject *obj;
    CCARRAY_FOREACH(selectLevels->getLevels(), obj) {
        level = dynamic_cast<Level*>(obj);
        
        CCMenuItemImage *item = CCMenuItemImage::create("arts/level_choise/level_bg.png", "arts/level_choise/level_bg.png", this, menu_selector(LevelSelection::onPlay));
        item->setTag(level->getNumber());
        item->setEnabled(level->getUnlocked());
        levelMenu->addChild(item);
        
        if (level->getUnlocked()) {
            CCSprite *overlaySprite = CCSprite::create(CCString::createWithFormat("arts/level_choise/%dStar-Normal.png", level->getStars())->getCString());
            overlaySprite->setTag(level->getNumber());
            overlay->addObject(overlaySprite);
        } else {
            CCSprite *overlaySprite = CCSprite::create("arts/level_choise/level_lock.png");
            overlaySprite->setTag(level->getNumber());
            overlay->addObject(overlaySprite);
        }
    }
    levelMenu->alignItemsInColumns(5,5,NULL);
    levelMenu->setPosition(_levelMenuLocation);
    this->addChild(levelMenu);
    
    // Create layers for star/padlock overlays & level number labels
    CCLayer *overLayers = CCLayer::create();
    CCLayer *labels = CCLayer::create();

    CCMenuItem *item;
    CCARRAY_FOREACH(levelMenu->getChildren(), obj)
    {
        item = dynamic_cast<CCMenuItem*>(obj);
        
        CCLabelTTF *label = CCLabelTTF::create(CCString::createWithFormat("%d", item->getTag())->getCString(), "Marker Felt", 25);
        label->setAnchorPoint(item->getAnchorPoint());
        label->setPosition(item->getPosition());
        labels->addChild(label, zOrderLevelText);
        
        // set position of overlay sprites
        CCSprite *olSprite; // overlaySprite
        CCARRAY_FOREACH(overlay, obj)
        {
            olSprite = dynamic_cast<CCSprite*>(obj);
            if (olSprite->getTag() == item->getTag()) {
                olSprite->setAnchorPoint(item->getAnchorPoint());
                olSprite->setPosition(item->getPosition());
                overLayers->addChild(olSprite, zOrderLevelText);
                break;
            }
        }
    }
    
    // put the overLayers and labelLayers on the screen at the same position as the levelMenu
    overLayers->setAnchorPoint(levelMenu->getAnchorPoint());
    overLayers->setPosition(levelMenu->getPosition());
    labels->setAnchorPoint(levelMenu->getAnchorPoint());
    labels->setPosition(levelMenu->getPosition());
    
    this->addChild(overLayers);
    this->addChild(labels);
}

void LevelSelection::onPlay(CCMenuItemImage* pSender)
{
    CCLog("onPlay.tag: %d", pSender->getTag());
    
    int selectedLevel = pSender->getTag();
    
    GameData::sharedData()->setSelectedLevel(CCInteger::create(selectedLevel));
    
    SceneManager::goGameScene();
}