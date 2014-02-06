//
//  SceneManager.cpp
//  AngryPanda
//
//  Created by renxueaiw on 13-12-24.
//
//

#include "SceneManager.h"

USING_NS_CC;

#pragma mark swap scene
void SceneManager::goStartGame()
{
    SceneManager::go(StartGameScene::create());
}

void SceneManager::goAboutScene()
{
    SceneManager::go(About::create());
}

void SceneManager::goChapterSelect()
{
    SceneManager::go(ChapterSelect::create());
}

void SceneManager::goLevelSelect()
{
    SceneManager::go(LevelSelection::create());
}

void SceneManager::goLevelResult()
{
    SceneManager::go(LevelResult::create());
}

void SceneManager::goGameScene()
{
    SceneManager::go(MainScene::create());
}

#pragma mark private method
CCScene* SceneManager::wrap(CCLayer *layer)
{
    CCScene *pScene = CCScene::create();
    pScene->addChild(layer);
    return pScene;
}

void SceneManager::go(CCLayer *layer)
{
    CCDirector *director = CCDirector::sharedDirector();
    CCScene *pScene = SceneManager::wrap(layer);
    
    if (director->getRunningScene()) {
        director->replaceScene(CCTransitionFade::create(1.0f, pScene));
    } else {
        director->runWithScene(CCTransitionFade::create(1.0f, pScene));
    }
}
