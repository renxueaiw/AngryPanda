//
//  GamePause.cpp
//  AngryPanda
//
//  Created by renxueaiw on 13-12-24.
//
//

#include "GamePause.h"
#include "../../game_assist/game_audio_manager/GameSounds.h"
#include "SimpleAudioEngine.h"
#include "../../game_data/game_state/GameData.h"
#include "../../game_data/game_constants/Constants.h"
#include "../../game_assist/game_scene_unify_switch_manager/SceneManager.h"

USING_NS_CC;
GamePause::~GamePause()
{
    CC_SAFE_RELEASE(_delegate);
    CC_SAFE_RELEASE(_bg);
}

GamePause* GamePause::createWithColor(cocos2d::ccColor4B color, PauseLayerProtocol *delegate)
{
    GamePause *layer = new GamePause();
    layer->initWithColor(color, delegate);
    layer->autorelease();
    return layer;
}

bool GamePause::initWithColor(cocos2d::ccColor4B color, PauseLayerProtocol *delegate)
{
    if (!CCLayerColor::initWithColor(color))
        return false;
    setDelegate(delegate);
    
    pauseDelegate();
    addBg();
    createPausedMenu();
    
    return true;
}

// 添加背景
void GamePause::addBg()
{
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    _bg = CCSprite::create("arts/pause_interfaces/bg_pause.png");
    _bg->retain();
    _bg->setPosition(ccp(_screenSize.width/2, _screenSize.height/2));
    addChild(_bg, -1);
}

// 创建暂停画面
void GamePause::createPausedMenu()
{
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    
    CCMenuItemImage *buttonPlay = CCMenuItemImage::create("arts/generally_buttons/button_play.png", "arts/generally_buttons/button_play.png", this, menu_selector(GamePause::resumeCurrentLevel));
    CCMenuItemImage *buttonMenu = CCMenuItemImage::create("arts/generally_buttons/button_menu.png", "arts/generally_buttons/button_menu.png", this, menu_selector(GamePause::goLevelSelection));
    CCMenuItem *buttonReplay = CCMenuItemImage::create("arts/generally_buttons/button_replay.png", "arts/generally_buttons/button_replay.png", this, menu_selector(GamePause::replayCurrentLevel));
    
    buttonPlay->setPosition(ccp(_screenSize.width*0.35f, _screenSize.height*0.5f));
    buttonMenu->setPosition(ccp(_screenSize.width*0.15f, _screenSize.height*0.3f));
    buttonReplay->setPosition(ccp(_screenSize.width*0.15f, _screenSize.height*0.7f));
    
    CCMenu *menu = CCMenu::create(buttonPlay, buttonMenu, buttonReplay,NULL);
    menu->setPosition(CCPointZero);
    addChild(menu, 1);
}

void GamePause::resumeCurrentLevel(CCObject *pSender)
{
    this->runAction(CCSequence::create(CCDelayTime::create(0.1f),
                                       CCCallFunc::create(this, callfunc_selector(GamePause::doResume)), NULL));
    
}

void GamePause::replayCurrentLevel(CCObject *pSender)
{
    SceneManager::goGameScene();
}

void GamePause::goLevelSelection(CCObject *pSender)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
    SceneManager::goLevelSelect();
}

void GamePause::pauseDelegate()
{
    _delegate->pauseLayerDidPause();
    _delegate->onExit();
    _delegate->getParent()->addChild(this, 10);
}

void GamePause::doResume(CCNode *pSender)
{
    _delegate->onEnter();
    _delegate->pauseLayerDidUnPause();
    this->getParent()->removeChild(this, true);
}


// getter && setter
PauseLayerProtocol* GamePause::getDelegate()
{
    return _delegate;
}
void GamePause::setDelegate(PauseLayerProtocol *delegate)
{
    if (_delegate != delegate) {
        CC_SAFE_RETAIN(delegate);
        CC_SAFE_RELEASE(_delegate);
        _delegate = delegate;
    }
}