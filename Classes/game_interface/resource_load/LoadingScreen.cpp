//
//  LoadingScreen.cpp
//  AngryPanda
//
//  Created by renxueaiw on 13-12-23.
//
//

#include "LoadingScreen.h"
#include "SimpleAudioEngine.h"

// The next scene you wish to transition to.
//#include "../../IntroLayer.h"
#include "../start/StartGameScene.h"
#include "../../game_data/game_state/GameData.h"
#include "../../game_data/game_constants/Constants.h"

USING_NS_CC;

CCScene* LoadingScreen::scene()
{
    CCScene *pScene = CCScene::create();
    CCLayer *layer = LoadingScreen::create();
    pScene->addChild(layer);
    
    return pScene;
}

LoadingScreen::~LoadingScreen()
{
    CC_SAFE_RELEASE(_progress);
}

bool LoadingScreen::init()
{
    if (!CCLayer::init())
        return false;
    
    _assetCount = 0;
    _progressInterval = 0.0f;
    
    _winSize = CCDirector::sharedDirector()->getWinSize();
    _winCenter = ccp(_winSize.width/2, _winSize.height/2);
    
    CCSprite *loadingBg = CCSprite::create("arts/resource_load/loading_bg.png");
    loadingBg->setPosition(_winCenter);
    addChild(loadingBg, -1);
    
    // Load your assets (background, progress bars, etc)
    _progress = CCProgressTimer::create(CCSprite::create("arts/resource_load/progressbar.png"));
    _progress->retain();
    _progress->setPercentage(0.0f);
    _progress->setScale(0.5f);
    _progress->setMidpoint(ccp(0.0f, 0.5f));
    _progress->setBarChangeRate(ccp(1.0f, 0.0f));
    _progress->setType(kCCProgressTimerTypeBar);
    _progress->setPosition(_winCenter);
    addChild(_progress);
    
    CCLabelTTF *loadingText = CCLabelTTF::create("Loading...", "Arial", 20);
    loadingText->setPosition(ccpAdd(_progress->getPosition(), ccp(0, 50)));
    addChild(loadingText);
    
    return true;
}

void LoadingScreen::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
    const char *path = CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile("preloadAssetManifest.plist", "");
    
    CCDictionary *manifest = CCDictionary::createWithContentsOfFile(path);
    
    CCArray *spriteSheets = dynamic_cast<CCArray*>(manifest->objectForKey("SpriteSheets"));
    CCArray *images = dynamic_cast<CCArray*>(manifest->objectForKey("Images"));
    CCArray *soundFX = dynamic_cast<CCArray*>(manifest->objectForKey("SoundFX"));
    CCArray *music = dynamic_cast<CCArray*>(manifest->objectForKey("Music"));
    CCArray *assets = dynamic_cast<CCArray*>(manifest->objectForKey("Assets"));
    
    _assetCount = (spriteSheets->count()+images->count()+soundFX->count()+music->count()+assets->count());
    _progressInterval = 100.0f / (float)_assetCount;
    
    if (soundFX) {
        runAction(CCCallFuncO::create(this, callfuncO_selector(LoadingScreen::loadSounds), soundFX));
    }
    
    if (spriteSheets) {
        runAction(CCCallFuncO::create(this, callfuncO_selector(LoadingScreen::loadSpriteSheets), spriteSheets));
    }
    
    if (images) {
        runAction(CCCallFuncO::create(this, callfuncO_selector(LoadingScreen::loadImages), images));
    }
    
    if (music) {
        runAction(CCCallFuncO::create(this, callfuncO_selector(LoadingScreen::loadMusic), music));
    }
    
    if (assets) {
        runAction(CCCallFuncO::create(this, callfuncO_selector(LoadingScreen::loadAssets), assets));
    }
}

void LoadingScreen::loadMusic(cocos2d::CCArray *musicFiles)
{
    CCLog("LoadinScreen - loadMusic");
    CCObject *obj;
    CCString *music;
    CCARRAY_FOREACH(musicFiles, obj) {
        music = dynamic_cast<CCString*>(obj);
        CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(music->getCString());
        this->progressUpdate();
    }
}

void LoadingScreen::loadSounds(cocos2d::CCArray *soundClips)
{
    CCLog("LoadingScreen - loadSounds");
    CCObject *obj;
    CCString *soundClip;
    CCARRAY_FOREACH(soundClips, obj) {
        soundClip = dynamic_cast<CCString*>(obj);
        CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(soundClip->getCString());
        this->progressUpdate();
    }
}

void LoadingScreen::loadSpriteSheets(cocos2d::CCArray *spriteSheets)
{
    CCLog("LoadinScreen - loadSpriteSheets");
    CCObject *obj;
    CCString *spriteSheet;
    CCARRAY_FOREACH(spriteSheets, obj) {
        spriteSheet = dynamic_cast<CCString*>(obj);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(spriteSheet->getCString());
        this->progressUpdate();
    }
}

void LoadingScreen::loadImages(cocos2d::CCArray *images)
{
    CCLog("LoadingScreen - loadImages");
    CCObject *obj;
    CCString *image;
    CCARRAY_FOREACH(images, obj) {
        image = dynamic_cast<CCString*>(obj);
        CCTextureCache::sharedTextureCache()->addImage(image->getCString());
        this->progressUpdate();
    }
}

void LoadingScreen::loadAssets(cocos2d::CCArray *assets)
{
    CCLog("LoadingScreen - loadAssets");
    CCObject *obj;
    CCString *asset;
    CCARRAY_FOREACH(assets, obj) {
        asset = dynamic_cast<CCString*>(obj);
        // Do nothing with the assets
        this->progressUpdate();
    }
}

void LoadingScreen::progressUpdate()
{
//    CCLog("_assetCount: %d", _assetCount);
    if (--_assetCount) {
        _progress->setPercentage(100.0f - (_progressInterval * _assetCount));
    } else {
        CCProgressFromTo *ac = CCProgressFromTo::create(0.5f, _progress->getPercentage(), 100.0f);
        CCCallFunc *callBlock = CCCallFunc::create(this, callfunc_selector(LoadingScreen::loadingComplete));
        _progress->runAction(CCSequence::create(ac, callBlock, NULL));
    }
}

void LoadingScreen::loadingComplete()
{
    this->runAction(CCSequence::create(
                                       CCDelayTime::create(2.0f),
                                       CCCallFunc::create(this, callfunc_selector(LoadingScreen::toStartGameScene)),NULL));
}

void LoadingScreen::toStartGameScene()
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, StartGameScene::scene()));
}

