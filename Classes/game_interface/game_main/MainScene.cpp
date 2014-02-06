//
//  MainScene.cpp
//  AngryPanda
//
//  Created by renxueaiw on 13-12-24.
//
//

#include "MainScene.h"
#include "../../visual_element/custom_animation/CustomAnimation.h"
#include "../level_result/LevelResult.h"
#include "../pause/GamePause.h"
#include "../../game_data/level_data/Level.h"
#include "../../game_data/level_data/Levels.h"
#include "../../game_data/level_data/LevelParser.h"
#include "SimpleAudioEngine.h"
#include "../../game_assist/game_scene_unify_switch_manager/SceneManager.h"
#include "../../game_data/game_state/GameData.h"
#include "../../game_data/game_constants/Constants.h"
#include "../../visual_element/stack_object/StackObject.h"
#include "../../visual_element/shooting_target/ShootingTargets.h"
#include "../level_selection/LevelSelection.h"
#include "../../game_assist/game_audio_manager/GameSounds.h"
#include "../../visual_element/fire_platform/FirePlatform.h"
#include "../../visual_element/ground_plane/GroundPlane.h"

USING_NS_CC;
USING_NS_CC_EXT;

// MainScene implementation
static MainScene *layerInstance;

MainScene* MainScene::sharedMainScene() {
    CCAssert(layerInstance != NULL, "初始化成功！");
    
    return layerInstance;
}

// 场景类初始化
CCScene* MainScene::scene() {
    // 'scene' is an autorelease object.
    CCScene *pScene = CCScene::create();
    
    // 'layer' is an autorelease object.
    MainScene *layer = MainScene::create();
    
    // add layer as a child to scene
    pScene->addChild(layer, -1);
    
    return pScene;
}

MainScene::~MainScene()
{
    CC_SAFE_RELEASE(_panda1);
    CC_SAFE_RELEASE(_panda2);
    CC_SAFE_RELEASE(_panda3);
    CC_SAFE_RELEASE(_panda4);
    CC_SAFE_RELEASE(_panda5);
    CC_SAFE_RELEASE(_system);
    CC_SAFE_RELEASE(_backgroundLayerClouds);
    CC_SAFE_RELEASE(_backgroundLayerHills);
    CC_SAFE_RELEASE(_slingShotFront);
    CC_SAFE_RELEASE(_strapFront);
    CC_SAFE_RELEASE(_strapBack);
    CC_SAFE_RELEASE(_strapEmpty);
    CC_SAFE_RELEASE(_currentScoreLabel);
    CC_SAFE_RELEASE(_pauseButtonMenu);
    CC_SAFE_RELEASE(_groundPlaneFileName);

    //    CC_SAFE_RELEASE(_contactListener);
    CC_SAFE_DELETE(_debugDraw);
}

bool MainScene::init()
{
    if (!CCLayer::init())
        return false;
    layerInstance = this;
    _stretchBeyondRange = 0;
    _particleSystemStartPosition=CCPointZero; // 若有不对，及时修改
    
    // 在场景中启用对触摸事件的支持
    this->setTouchEnabled(true);

    // 读取数据&&设置属性
    readData();

    // 设置初始位置
    setInitialPosition();

    // 添加关卡介绍
    addLevelIntroLabel();

    // 添加得分和历史最高得分标签
    addScoreLabel();
    updatePointsLabel();

    // 添加暂停按钮
    addPauseButton();

    // 设置Box2D
    initPhysics();
    initContactListener();

    // 添加游戏世界中的各种物体
    addGroundPlaneBody();
    addFirePlatform();
    addPanda();
    addTargets();

    // 加载游戏音效和背景音乐
    initSounds();

    // 实时更新游戏中的物体所在位置
//    schedule(schedule_selector(MainScene::tick));
    
    return true;
}

