//
//  ChpaterSelect.cpp
//  AngryPanda
//
//  Created by renxueaiw on 13-12-3.
//
//

#include "ChpaterSelect.h"
#include "../../game_data/game_constants/Constants.h"
#include "../../game_data/game_state/GameData.h"
#include "SimpleAudioEngine.h"
//#include "../start/StartGameScene.h"
#include "../../game_assist/game_scene_unify_switch_manager/SceneManager.h"
#include "../../game_data/scene_data/Chapters.h"
#include "../../game_data/scene_data/Chapter.h"
#include "../level_selection/LevelSelection.h"

#define TABLE_CELL_ZOOM_RATIO 0.9f // 表单元缩放比率

USING_NS_CC;
USING_NS_CC_EXT;

CCScene* ChapterSelect::scene()
{
    CCScene *scene = CCScene::create();
    ChapterSelect *layer = ChapterSelect::create();
    scene->addChild(layer);
    return scene;
}

ChapterSelect::~ChapterSelect()
{
    CC_SAFE_RELEASE(_chapters);
}

bool ChapterSelect::init()
{
    if (!CCLayer::init())
        return false;
    
    // 设置位置
    this->setMenuLocation();
    
    // 添加背景
    this->addBackground();
    
    // 播放音乐
    this->playBackgroundMusic();
    
    // 添加菜单选项
    this->addBackButton();
    
    // 添加场景选择
    this->addScrollChapters();
    
    return true;
}

// 获取屏幕大小
void ChapterSelect::getScreenSize()
{
    _screenSize = CCDirector::sharedDirector()->getWinSize();
}

#pragma mark 设置菜单的位置
void ChapterSelect::setMenuLocation()
{
    getScreenSize();
    _backButtonLocation = ccp(_screenSize.width*0.15, _screenSize.height*0.85);
    _storeButtonLocation = ccp(_screenSize.width*0.85, _screenSize.height*0.1);
    _textLocation = ccp(_screenSize.width*0.5, _screenSize.height*0.75);
    _chapterLocation = ccp(_screenSize.width*0.5, _screenSize.height*0.5);
    _bgLocation = ccp(_screenSize.width*0.5, _screenSize.height*0.5);
}

// 添加背景图片
void ChapterSelect::addBackground()
{
    CCSprite *background = CCSprite::create("arts/level_choise/menu_background.png");
    background->setPosition(_bgLocation);
    this->addChild(background, zOrderChapterBg);
}

// 播放背景音乐
void ChapterSelect::playBackgroundMusic()
{
    if (GameData::sharedData()->getBackgroundMusicMuted()->getValue() == false) {
        if (!CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) {
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background_music/bg_startgamescene.mp3", true);
        }
    }
}

// 返回起始画面
void ChapterSelect::backToStart(CCObject *pSender)
{
//    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, StartGameScene::scene()));
    SceneManager::goStartGame();
}

// 添加返回按钮
void ChapterSelect::addBackButton()
{
    getScreenSize();
    CCMenuItem *backButton = CCMenuItemImage::create("arts/generally_buttons/back.png", "arts/generally_buttons/back.png", this, menu_selector(ChapterSelect::backToStart));
    CCMenu *menu = CCMenu::create(backButton, NULL);
    menu->setPosition(_backButtonLocation);
    this->addChild(menu, 1);
}

#pragma mark 选择关卡场景

// 添加滚动章节
void ChapterSelect::addScrollChapters()
{
    getScreenSize();
    _chapters = ChapterParser::loadData();
    _chapters->retain();
    
    // 设置成滚动层
    CCTableView *tableView = CCTableView::create(this, CCSizeMake(_screenSize.width*0.7, _screenSize.height*0.7));
    tableView->setDirection(kCCScrollViewDirectionHorizontal);
    tableView->setPosition(ccp(_screenSize.width*0.3/2, _screenSize.height*0.4/2));
    tableView->setDelegate(this);
    this->addChild(tableView);
    tableView->reloadData();
    
}

//单元格点击事件
void ChapterSelect::tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell)
{
    //TODO 进入关卡选择界面
    GameData *data = GameData::sharedData();
    data->setSelectedChapter(dynamic_cast<Chapter*>(_chapters->getChapters()->objectAtIndex(cell->getIdx())));
//    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, LevelSelection::scene()));
    SceneManager::goLevelSelect();
}
//单元格尺寸设定
cocos2d::CCSize ChapterSelect::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    return CCSizeMake(258+30, 153+20);
}
//单元格索引
cocos2d::extension::CCTableViewCell* ChapterSelect::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    Chapter *chapter = dynamic_cast<Chapter*>(_chapters->getChapters()->objectAtIndex(idx));
    CCTableViewCell *cell = table->dequeueCell();
    cell = new CCTableViewCell();
    cell->autorelease();
//    CCLog("image: %s", chapter->getImage()->getCString());
    CCSprite *sprite = CCSprite::create(chapter->getImage()->getCString());
    sprite->setAnchorPoint(ccp(0.5, 0.5));
    sprite->setPosition(ccp(258/2, 152/2));
    cell->addChild(sprite);
        
    CCLabelTTF *label = CCLabelTTF::create(chapter->getName()->getCString(), "Helvetica", 20.0);
    label->setPosition(ccp(258/2,180));
    label->setAnchorPoint(ccp(0.5, 0.5));
    label->setTag(123);
    cell->addChild(label);
    
    return cell;
}
//单元格数量设定
unsigned int ChapterSelect::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
    return 5;
}


