//
//  GameSounds.cpp
//  AngryPanda
//
//  Created by renxueaiw on 13-11-30.
//
//

#include "GameSounds.h"
#include "SimpleAudioEngine.h"
#include "../../game_data/game_constants/Constants.h"
#include "../../game_data/game_state/GameData.h"

USING_NS_CC;

static GameSounds *_sharedGameSounds = NULL;

// 单例类方法
GameSounds* GameSounds::sharedGameSounds()
{
    if (_sharedGameSounds == NULL) {
        _sharedGameSounds = new GameSounds();
        _sharedGameSounds->init();
    }
    
    return _sharedGameSounds;
}

// 场景初始化
bool GameSounds::init()
{
    if (!CCNode::init())
        return false;
    
    return true;
}

// 禁用音效
void GameSounds::disableSoundEffect()
{
    GameData::sharedData()->setSoundEffectMuted(CCBool::create(true));
}

// 启用音效
void GameSounds::enableSoundEffect()
{
    GameData::sharedData()->setSoundEffectMuted(CCBool::create(false));
}

// 播放背景音乐
void GameSounds::playBackgroundMusic()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
    if (GameData::sharedData()->getBackgroundMusicMuted()->getValue() == false) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("audio/birds.mp3", true);
        CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.15f);
    }
}

// 停止背景音乐
void GameSounds::stopBackGroundMusic()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
    GameData::sharedData()->setBackgroundMusicMuted(CCBool::create(true));
}