// 从GameData读取数据，并设置一些基本的参数
void MainScene::readData() {
    _throwInProgress = false; // 是否当前有抛投在进行中，用于防止同时抛投两个熊猫
    _areWeInTheStartingPostion = true; // 场景在x轴是否为0(如果是，则将熊猫放置在弹弓上)
    
    _throwCount = 0;
    _dotTotalOnOddNumberedTurn = 0;
    _dotTotalOnEvenNumberedTurn = 0;
    
    _currentLevel = GameData::sharedData()->getSelectedLevel()->getValue();
    _scoreForCurrentLevel = 0;
    
    // 根据关卡编号的不同设置和其它数值，此处可以优化为放到plist,xml或Constants.h中
    switch (_currentLevel) {
        case 1:
        {
            _backgroundLayerClouds = CCSprite::create("arts/game_main_scenes/background_clouds.png");
            _backgroundLayerClouds->retain();
            _backgroundLayerHills = CCSprite::create("arts/game_main_scenes/background_hills.png");
            _backgroundLayerHills->retain();
            _groundPlaneFileName = CCString::create("ground_plane");
            _groundPlaneFileName->retain();
            _scoreForCurrentLevel = 10000;
            _bonusPerLeftPanda = 10000;
            _pandasToTossThisLevel = 1;
        }
            break;
        case 2:
        {
            _backgroundLayerClouds = CCSprite::create("arts/game_main_scenes/background_clouds.png");
            _backgroundLayerClouds->retain();
            _backgroundLayerHills = CCSprite::create("arts/game_main_scenes/background_hills.png");
            _backgroundLayerHills->retain();
            _groundPlaneFileName = CCString::create("ground_plane");
            _groundPlaneFileName->retain();
            _scoreForCurrentLevel = 12000;
            _bonusPerLeftPanda = 10000;
            _pandasToTossThisLevel = 2;
        }
            break;
        case 3:
        {
            _backgroundLayerClouds = CCSprite::create("arts/game_main_scenes/background_clouds.png");
            _backgroundLayerClouds->retain();
            _backgroundLayerHills = CCSprite::create("arts/game_main_scenes/background_hills.png");
            _backgroundLayerHills->retain();
            _groundPlaneFileName = CCString::create("ground_plane");
            _groundPlaneFileName->retain();
            _scoreForCurrentLevel = 15000;
            _bonusPerLeftPanda = 10000;
            _pandasToTossThisLevel = 3;
        }
            break;
        case 4:
        {
            _backgroundLayerClouds = CCSprite::create("arts/game_main_scenes/background_clouds.png");
            _backgroundLayerClouds->retain();
            _backgroundLayerHills = CCSprite::create("arts/game_main_scenes/background_hills.png");
            _backgroundLayerHills->retain();
            _groundPlaneFileName = CCString::create("ground_plane");
            _groundPlaneFileName->retain();
            _scoreForCurrentLevel = 15000;
            _bonusPerLeftPanda = 10000;
            _pandasToTossThisLevel = 4;
        }
            break;
        case 5:
        {
            _backgroundLayerClouds = CCSprite::create("arts/game_main_scenes/background_clouds.png");
            _backgroundLayerClouds->retain();
            _backgroundLayerHills = CCSprite::create("arts/game_main_scenes/background_hills.png");
            _backgroundLayerHills->retain();
            _groundPlaneFileName = CCString::create("ground_plane");
            _groundPlaneFileName->retain();
            _scoreForCurrentLevel = 15000;
            _bonusPerLeftPanda = 10000;
            _pandasToTossThisLevel = 5;
        }
            break;
        case 6:
        {
            _backgroundLayerClouds = CCSprite::create("arts/game_main_scenes/background_clouds.png");
            _backgroundLayerClouds->retain();
            _backgroundLayerHills = CCSprite::create("arts/game_main_scenes/background_hills.png");
            _backgroundLayerHills->retain();
            _groundPlaneFileName = CCString::create("ground_plane");
            _groundPlaneFileName->retain();
            _scoreForCurrentLevel = 15000;
            _bonusPerLeftPanda = 10000;
            _pandasToTossThisLevel = 6;
        }
            break;
        case 7:
        {
            _backgroundLayerClouds = CCSprite::create("arts/game_main_scenes/background_clouds.png");
            _backgroundLayerClouds->retain();
            _backgroundLayerHills = CCSprite::create("arts/game_main_scenes/background_hills.png");
            _backgroundLayerHills->retain();
            _groundPlaneFileName = CCString::create("ground_plane");
            _groundPlaneFileName->retain();
            _scoreForCurrentLevel = 15000;
            _bonusPerLeftPanda = 10000;
            _pandasToTossThisLevel = 7;
        }
            break;
        case 8:
        {
            _backgroundLayerClouds = CCSprite::create("arts/game_main_scenes/background_clouds.png");
            _backgroundLayerClouds->retain();
            _backgroundLayerHills = CCSprite::create("arts/game_main_scenes/background_hills.png");
            _backgroundLayerHills->retain();
            _groundPlaneFileName = CCString::create("ground_plane");
            _groundPlaneFileName->retain();
            _scoreForCurrentLevel = 15000;
            _bonusPerLeftPanda = 10000;
            _pandasToTossThisLevel = 8;
        }
            break;
        case 9:
        {
            _backgroundLayerClouds = CCSprite::create("arts/game_main_scenes/background_clouds.png");
            _backgroundLayerClouds->retain();
            _backgroundLayerHills = CCSprite::create("arts/game_main_scenes/background_hills.png");
            _backgroundLayerHills->retain();
            _groundPlaneFileName = CCString::create("ground_plane");
            _groundPlaneFileName->retain();
            _scoreForCurrentLevel = 15000;
            _bonusPerLeftPanda = 10000;
            _pandasToTossThisLevel = 9;
        }
            break;
        case 10:
        {
            _backgroundLayerClouds = CCSprite::create("arts/game_main_scenes/background_clouds.png");
            _backgroundLayerClouds->retain();
            _backgroundLayerHills = CCSprite::create("arts/game_main_scenes/background_hills.png");
            _backgroundLayerHills->retain();
            _groundPlaneFileName = CCString::create("ground_plane");
            _groundPlaneFileName->retain();
            _scoreForCurrentLevel = 15000;
            _bonusPerLeftPanda = 10000;
            _pandasToTossThisLevel = 10;
        }
            break;
        default:
        {
            _backgroundLayerClouds = CCSprite::create("arts/game_main_scenes/background_clouds.png");
            _backgroundLayerClouds->retain();
            _backgroundLayerHills = CCSprite::create("arts/game_main_scenes/background_hills.png");
            _backgroundLayerHills->retain();
            _groundPlaneFileName = CCString::create("ground_plane");
            _groundPlaneFileName->retain();
            _scoreForCurrentLevel = 10000;
            _bonusPerLeftPanda = 10000;
            _pandasToTossThisLevel = 1;
        }
            break;
    }
    
    // 参数设置
    _continuePanningScreenOnFingerRelease = true; // 如果场景平移正在弹弓或目标间移动，当玩家松开手指时，场景会继续朝之前的方向平移
    _reverseHowFingerPansScreen = false; // 如果要反向则设置为true
    
    //设置背景图片
    addChild(_backgroundLayerClouds, zOrderClouds);
    addChild(_backgroundLayerHills, zOrderHills);
    _backgroundLayerHills->setScaleX(1.05f);
    
    // 弹弓的视觉效果
    _slingShotFront = CCSprite::create("arts/game_main_scenes/slingshot_front.png");
    _slingShotFront->retain();
    addChild(_slingShotFront, zOrderSlingShotFront);
    
    _strapFront = CCSprite::create("arts/game_main_scenes/strap.png");
    _strapFront->retain();
    addChild(_strapFront, zOrderStrapFront);
    
    _strapBack = CCSprite::create("arts/game_main_scenes/strapBack.png");
    _strapBack->retain();
    addChild(_strapBack, zOrderStrapBack);
    
    _strapEmpty = CCSprite::create("arts/game_main_scenes/strapEmpty.png");
    _strapEmpty->retain();
    addChild(_strapEmpty, zOrderStrapBack);
    
    _strapBack->setVisible(false); // 仅在拉伸时可见
    _strapFront->setVisible(false); // 仅在拉伸时可见
}

// 设置初始位置
void MainScene::setInitialPosition() {
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    _screenWidth = winSize.width;
    _screenHeight = winSize.height;
    
    _currentScoreLabelPostion = ccp(_screenWidth*0.5f, _screenHeight*0.9f);
    
    // is_android
    // 变量
    _maxStretchOfSlingShot = 75; // 应为源图片大小的1/4
    _multiplyThrowPower = 1.0f; //数值可以在0.5到1.5之间，需要精细调整
    
    _worldMaxToHorizontalShift = -(_screenWidth); // 玩家可以朝左或朝右滑动以查看整个平台，通常为负值
    _maxScaleDownValue = 0.65f; // 范围应在0.75到1.0之间
    _scaleAmount = 0.01; // 当拖动场景时用于调整场景比例的增量
    _initialPanAmount = 30; // 屏幕场景开始拖动时的速度
    _extraAmountOnPanBack = 10; // 向回拖动时的增量
    _adjustY = -34;
    
    // 背景
    _backgroundLayerClouds->setPosition(ccp(_screenWidth, 192));
    _backgroundLayerClouds->setScale(0.7f);
    _backgroundLayerHills->setPosition(ccp(_screenWidth,245));
    _backgroundLayerHills->setScale(0.7f);
    
    _pauseButtonPosition = ccp(50, _screenHeight-30);
    _fontSizeForScore = 18;
    
    // 地平面和平台
    _groundPlaneStartPosition = ccp(_screenWidth, -25);
    _platformStartPosition = ccp(185, 110);
    
    // 弹弓
    _slingShotCenterPosition = ccp(160, 160);
    _slingShotFront->setPosition(ccp(164, 145));
    _strapFront->setPosition(ccp(_slingShotCenterPosition.x, _slingShotCenterPosition.y));
    _strapBack->setPosition(ccp(_slingShotCenterPosition.x+33, _slingShotCenterPosition.y-10));
    _strapEmpty->setPosition(ccp(168, 145));
    
    // 熊猫
    _pandaStartPosition1 = ccp(170, 175);
    _pandaStartPosition2 = ccp(110, 82);
    _pandaStartPosition3 = ccp(65, 82);
    _pandaStartPosition4 = ccp(90, 65);
    _pandaStartPosition5 = ccp(43, 65);
    
    // 记录物体的起始位置
    _hillsLayerStartPosition = _backgroundLayerHills->getPosition();
    _cloudLayerStartPosition = _backgroundLayerClouds->getPosition();
}

