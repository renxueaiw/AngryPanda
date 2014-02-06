//
//  StartGameScene.cpp
//  AngryPanda
//
//  Created by renxueaiw on 13-12-1.
//
//

#include "StartGameScene.h"
#include "SimpleAudioEngine.h"
#include "../../game_data/game_state/GameData.h"
//#include "../../game_assist/game_audio_manager/GameSounds.h"
//#include "../about/About.h"
//#include "../chapter_select/ChpaterSelect.h"
#include "../../game_assist/game_scene_unify_switch_manager/SceneManager.h"

USING_NS_CC;

CCScene* StartGameScene::scene()
{
    CCScene *scene = CCScene::create();
    StartGameScene *layer = StartGameScene::create();
    scene->addChild(layer);
    
    return scene;
}

StartGameScene::~StartGameScene()
{
    CC_SAFE_RELEASE(_bgGameStart);
    CC_SAFE_RELEASE(_gameTitle);
    CC_SAFE_RELEASE(_playItem);
    CC_SAFE_RELEASE(_aboutItem);
    CC_SAFE_RELEASE(_soundEffectMenu);
    CC_SAFE_RELEASE(_backgroundMusicMenu);
}

bool StartGameScene::init()
{
    if (!CCLayer::init())
        return false;
    
    addGameTitle();
    addBackground();
    
    setMenuLocation();
    addPlayItem();
    addAboutItem();
    
    createSoundSettingMenu();
    
    playBacgroundMusic();
    
        
    return true;
}

// 逻辑处理

void StartGameScene::addGameTitle()
{
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    
    _gameTitle = CCLabelTTF::create("ANGRYPANDA", "Noteworthy-Bold", 40);
    _gameTitle->retain();
    _gameTitle->setPosition(ccp(_screenSize.width/2, _screenSize.height*0.85));
    this->addChild(_gameTitle);
}

void StartGameScene::addBackground()
{
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    
    _bgGameStart = CCSprite::create("arts/start_interfaces/bg_startgame.png");
    _bgGameStart->retain();
    _bgGameStart->setPosition(ccp(_screenSize.width/2, _screenSize.height/2));
    this->addChild(_bgGameStart, -1);
}

void StartGameScene::addPlayItem()
{
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    _playItem = CCMenuItemImage::create("arts/start_interfaces/button_begin.png", "arts/start_interfaces/button_begin.png", this, menu_selector(StartGameScene::startGame));
    _playItem->retain();
    _playItem->setScale(0.5f);
    _playItem->setPosition(ccp(_screenSize.width*0.52, _screenSize.height*0.5));
    _playItem->runAction(CCScaleTo::create(2.0f, 0.9f));
    
    CCMenu *menu = CCMenu::create(_playItem, NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
}

// 添加about菜单项
void StartGameScene::addAboutItem()
{
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    
    _aboutItem = CCMenuItemImage::create("arts/start_interfaces/about.png", "arts/start_interfaces/about.png", this, menu_selector(StartGameScene::about));
    _aboutItem->retain();
    _aboutItem->setPosition(_aboutMenuLocation);
    CCMenu *menu = CCMenu::create(_aboutItem, NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
}

// 进入关卡选择画面
void StartGameScene::startGame(CCObject *pSender)
{
    // 进入关卡选择界面
//    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, ChapterSelect::scene()));
    SceneManager::goChapterSelect();
}

// 进入游戏介绍界面
void StartGameScene::about(CCObject *pSender)
{
//    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, About::scene()));
    SceneManager::goAboutScene();
}

// 添加背景韵
void StartGameScene::playBacgroundMusic()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
    
    GameData *data = GameData::sharedData();
    if (data->getBackgroundMusicMuted()->getValue() == false) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background_music/bg_startgamescene.mp3", true);
        CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.15f);
    }
}

