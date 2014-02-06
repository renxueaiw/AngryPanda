//
//  IntroLayer.cpp
//  AngryPanda
//
//  Created by renxueaiw on 13-12-1.
//
//

#include "IntroLayer.h"
#include "game_interface/start/StartGameScene.h"

USING_NS_CC;

#pragma mark -IntroLayer
CCScene* IntroLayer::scene()
{
    CCScene *scene = CCScene::create();
    IntroLayer *layer = IntroLayer::create();
    scene->addChild(layer);
    
    return scene;
}

bool IntroLayer::init()
{
    if (!CCLayer::init())
        return false;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *background = CCSprite::create("Default.png");
    background->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(background);
    
    return true;
}

void IntroLayer::onEnter()
{
    CCLayer::onEnter();
    
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0, StartGameScene::scene()));
}