// 添加暂停按钮
void MainScene::addPauseButton() {
    CCMenuItemImage *pauseButton = CCMenuItemImage::create("arts/game_main_scenes/button_pause.png", "arts/game_main_scenes/button_pause.png", this, menu_selector(MainScene::pauseGame));
    _pauseButtonMenu = CCMenu::create(pauseButton, NULL);
    _pauseButtonMenu->setPosition(_pauseButtonPosition);
    addChild(_pauseButtonMenu, zOrderScore);
}

#pragma mark 菜单按钮等基本场景视觉元素
// 切换到暂停画面
void MainScene::pauseGame(CCObject *pSender) {
    ccColor4B c = {0,0,0,0};
//  TODO  GamePause::createWithColor(c, this);
    GamePause::createWithColor(c, NULL);
}

// 初始化box2D
void MainScene::initPhysics() {
    _yAxisGravity = -10;
    
    b2Vec2 gravity;
    gravity.Set(0.0f, _yAxisGravity);
    
    _world = new b2World(gravity);
    
    // Do we wnat to let bodies sleep?
    _world->SetAllowSleeping(true);
    _world->SetContinuousPhysics(true);
//    enableDebugMode();
    
    // 定义地面物体
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0); // bottom-left corner
    
    
    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.调用物体工厂来创建地面物体
    b2Body *groundBody = _world->CreateBody(&groundBodyDef);
    
    // Define the ground box shape. 创建地面盒定义
    b2EdgeShape groundBox;
    
    int worldMaxWith = _screenWidth *4; // Box2D世界的最大宽度
    int worldMaxHeight = _screenHeight *3; // Box2D世界最大的高度
    
    // 底部
    groundBox.Set(b2Vec2(-4, 0), b2Vec2(worldMaxWith/PTM_RATIO, 0));
    groundBody->CreateFixture(&groundBox, 0);
    
    // 顶部
    groundBox.Set(b2Vec2(-4, worldMaxHeight/PTM_RATIO), b2Vec2(worldMaxWith/PTM_RATIO, worldMaxHeight/PTM_RATIO));
    groundBody->CreateFixture(&groundBox, 0);
    
    // 左侧
    groundBox.Set(b2Vec2(-4, worldMaxHeight/PTM_RATIO), b2Vec2(-4,0));
    groundBody->CreateFixture(&groundBox, 0);
    
    // 右侧
    groundBox.Set(b2Vec2(worldMaxWith/PTM_RATIO, worldMaxHeight/PTM_RATIO), b2Vec2(worldMaxWith/PTM_RATIO, worldMaxHeight/PTM_RATIO));
    groundBody->CreateFixture(&groundBox, 0);
}

// 启用碰撞检测
void MainScene::initContactListener() {
    _contactListener = new ContactListener();
    _world->SetContactListener(_contactListener);
}

// 添加地平面物体
void MainScene::addGroundPlaneBody() {
    GroundPlane *theGroundPlane = GroundPlane::createWithWorld(_world, _groundPlaneStartPosition, _groundPlaneFileName->getCString());
    addChild(theGroundPlane, zOrderFloor);
}

// 添加弹弓平台
void MainScene::addFirePlatform() {
    FirePlatform *platform = FirePlatform::createWithWorld(_world, _platformStartPosition, "arts/game_main_scenes/platform.png");
    
    addChild(platform, zOrderPlatform);
}

// 添加熊猫物体
void MainScene::addPanda() {
    // 设置熊猫
    _pandaBeingThrown = 1;  // 从第一个熊猫开始
    
    _panda1 = Panda::createWithWorld(_world, _pandaStartPosition1, "panda");
    addChild(_panda1, zOrderPandas);
    
    _currentBodyNode = _panda1;
    
    if (_pandasToTossThisLevel >= 2) {
        _panda2 = Panda::createWithWorld(_world, _pandaStartPosition2, "pandaYellow");
        addChild(_panda2, zOrderPandas);
    }
    
    if (_pandasToTossThisLevel >= 3) {
        _panda3 = Panda::createWithWorld(_world, _pandaStartPosition3, "pandaBlue");
        addChild(_panda3, zOrderPandas);
    }
    
    if (_pandasToTossThisLevel >= 4) {
        _panda4 = Panda::createWithWorld(_world, _pandaStartPosition4, "pandaGreen");
        addChild(_panda4, zOrderPandas);
    }
}

// 创建遮挡物和外星怪物
void MainScene::addTargets() {
    // 创建遮挡物和外星怪物
    ShootingTargets *targets = ShootingTargets::createWithWorld(_world);
    addChild(targets, zOrderStack);
    
    // 给遮挡物和怪物一定的时间来掉落，然后将其中的每一部分设置为静态 (锁定其位置，直到第一次弹弓发射开始)
    this->runAction(CCSequence::create(CCDelayTime::create(1.0f), CCCallFunc::create(this, callfunc_selector(MainScene::switchAllStackObjectsToStatic)), NULL));
}

// 添加得分和历史最高得分标签
void MainScene::addScoreLabel() {
    _currentScoreLabel = CCLabelTTF::create("", "Marker Felt", (int)_fontSizeForScore);
    addChild(_currentScoreLabel, zOrderPointScore);
    _currentScoreLabel->setColor(ccc3(255, 255, 255));
    _currentScoreLabel->setPosition(_currentScoreLabelPostion);
}

// 更新PointsLabel
void MainScene::updatePointsLabel() {
    // 顶部标签
    CCString *scoreLabel = CCString::createWithFormat("Score: %i", _scoreForCurrentLevel);
    _currentScoreLabel->setString(scoreLabel->getCString());
}