#pragma mark 设置背影音乐选项
void StartGameScene::createBackgroundMusicMenuOn()
{
    this->removeChild(_backgroundMusicMenu);
    
    CCMenuItem *button1 = CCMenuItemImage::create("arts/start_interfaces/music_on.png","arts/start_interfaces/music_on.png", this, menu_selector(StartGameScene::turnBackgroundMusicOff));
    
    _backgroundMusicMenu = CCMenu::create(button1, NULL);
    _backgroundMusicMenu->retain();
    _backgroundMusicMenu->setPosition(_backgroundMusicMenuLocation);
    
    this->addChild(_backgroundMusicMenu, 10);
}

void StartGameScene::createBackgroundMusicMenuOff()
{
    this->removeChild(_backgroundMusicMenu);
    
    CCMenuItem *button1 = CCMenuItemImage::create("arts/start_interfaces/music_off.png", "arts/start_interfaces/music_off.png", this, menu_selector(StartGameScene::turnBackgroundMusicOn));
    
    _backgroundMusicMenu = CCMenu::create(button1, NULL);
    _backgroundMusicMenu->retain();
    _backgroundMusicMenu->setPosition(_backgroundMusicMenuLocation);
    
    this->addChild(_backgroundMusicMenu, 10);
}

void StartGameScene::turnBackgroundMusicOn(CCObject *pSender)
{
    GameData::sharedData()->setBackgroundMusicMuted(CCBool::create(false));
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    this->createBackgroundMusicMenuOn();
}

void StartGameScene::turnBackgroundMusicOff(CCObject *pSender)
{
    GameData::sharedData()->setBackgroundMusicMuted(CCBool::create(true));
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    this->createBackgroundMusicMenuOff();
}


#pragma mark 设置音效开关选项
// 创建音效开关选项
void StartGameScene::createSoundEffectMenuOn()
{
    this->removeChild(_soundEffectMenu);
    CCMenuItem *button1 = CCMenuItemImage::create("arts/start_interfaces/sound_on.png", "arts/start_interfaces/sound_on.png", this, menu_selector(StartGameScene::turnSoundEffectOff));
    
    _soundEffectMenu = CCMenu::create(button1, NULL);
    _soundEffectMenu->retain();
    _soundEffectMenu->setPosition(_soundEffectMenuLocation);
    
    this->addChild(_soundEffectMenu, 10);
}

void StartGameScene::createSoundEffectMenuOff()
{
    this->removeChild(_soundEffectMenu);
    CCMenuItem *button1 = CCMenuItemImage::create("arts/start_interfaces/sound_off.png", "arts/start_interfaces/sound_off.png", this, menu_selector(StartGameScene::turnSoundEffectOn));
    
    _soundEffectMenu = CCMenu::create(button1, NULL);
    _soundEffectMenu->retain();
    _soundEffectMenu->setPosition(_soundEffectMenuLocation);
    
    this->addChild(_soundEffectMenu, 10);
}

void StartGameScene::turnSoundEffectOff(CCObject *pSender)
{
//    GameSounds::sharedGameSounds()->disableSoundEffect();
    this->createSoundEffectMenuOff();
}

void StartGameScene::turnSoundEffectOn(CCObject *pSender)
{
//    GameSounds::sharedGameSounds()->enableSoundEffect();
    this->createSoundEffectMenuOn();
}

#pragma mark 设置菜单的位置

void StartGameScene::setMenuLocation()
{
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    
    _soundEffectMenuLocation = ccp(_screenSize.width*0.375, _screenSize.height*0.15);
    _backgroundMusicMenuLocation = ccp(_screenSize.width*0.5, _screenSize.height*0.15);
    _aboutMenuLocation = ccp(_screenSize.width*0.625, _screenSize.height*0.15);
}

#pragma mark 创建声音的两个选项
void StartGameScene::createSoundSettingMenu()
{
    if (GameData::sharedData()->getSoundEffectMuted()->getValue() == false) {
        this->createSoundEffectMenuOn();
    } else {
        this->createSoundEffectMenuOff();
    }
    if (GameData::sharedData()->getBackgroundMusicMuted()->getValue() == false) {
        this->createBackgroundMusicMenuOn();
    } else {
        this->createBackgroundMusicMenuOff();
    }
}

