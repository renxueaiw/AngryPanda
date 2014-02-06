//
//  MainScene.h
//  AngryPanda
//
//  Created by renxueaiw on 13-12-24.
//
//

#ifndef __AngryPanda__MainScene__
#define __AngryPanda__MainScene__

/*
 游戏中最为重要的类，它也是游戏的主场景，
 该类是游戏最核心的引擎
 */

#include "cocos2d.h"
#include "Box2D.h"
#include "GLES-Render.h"
#include "../../game_data/game_constants/Constants.h"
#include "../../visual_element/physics_node/PhysicsNode.h"
#include "../../visual_element/panda/Panda.h"

#include "../../game_logic/collection_detection/ContactListener.h"

class MainScene: public cocos2d::CCLayer
{
private:
    int _screenWidth;
    int _screenHeight;
    
    int _currentLevel;
    int _scoreForCurrentLevel;
    int _scoreToPassLevel;
    int _bonusThisRound;
    int _bonusPerLeftPanda;
    
    int _enemyNumber;
    
    unsigned char _fontSizeForScore;
    
    float _panAmount;
    int _initialPanAmount;
    int _extraAmountOnPanBack;
    int _maxStretchOfSlingShot;
    
    bool _stackIsNowDynamic;
//    bool _areWeOnTheIPad;
    bool _useImagesForPointScoreLabels;
    
    bool _somethingJustScored;
    bool _dottingOn;
    bool _areWeInTheStartingPostion;
    bool _slingShotPandaInHand; // 熊猫是否是弹弓中
    bool _throwInProgress; // 是否熊猫正在抛投
    bool _autoPanningInProgress;
    bool _reverseHowFingerPansScreen; // 根据手指向左或向右移动来切换屏幕移动方向
    bool _panningTowardSling;
    bool _continuePanningScreenOnFingerRelease;
    bool _autoReverseOn;
    
    float _multiplyThrowPower;
    
    float _yAxisGravity;
    bool _gravityOn;
    
    b2World* _world;
    cocos2d::extension::GLESDebugDraw *_debugDraw;
    ContactListener *_contactListener;
    
    // 当前被抛投的熊猫角色
    Panda *_currentBodyNode;
    Panda *_panda1;
    
    // 等待被抛投的熊猫角色
    Panda *_panda2;
    Panda *_panda3;
    Panda *_panda4;
    Panda *_panda5;
    
    unsigned char _pandasToTossThisLevel;
    unsigned char _pandaBeingThrown;
    
    // 背景
    cocos2d::CCSprite *_backgroundLayerClouds;
    cocos2d::CCSprite *_backgroundLayerHills;
    
    // 粒子效果
    cocos2d::CCParticleSystem *_system;
    
    // 初始位置
    cocos2d::CCPoint _cloudLayerStartPosition;
    cocos2d::CCPoint _hillsLayerStartPosition;
    cocos2d::CCPoint _particleSystemStartPosition;
    cocos2d::CCPoint _labelStartingPoint;
    
    // 弹弓
    cocos2d::CCSprite *_slingShotFront;
    cocos2d::CCSprite *_strapFront;
    cocos2d::CCSprite *_strapBack;
    cocos2d::CCSprite *_strapEmpty;
    
    // Box2D物体
    cocos2d::CCPoint _groundPlaneStartPosition;
    cocos2d::CCPoint _platformStartPosition;
    cocos2d::CCPoint _pandaStartPosition1;
    cocos2d::CCPoint _pandaStartPosition2;
    cocos2d::CCPoint _pandaStartPosition3;
    cocos2d::CCPoint _pandaStartPosition4;
    cocos2d::CCPoint _pandaStartPosition5;
    
    // 用于移动场景以查看目标
    float _worldMaxToHorizontalShift;
    float _previousTouchLocationX;
    
    float _adjustY;
    float _maxScaleDownValue;
    float _scaleAmount;
    float _speed;
    
    // 标签相关的变量
    cocos2d::CCLabelTTF *_currentScoreLabel;
    cocos2d::CCPoint _currentScoreLabelPostion;
    
    cocos2d::CCPoint _pauseButtonPosition;
    
    cocos2d::CCPoint _slingShotCenterPosition;
    cocos2d::CCPoint _positionInSling;
    
    //  熊猫在空中的白色痕迹
    int _dotCount;
    int _throwCount;
    int _dotTotalOnEvenNumberedTurn;
    int _dotTotalOnOddNumberedTurn;
    