// 增加关卡标签
void MainScene::addLevelIntroLabel() {
    CCString *levelString = CCString::createWithFormat("Level: %i", GameData::sharedData()->getSelectedLevel()->getValue());
    CCLabelTTF *message = CCLabelTTF::create(levelString->getCString(), "Marker Felt", 18);
    addChild(message, 1);
    message->setColor(ccc3(255, 255, 255));
    message->setPosition(ccp(_screenWidth/2, _screenHeight/2));

    CCSequence *seq = CCSequence::create(
                                         CCScaleTo::create(1.0f, 2.0f),
                                         CCFadeTo::create(1.0f, 0.0f),
                                         CCCallFuncN::create(this, callfuncN_selector(MainScene::removeMessage))
                                         , NULL);
    message->runAction(seq);
}

// 删除消息
void MainScene::removeMessage(CCNode *pSender) {
    this->removeChild(pSender);
}

#pragma mark 场景初始化
// 初始化音效和背景音乐
void MainScene::initSounds() {
    if (GameData::sharedData()->getSoundEffectMuted()->getValue() == false) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("audio/birds.mp3");
    }
}

#pragma mark Box2D物理世界相关的方法
// 将ShootingTarget中的物体转换为静态物体
void MainScene::switchAllStackObjectsToStatic() {
    _stackIsNowDynamic = false;
    
    // 遍历物理世界中所有的物体
    for (b2Body* b = _world->GetBodyList(); b; b = b->GetNext()) {
        if (b->GetUserData() != NULL) {
            CCNode *node = (CCNode*)b->GetUserData();
            std::string name = typeid(*node).name();
            if (name.find("StackObject") != std::string::npos) {
//                CCLog("*** %s", typeid(*node).name());
                StackObject *myActor = dynamic_cast<StackObject*>(node);
                myActor->getBody()->SetType(b2_staticBody);
            }
        }
    }
}

// 将shootingTargets中的所有物体转换为动态物体
void MainScene::switchAllStackObjectsToDynamic() {
    if (_stackIsNowDynamic == false) {
        _stackIsNowDynamic = true;
        
        // 遍历世界中所有物体
        for (b2Body* b=_world->GetBodyList(); b; b = b->GetNext()) {
            if (b->GetUserData() != NULL) {
//                StackObject *myActor = (StackObject*)b->GetUserData();
                CCNode *node = (CCNode*)b->GetUserData();
                std::string name = typeid(*node).name();
                if (name.find("StackObject") != std::string::npos) {
                    StackObject *myActor = dynamic_cast<StackObject*>(node);
                    if (myActor->getIsStatic() == false) {
                        myActor->getBody()->SetType(b2_dynamicBody);
                        myActor->getBody()->SetAwake(true);
                    }
                }
            }
        }
    }
}

// 启动调度模式
void MainScene::enableDebugMode() {
    _debugDraw = new GLESDebugDraw(PTM_RATIO);
    _world->SetDebugDraw(_debugDraw);
    
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    //		flags += b2Draw::e_jointBit;
	//		flags += b2Draw::e_aabbBit;
	//		flags += b2Draw::e_pairBit;
	//		flags += b2Draw::e_centerOfMassBit;
    _debugDraw->SetFlags(flags);
}

// 每帧更新世界中的内容
void MainScene::tick(float dt) {
    int32 velocityIterations = 8;
    int32 positionIterations = 1;
    
    //  Instruct the world to perform a single step of simulation. It is generally best to keep the time step and iterations fixed.
    _world->Step(dt, velocityIterations, positionIterations);
    
    // Iterate over the bodies in the physics world
    for (b2Body* b = _world->GetBodyList(); b; b->GetUserData()) {
        if (b->GetUserData() != NULL) {
            // 让Box2d世界中的物体和cocos2d的精灵位置一一对应
            CCSprite *myActor = (CCSprite*)b->GetUserData();
            myActor->setPosition(ccp(b->GetPosition().x *PTM_RATIO, b->GetPosition().y *PTM_RATIO));
            myActor->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
        }
    }
}

# pragma mark 和碰撞检测机制相关的方法
// 切换到下一次抛投
void MainScene::proceedToNextTurn(Panda *thePanda) { // 如果熊猫碰到地面
    if (thePanda == _currentBodyNode) {
        unschedule(schedule_selector(MainScene::timerAfterThrow));
        schedule(schedule_selector(MainScene::moveNextPandaIntoSling), 1.0f);
    } else {
    }
}

// 将下一个熊猫放在弹弓上
void MainScene::moveNextPandaIntoSling(float delta) {
    if (_somethingJustScored == false) { // 在完成得部分前不要移动熊猫
        unschedule(schedule_selector(MainScene::moveNextPandaIntoSling));
        _enemyNumber = GameData::sharedData()->getEnemyNumberForCurrentLevel()->getValue();
        _pandaBeingThrown++;
        
        if (_pandaBeingThrown <= _pandasToTossThisLevel && _scoreForCurrentLevel < _scoreToPassLevel) {
            switch (_pandaBeingThrown) {
                case 2:
                    _currentBodyNode = _panda2;
                case 3:
                    _currentBodyNode = _panda3;
                case 4:
                    _currentBodyNode = _panda4;
            }
            b2Vec2 locationInMeters = b2Vec2(_pandaStartPosition1.x /PTM_RATIO, _pandaStartPosition1.y / PTM_RATIO);
            _currentBodyNode->getBody()->SetTransform(locationInMeters, CC_DEGREES_TO_RADIANS(0));
        } else if (_pandaBeingThrown > _pandasToTossThisLevel || _scoreForCurrentLevel >= _scoreToPassLevel) {
            this->runAction(CCSequence::create(CCDelayTime::create(2.0f),
                                               CCCallFunc::create(this, callfunc_selector(MainScene::showLevelResult)) ,NULL));
        }
    }
}

// 停止添加白色点痕迹
void MainScene::stopDotting() {
    _dottingOn = false;
}

// 显示熊猫碰撞电影票动画
void MainScene::showPandaImpactingStack(Panda *thePanda) {
    if (thePanda == _currentBodyNode) { // 确保currentBodyNode就是和目标发生在同一个熊猫
        // TODO 此处添加其它音效
        // TODO 此外可添加动画或执行其它动作
    }
}

// 熊猫在地面上时所调用的方法
void MainScene::showPandaOnGround(Panda *thePanda) {
    if (thePanda == _currentBodyNode) { // 确保_currentBodyNode就是和地面发生碰撞的熊猫
        schedule(schedule_selector(MainScene::makePandaStaticOnGround), 1.0f/60.0f);
        // TODO 此处可添加其它音效
        // TODO 此处可添加动画或执行其它动作
        _currentBodyNode->runAction(CCSequence::create(CCDelayTime::create(2.0f),
                                                       CCCallFunc::create(this, callfunc_selector(Panda::fadeThenRemove)) ,NULL));
    }
}

// 让熊猫在地面上成为表态物体
void MainScene::makePandaStaticOnGround(float delta) {
    _currentBodyNode->getBody()->SetType(b2_staticBody);
    _currentBodyNode->getBody()->SetTransform(_currentBodyNode->getBody()->GetPosition(), CC_DEGREES_TO_RADIANS(0));
    unschedule(schedule_selector(MainScene::makePandaStaticOnGround));
}

#pragma mark 触摸事件处理
// 开始触摸
void MainScene::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {
    for (CCSetIterator it=pTouches->begin(); it!=pTouches->end(); it++) {
        CCTouch *touch = dynamic_cast<CCTouch*>(*it);
        CCPoint location = touch->getLocationInView();
        location = CCDirector::sharedDirector()->convertToGL(location);
        _previousTouchLocationX = location.x;
        if (_throwInProgress == false) {
            _currentBodyNode->getBody()->SetType(b2_staticBody);
        }
    }
}

// 触摸移动
void MainScene::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {
    if (_autoPanningInProgress == false) {
        cancelAutoPan();
    }
    
    // 触摸交互
    for (CCSetIterator it=pTouches->begin(); it!=pTouches->end(); it++) {
        CCTouch *touch = dynamic_cast<CCTouch*>(*it);
        
        CCPoint location = touch->getLocationInView();
        
        // 移动弹弓中的熊猫。 如果场景在起始位置(self.position.x == 0), 且还未开始抛投，而玩家手指正在弹弓周围触摸
        if ((checkCircleCollision(location, 2.0f, _slingShotCenterPosition, _maxStretchOfSlingShot) == true || _slingShotPandaInHand == true) && _throwInProgress == false && _areWeInTheStartingPostion == true) {
            if (_slingShotPandaInHand == false) {
                _positionInSling = _slingShotCenterPosition;
                _slingShotPandaInHand = true;
                
                _strapBack->setVisible(true);
                _strapFront->setVisible(true);
                _strapEmpty->setVisible(false);
            }
            
            int currentAngle = _currentBodyNode->getBody()->GetAngle();
            b2Vec2 bodyPos = _currentBodyNode->getBody()->GetWorldCenter();
            
            for (CCSetIterator it=pTouches->begin(); it!= pTouches->end();it++) {
                CCTouch *touch = dynamic_cast<CCTouch*>(*it);
                
                CCPoint location = touch->getLocationInView();
                
                float radius = _maxStretchOfSlingShot; // radius of slingShot
                GLfloat  angle = calculateAngle(location.x, location.y, _slingShotCenterPosition.x, _slingShotCenterPosition.y); // 从弹弓中心到触摸位置的角度
                
                // 如果玩家在弹弓的最大拉伸半径范围移动熊猫
                if (checkCircleCollision(location, 2, _slingShotCenterPosition, radius)==true) {
                    _positionInSling = ccp(location.x, location.y);
                    // 根据触摸点和弹弓中心点的位置来判断弹弓皮带的绽放大小
                    float scaleStrap = (abs(_slingShotCenterPosition.x-location.x))/radius;
                    scaleStrap = scaleStrap+0.3; // 添加一点增量
                    if (scaleStrap > 1) { // 判断是否100%的缩放
                        scaleStrap = 1;
                    }
                    
                    _strapFront->setScaleX(scaleStrap);
                    _strapBack->setScaleX(_strapFront->getScaleX()); // 弹弓的后部和前部是相同大小
                } else {
                    // 如果玩家向弹弓的最大拉伸半径范围外移动熊猫
                    GLfloat angleRadians = CC_DEGREES_TO_RADIANS(angle - 90);
                    _positionInSling = ccp(_slingShotCenterPosition.x - (cos(angleRadians)*radius), _slingShotCenterPosition.y + (sin(angleRadians)*radius));
                    _strapFront->setScaleX(1);
                    _strapBack->setScaleY(1);
                    
                    if (_stretchBeyondRange == 0) {
                        // 播放音效
                        if (GameData::sharedData()->getSoundEffectMuted()->getValue() == false) {
                            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("audio/slingshotstretch.mp3");
                        }
                        _stretchBeyondRange++;
                    }
                }
                
                _strapFront->setRotation(angle-90);
                adjustBackStrap(angle);
                
                // 设置熊猫物体的位置
                b2Vec2 locationInMeters = b2Vec2(_positionInSling.x/PTM_RATIO, _positionInSling.y/PTM_RATIO);
                _currentBodyNode->getBody()->SetTransform(locationInMeters, CC_DEGREES_TO_RADIANS(currentAngle));
            }
        } else {    // 如果不满足以上条件则移动屏幕中的场景
            int amountToShiftScreen;
            int diff = (location.x - _previousTouchLocationX); // 起始(上一个)触摸点和当前触摸点的位置差别
            amountToShiftScreen = returnAmountToShiftScreen(diff); // 仅用于放置场景移动过多
            
            // 如果玩家手中没有熊猫，则将屏幕场景前后平移
            if (getPosition().x <=0 && getPosition().x >= _worldMaxToHorizontalShift && _slingShotPandaInHand == false) {
                _areWeInTheStartingPostion = false;
                moveScreen(amountToShiftScreen);
                if (getPosition().x >0) { // 如果场景向左移动过多， 则重新设置起始位置。
                    putEverythingInStartingViewOfSlingShot();
                } else if (getPosition().x < _worldMaxToHorizontalShift) { // 如果场景向相反方向移动过多，则重新设置最大位置
                    putEverythingInViewOfTargets();
                }
            }
        }
        _previousTouchLocationX = location.x;
    }
}

// 触摸结束
void MainScene::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {
    for (CCSetIterator it = pTouches->begin(); it!=pTouches->end();it++) {
        CCTouch *touch = dynamic_cast<CCTouch*>(*it);
        
        CCPoint location = touch->getLocationInView();
        location = CCDirector::sharedDirector()->convertToGL(location);
        
        if (_slingShotPandaInHand == true) { // 熊猫在手中
            // 播放音乐
            if (GameData::sharedData()->getSoundEffectMuted()->getValue() == false) {
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("audio/whoosh.mp3");
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("audio/bird.mp3");
            }
            
            // 将所有障碍物转换为动态物体
            switchAllStackObjectsToDynamic();
            
            _throwCount++;
            _dotCount = 0;
            
            _throwInProgress = true;
            
            _currentBodyNode->getBody()->SetType(b2_dynamicBody);
            _currentBodyNode->getBody()->SetAwake(true);
            
            _strapBack->setVisible(false);
            _strapFront->setVisible(false);
            _strapEmpty->setVisible(true);
            
            // 计算速度
            _speed = (abs(_slingShotCenterPosition.x - _positionInSling.x))+(abs(_slingShotCenterPosition.y-_positionInSling.y));
            _speed = _speed / 5;
            _speed = _speed * _multiplyThrowPower;
            
            // targetPosition即触摸点
//            b2Vec2 targetPosition = b2Vec2(location.x, location.y);
            
            // 判断熊猫的实际运动方向，从弹弓中心到触摸点
            b2Vec2 direction = b2Vec2(_slingShotCenterPosition.x-location.x, _slingShotCenterPosition.y-location.y);
            direction.Normalize();
            
            // 移动物体
            _currentBodyNode->getBody()->SetLinearVelocity(_speed*direction);
            _slingShotPandaInHand = false;
            
            // 添加熊猫的运行轨迹白点
            removePreviousDots();
            _dottingOn = true; // 正在添加白点中
            
            schedule(schedule_selector(MainScene::placeWhiteDots), 1.0f/45.0f); // 根据间隔增加或减少白点的密度
            
            // 确保在6秒后将throwInProgress设置为false
            unschedule(schedule_selector(MainScene::timerAfterThrow));
            schedule(schedule_selector(MainScene::timerAfterThrow), 6.0f);
            
            if (location.x < _slingShotCenterPosition.x) {
                startScreenPanToTargetsWithAutoReverseOn();
            }
        } else if (_continuePanningScreenOnFingerRelease == true) {
            if (_panningTowardSling == true) {
                startScreenPanToSling();
            } else {
                startScreenPanToTargets();
            }
        }
    }
    _stretchBeyondRange = 0;
}