    //  菜单按钮
    cocos2d::CCMenu *_pauseButtonMenu;
    
    // 拉伸弹弓到最大范围的次数
    int _stretchBeyondRange;
    
    // 地面物体
    cocos2d::CCString *_groundPlaneFileName;
    // 当前关卡是否通过
    bool _levelClear;
public:
    static MainScene* sharedMainScene(void);
    static cocos2d::CCScene* scene(void);
    CREATE_FUNC(MainScene);
    virtual bool init(void);
    virtual ~MainScene(void);
    
    void enableDebugMode(void);
    
    // 从GameData读取数据，并设置一些基本的参数
    void readData(void);
    // 设置初始位置
    void setInitialPosition(void);
    // 添加暂停按钮
    void addPauseButton(void);
    void pauseGame(cocos2d::CCObject *pSender);
    // 初始化box2D物理世界
    void initPhysics(void);
    // 启用碰撞检测
    void initContactListener(void);
    // 添加地平面物体
    void addGroundPlaneBody(void);
    // 添加弹弓平台
    void addFirePlatform(void);
    // 添加熊猫物体
    void addPanda(void);
    // 创建遮挡物和外星怪物
    void addTargets(void);
    // 添加得分和历史最高得分标签
    void addScoreLabel(void);
    // 更新PointsLabel
    void updatePointsLabel(void);
    // 增加关卡标签
    void addLevelIntroLabel(void);
    // 初始化音效和背景音乐
    void initSounds(void);
    // 每帧更新新世界中的内容
    void tick(float delta);
    // 抛投后的计时器
    void timerAfterThrow(float delta);
    // 将下一个熊猫放在弹弓上
    void moveNextPandaIntoSling(float delta);
    // 让熊猫在地面上成为表态物体
    void makePandaStaticOnGround(float delta);
    // 判断圆形间的碰撞
//    bool checkCircleCollision(cocos2d::CCPoint center1, float radius1, cocos2d::CCPoint center2, float radius2);
    // 计算角度
    GLfloat calculateAngle(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
    // 放置白色点
    void placeWhiteDots(float delta);
    // 如果没有得分，则启用屏幕场景向弹弓平移
    void startScreenPanToSlingIfScoringIsNotOccuring(float delta);
    // 辅助方法，当有得分时调用
    void somethingJustScored(void);
    // 重置得分后的属性
    void resetSomethingJustScored(float delta);
    // 删除子节点
    void removeThisChild(cocos2d::CCNode *pSender);
    // 删除标签
    void removeThisLabel(cocos2d::CCNode *pSender);
    // 为剩下的熊猫获得额外奖励得分
    void provideBonusForLeftPandas(void);
    
    // 碰撞检测机制将会调用以下方法
    void proceedToNextTurn(Panda *panda);
    void stopDotting(void);
    void showPandaImpactingStack(Panda *panda);
    void showPandaOnGround(Panda *panda);
    
    //
    void removeMessage(cocos2d::CCNode *pSender);
    void removePreviousDots(void);
    void switchAllStackObjectsToStatic(void);
    void switchAllStackObjectsToDynamic(void);
    void showLevelResult(void);
    
    // 触摸事件
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
//    virtual void ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

    
    // 场景移动
    void moveScreen(int amountToSiftScreen);
    void putEverythingInStartingViewOfSlingShot(void);
    void putEverythingInViewOfTargets(void);
    
    void startScreenPanToTargets(void);
    void startScreenPanToTargetsWithAutoReverseOn(void);
    void autoScreenPanToTargets(float delta);
    
    void startScreenPanToSling(void);
    void autoScreenPanToSling(float delta);
    
    void moveScreenUp(float delta);
    void moveScreenDown(float delta);
    
    void cancelAutoPan(void);
    
    // 熊猫在弹弓时的调整
    void adjustBackStrap(float angle);
    int returnAmountToShiftScreen(int diff);
    bool checkCircleCollision(cocos2d::CCPoint center1, float radius1, cocos2d::CCPoint center2, float radius2); // 判断圆形的碰撞
    
    void jumpToLevelResultScene(void);
    
    // 显示游戏分值
    void showPoints(int pointValue, cocos2d::CCPoint positionToShowScore, int theSimpleScore);
    void showPointsWithImagesForValue(int pointValue, cocos2d::CCPoint positionToShowScore);
};


#endif /* defined(__AngryPanda__MainScene__) */