// 判断圆形间的碰撞
bool MainScene::checkCircleCollision(cocos2d::CCPoint center1, float radius1, cocos2d::CCPoint center2, float radius2)
{
    float a = center2.x - center1.x;
    float b = center2.y - center1.y;
    float c = radius1 + radius2;
    float distanceSqrd = (a*a)+(b*b);
    if (distanceSqrd < (c*c))
        return true;
    else
        return false;
}

// 计算角度
GLfloat MainScene::calculateAngle(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
    // DX
    GLfloat x = x2 -x1;
    // DY
    GLfloat y = y2 - y1;
    
    GLfloat angle = 180 + (atan2(-x, -y) * (180/M_PI));
    
    return angle; // degress
}

// 返回平移场景的偏移量
int MainScene::returnAmountToShiftScreen(int diff) {
    int amountToShiftScreen;
    
    if (diff > 50) {
        amountToShiftScreen = 50;
    } else if (diff < -50) {
        amountToShiftScreen = -50;
    } else {
        amountToShiftScreen = diff;
    }
    
    if (_reverseHowFingerPansScreen == false) {
        amountToShiftScreen = amountToShiftScreen * -1;
    }
    
    if (amountToShiftScreen < 0) {
        _panningTowardSling = true;
    } else {
        _panningTowardSling = false;
    }
    
    return amountToShiftScreen;
}

// 删除之前的白点
void MainScene::removePreviousDots() {
    int someNum = 0;
    
    if (_throwCount % 2) { // 返回奇数
        while (someNum <= _dotTotalOnOddNumberedTurn) {
            removeChildByTag(tagForWhiteDotsOddNumberedTurn + someNum, false);
            someNum++;
        }
        _dotTotalOnOddNumberedTurn = 0;
    } else { // 返回偶数
        while (someNum < _dotTotalOnEvenNumberedTurn) {
            removeChildByTag(tagForWhiteDotsEvenNumberedTurn + someNum, false);
            someNum++;
        }
        _dotTotalOnEvenNumberedTurn = 0;
    }
}

// 放置白色点
void MainScene::placeWhiteDots(float delta) {
    if (_dottingOn == true) {
        _dotCount++;
        CCSprite *whiteDot = CCSprite::create("arts/game_main_scenes/circle.png");
        
        if (_throwCount % 2) { // 奇数
            addChild(whiteDot, zOrderWhiteDots, tagForWhiteDotsOddNumberedTurn+_dotCount);
            _dotTotalOnOddNumberedTurn = _dotCount;
        } else { // 偶数
            addChild(whiteDot, zOrderWhiteDots, tagForWhiteDotsEvenNumberedTurn+_dotCount);
            _dotTotalOnEvenNumberedTurn = _dotCount;
        }
        whiteDot->setPosition(ccp(_currentBodyNode->getBody()->GetPosition().x, _currentBodyNode->getBody()->GetPosition().y));
        if (_dotCount % 2) { // 奇数
            whiteDot->setScale(0.5f);
        }
    } else {
        unschedule(schedule_selector(MainScene::placeWhiteDots));
    }
}

// 掷投后的计时器
void MainScene::timerAfterThrow(float delta) {
    // 当熊猫碰到地面时不会调用该方法
    // 但如果熊猫被卡在遮挡物上面而没有击中地面，则调用该方法
    proceedToNextTurn(_currentBodyNode);
    unschedule(schedule_selector(MainScene::timerAfterThrow));
}

#pragma mark 屏幕场景平移
// 启动场景向目标平移
void MainScene::startScreenPanToTargets() {
    _panAmount = _initialPanAmount;
    
    _autoPanningInProgress = true;
    _autoReverseOn = false;
    _panningTowardSling = false;
    
    unschedule(schedule_selector(MainScene::autoScreenPanToSling));
    schedule(schedule_selector(MainScene::autoScreenPanToSling), 1.0f/60.0f);
    
//    if (_areweOnTheIPad == false) {
    unschedule(schedule_selector(MainScene::moveScreenUp));
    schedule(schedule_selector(MainScene::moveScreenDown), 1.0f/60.0f);
//    }
}

// 启用场景向目标平移，此时启用自动转向
void MainScene::startScreenPanToTargetsWithAutoReverseOn() {
    _panAmount = _initialPanAmount;
    
    _autoPanningInProgress = true;
    _autoReverseOn = true;
    _panningTowardSling = false;
    
    unschedule(schedule_selector(MainScene::autoScreenPanToSling));
    schedule(schedule_selector(MainScene::autoScreenPanToTargets), 1.0f/60.0f);
    
//    if (areWeOnIPad == false) {
    unschedule(schedule_selector(MainScene::moveScreenUp));
    schedule(schedule_selector(MainScene::moveScreenDown), 1.0f/60.0f);
//    }
}

// 屏幕场景自动向目标平移
void MainScene::autoScreenPanToTargets(float delta) {
    if (_panAmount > 3) {
        _panAmount = _panAmount - 0.5f;
    }
    
    if (getPosition().x > _worldMaxToHorizontalShift) {
        if (getPosition().x < _worldMaxToHorizontalShift + 50) { // slows down panning when close to finishing
            moveScreen(3);
        } else {
            moveScreen(_panAmount);
        }
    } else {
        unschedule(schedule_selector(MainScene::autoScreenPanToTargets));
        putEverythingInViewOfTargets();
        
        if (_autoReverseOn == true) {
            schedule(schedule_selector(MainScene::startScreenPanToSlingIfScoringIsNotOccuring), 2.0f);
        }
    }
}

// 如果没有得分，则启用屏幕场景向弹弓平移
void MainScene::startScreenPanToSlingIfScoringIsNotOccuring(float delta) {
    if (_somethingJustScored == false) {
        startScreenPanToSling();
        unschedule(schedule_selector(MainScene::startScreenPanToSlingIfScoringIsNotOccuring));
    } else {
    }
}

// 启用屏幕场景向弹弓平移
void MainScene::startScreenPanToSling() {
    _panAmount = _initialPanAmount + _extraAmountOnPanBack;
    
    _autoPanningInProgress = true;
    _panningTowardSling = true;
    
    unschedule(schedule_selector(MainScene::autoScreenPanToTargets));
    schedule(schedule_selector(MainScene::autoScreenPanToSling), 1.0f/60.0f);
    
//    if ( areWeInIPad == false) {
    unschedule(schedule_selector(MainScene::moveScreenDown));
    schedule(schedule_selector(MainScene::moveScreenUp),1.0f/60.0f);
//    }
}

// 场景自动向弹弓平移
void MainScene::autoScreenPanToSling(float delta) {
    if (_panAmount > 3) {
        _panAmount = _panAmount - 0.5f;
    }
    
    if (getPosition().x < 0) {
        if (getPosition().x > -50) { // slows down panning when close to finishing
            moveScreen(-3);
        } else {
            moveScreenDown(_panAmount * -1);
        }
    } else {
        unschedule(schedule_selector(MainScene::autoScreenPanToSling));
        putEverythingInStartingViewOfSlingShot();
        
        _autoPanningInProgress = false;
        setScale(1.0f);
    }
}

// 取消自动平稳
void MainScene::cancelAutoPan() {
    _autoPanningInProgress = false;
    unschedule(schedule_selector(MainScene::autoScreenPanToSling));
    unschedule(schedule_selector(MainScene::autoScreenPanToTargets));
    unschedule(schedule_selector(MainScene::startScreenPanToSlingIfScoringIsNotOccuring));
}

// 按一定增量移动场景
void MainScene::moveScreen(int amountToSiftScreen) {
    setPosition(ccp(getPosition().x - amountToSiftScreen, getPosition().y));
//    if (areWeInIpad) { // 看起来标签保持在原位置，实际上整个层都在移动
//        _pauseButtonMenu->setPosition(ccp(_pauseButtonMenu->getPosition().x + amountToSiftScreen, _pauseButtonMenu->getPosition().y));
//        _currentScoreLabel->setPosition(ccp(_currentScoreLabel->getPosition().x + amountToSiftScreen,
//                                            _currentScoreLabel->getPosition().y));
//    }
    
    // 背景云影和粒子系统移动的视觉效果
    _backgroundLayerHills->setPosition(ccp(_backgroundLayerHills->getPosition().x + (amountToSiftScreen *0.5f), _backgroundLayerHills->getPosition().y));
    _backgroundLayerClouds->setPosition(ccp(_backgroundLayerClouds->getPosition().x + (amountToSiftScreen*0.75), _backgroundLayerClouds->getPosition().y));
    _system->setPosition(ccp(_system->getPosition().x + (amountToSiftScreen*0.75f), _system->getPosition().y));
    
    // 处理缩放
    if (amountToSiftScreen > 0) { // 等比缩小
        if (getScale() > _maxScaleDownValue) {
            setScale(getScale() - _scaleAmount);
        }
    } else { // 等比放大
        if (getScale() < 1) {
            setScale(getScale() + _scaleAmount);
        }
    }
}

// 重置所有场景元素到弹弓起始视角
void MainScene::putEverythingInStartingViewOfSlingShot() {
    setPosition(CCPointZero);
    
    _pauseButtonMenu->setPosition(_pauseButtonPosition);
    
    _system->setPosition(_particleSystemStartPosition);
    _backgroundLayerClouds->setPosition(_cloudLayerStartPosition);
    _backgroundLayerHills->setPosition(_hillsLayerStartPosition);
    
    setScale(1.0f);
    
    _areWeInTheStartingPostion = true;
}

// 将所有场景元素放置到目标视角
void MainScene::putEverythingInViewOfTargets() {
    setPosition(ccp(_worldMaxToHorizontalShift, _adjustY));
    
//    if (areWeInIpad==true) { // 在Ipad中不存在缩放
//        _pauseButtonMenu->setPosition(ccp(_pauseButtonPosition.x - _worldMaxToHorizontalShift, _pauseButtonMenu->getPosition().y));
//        _currentScoreLabel->setPosition(ccp(_currentScoreLabelPostion.x-_worldMaxToHorizontalShift, _currentScoreLabel->getPosition().y));
//    }
    
    _backgroundLayerHills->setPosition(ccp(_hillsLayerStartPosition.x-(_worldMaxToHorizontalShift*0.5f), _backgroundLayerHills->getPosition().y));
    _backgroundLayerClouds->setPosition(ccp(_cloudLayerStartPosition.x-(_worldMaxToHorizontalShift*0.75f),_backgroundLayerClouds->getPosition().y));
    _system->setPosition(ccp(_particleSystemStartPosition.x-(_worldMaxToHorizontalShift*0.75f), _system->getPosition().y));
    
    if (getScale() < _maxScaleDownValue) {
        setScale(_maxScaleDownValue);
    }
    
    _areWeInTheStartingPostion = false;
}

// 让场景上移
void MainScene::moveScreenUp(float delta) {
    if (getPosition().y < 0) {
        setPosition(ccp(getPosition().x, getPosition().y+2));
    } else {
        setPosition(ccp(getPosition().x, 0));
        unschedule(schedule_selector(MainScene::moveScreenUp));
                    
    }
}

// 让场景下移
void MainScene::moveScreenDown(float delta) {
    if (getPosition().y > _adjustY) {
        setPosition(ccp(getPosition().x, getPosition().y-2));
    } else {
        setPosition(ccp(getPosition().x, _adjustY));
        unschedule(schedule_selector(MainScene::moveScreenDown));
    }
}

# pragma mark 游戏分值
// 辅助方法，当有得分时调用
void MainScene::somethingJustScored() {
    _somethingJustScored = true;
    
    unschedule(schedule_selector(MainScene::resetSomethingJustScored));
    schedule(schedule_selector(MainScene::resetSomethingJustScored), 3.0f);
}

// 重置得分后的属性
void MainScene::resetSomethingJustScored(float delta) {
    _somethingJustScored = false;
    unschedule(schedule_selector(MainScene::resetSomethingJustScored));
}

// 显示得分
void MainScene::showPoints(int pointValue, cocos2d::CCPoint positionToShowScore, int theSimpleScore)
{
    _scoreForCurrentLevel = _scoreForCurrentLevel + pointValue;
    somethingJustScored();
    showPointsWithImagesForValue(pointValue, positionToShowScore);
}

// 使用分傎图片来显示得分
void MainScene::showPointsWithImagesForValue(int pointValue, cocos2d::CCPoint positionToShowScore)
{
    CCSprite *scoreLabel;
    
    switch (pointValue) {
        case 100:
            scoreLabel = CCSprite::create("arts/game_main_scenes/100points.png");
            break;
        case 500:
            scoreLabel = CCSprite::create("arts/game_main_scenes/500points.png");
            break;
        case 1000:
            scoreLabel = CCSprite::create("arts/game_main_scenes/1000points.png");
            break;
        case 5000:
            scoreLabel = CCSprite::create("arts/game_main_scenes/5000points.png");
            break;
        case 10000:
            scoreLabel = CCSprite::create("arts/game_main_scenes/10000points.png");
            break;
    }
    
    addChild(scoreLabel, zOrderPointScore);
    scoreLabel->setPosition(positionToShowScore);
    
    CCMoveTo *moveAction = CCMoveTo::create(1.0f, ccp(scoreLabel->getPosition().x, scoreLabel->getPosition().y+25));
    scoreLabel->runAction(moveAction);

    CCSequence *seq = CCSequence::create(CCFadeTo::create(1.5f, 20.2f),
                                         CCCallFuncN::create(this, callfuncN_selector(MainScene::removeThisChild)), NULL);
    scoreLabel->runAction(seq);
}

// 删除子节点
void MainScene::removeThisChild(cocos2d::CCNode *pSender) {
    CCSprite *theSprite = dynamic_cast<CCSprite*>(pSender);
    removeChild(theSprite, true);
}

// 删除标签
void MainScene::removeThisLabel(CCNode *pSender) {
    CCLabelTTF *theLabel = dynamic_cast<CCLabelTTF*>(pSender);
    removeChild(theLabel, true);
}

// 调整弹弓的皮带
void MainScene::adjustBackStrap(float angle) {
    if (angle < 30) {
        _strapBack->setScaleX(_strapBack->getScaleX()*1.0f);
        _strapBack->setRotation(_strapFront->getRotation()*0.8f);
    } else if (angle < 60) {
        _strapBack->setScaleX(_strapBack->getScaleX()*1.05f);
        _strapBack->setRotation(_strapFront->getRotation()*0.8f);
    } else if (angle < 90) {
        _strapBack->setScaleX(_strapBack->getScaleX()*1.1f);
        _strapBack->setRotation(_strapFront->getRotation()*0.85f);
    } else if (angle < 120) {
        _strapBack->setScaleX(_strapBack->getScaleX()*1.2f);
        _strapBack->setRotation(_strapFront->getRotation()*0.95f);
    } else if (angle < 150) {
        _strapBack->setScaleX(_strapBack->getScaleX()*1.2f);
        _strapBack->setRotation(_strapFront->getRotation()*0.9f);
    } else if (angle < 180) {
        _strapBack->setScaleX(_strapBack->getScaleX()*1.1f);
        _strapBack->setRotation(_strapFront->getRotation()*0.85f);
    } else if (angle < 210) {
        _strapBack->setScaleX(_strapBack->getScaleX()*0.95f);
        _strapBack->setRotation(_strapFront->getRotation()*0.85f);
    } else if (angle < 240) {
        _strapBack->setScaleX(_strapBack->getScaleX()*0.7f);
        _strapBack->setRotation(_strapFront->getRotation()*0.85f);
    } else if (angle < 270) {
        _strapBack->setScaleX(_strapBack->getScaleX()*0.6f);
        _strapBack->setRotation(_strapFront->getRotation()*0.9f);
    } else if (angle < 300) {
        _strapBack->setScaleX(_strapBack->getScaleX()*0.5f);
        _strapBack->setRotation(_strapFront->getRotation()*1.0f);
    } else if (angle < 330) {
        _strapBack->setScaleX(_strapBack->getScaleX()*0.6f);
        _strapBack->setRotation(_strapFront->getRotation()*1.1f);
    } else if (angle < 360) {
        _strapBack->setScaleX(_strapBack->getScaleX()*0.6f);
        _strapBack->setRotation(_strapFront->getRotation()*1.1f);
    }
}

#pragma mark 重置游戏或进入下一关
// 为剩下的熊猫获得额外奖励得分
void MainScene::provideBonusForLeftPandas() {
    int pandasLeft = (_pandasToTossThisLevel - _pandaBeingThrown) + 1;
    _bonusThisRound = (_bonusPerLeftPanda * pandasLeft);
    _scoreForCurrentLevel = _scoreForCurrentLevel + _bonusThisRound;
    updatePointsLabel();
}

// 进入显示当前关卡的游戏结束界面
void MainScene::showLevelResult() {
    GameData *data = GameData::sharedData();
    
    if (_scoreForCurrentLevel >= _scoreToPassLevel) {
        _levelClear = true;
        
        provideBonusForLeftPandas();
        
        data->setCurrentLevelScore(CCInteger::create(_scoreForCurrentLevel));
        data->setCurrentLevelToSolved(CCBool::create(true));
        
        GameData::sharedData()->setHighScoreForCurrentLevel(CCInteger::create(_scoreForCurrentLevel)); // 设置最高得分
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("audio/levelwin.mp3");
    } else {
        _levelClear = false;
        GameData::sharedData()->setHighScoreForCurrentLevel(CCInteger::create(_scoreForCurrentLevel)); // 即使未能通关也会设置最高得分
        
        data->setCurrentLevelScore(CCInteger::create(_scoreForCurrentLevel));
        data->setCurrentLevelToSolved(CCBool::create(false));
        
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("audio/levelfailure.mp3");
    }
    
    // 保存关卡的信息
    Levels *selectedLevels = LevelParser::loadLevelsForChapter(data->getSelectedChapter()->getNumber());
    
    // Iterate through the array of levels
    CCObject *obj;
    Level *level;
    CCARRAY_FOREACH(selectedLevels->getLevels(), obj) {
        level = dynamic_cast<Level*>(obj);
        
        // look for currently selected level
        if (level->getNumber() == data->getSelectedLevel()->getValue()) {
            level->setLevelClear(_levelClear);
//            level->setNumber(data->getSelectedLevel()->getValue());
        }
        
        // 如果当前关卡编号为为10,则将下一关解锁
        if (data->getSelectedLevel()->getValue() != 10) {
            if (level->getNumber() == data->getSelectedLevel()->getValue() + 1) {
                if (_levelClear) {
                    level->setUnlocked(true);
                }
            }
        }
    }
    
    // Write the next record
    LevelParser::saveDataForChapter(selectedLevels, data->getSelectedChapter()->getNumber());
    
    this->runAction(CCCallFunc::create(this, callfunc_selector(MainScene::jumpToLevelResultScene)));
}

// 切换到关卡场景
void MainScene::jumpToLevelResultScene() {
    SceneManager::goLevelResult();
}