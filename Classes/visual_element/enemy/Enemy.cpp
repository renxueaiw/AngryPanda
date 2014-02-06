//
//  Enemy.cpp
//  AngryPanda
//
//  Created by renxueaiw on 13-12-21.
//
//

#include "Enemy.h"

USING_NS_CC;

Enemy::~Enemy()
{
    CC_SAFE_RELEASE(_spriteImageName);
    CC_SAFE_RELEASE(_baseImageName);
}

Enemy* Enemy::createWithWorld(b2World *world, cocos2d::CCPoint location, std::string spriteFileName, bool isRotationFixed, bool getDamageFromGround, bool doesGetDamageFromDamageEnabledStackObjects, int breaksFromHowMuchContact, bool hasDifferentSpritesForDamage, int numberOfFramesToAnimateOnBreak, float desity, int createHow, int points, int simpleScoreType)
{
    Enemy *enemy = new Enemy();
    enemy->initWithWorld(world, location, spriteFileName, isRotationFixed, getDamageFromGround, doesGetDamageFromDamageEnabledStackObjects, breaksFromHowMuchContact,hasDifferentSpritesForDamage, numberOfFramesToAnimateOnBreak,desity,createHow,points,simpleScoreType);
    enemy->autorelease();
    return enemy;
}

// 在世界中创建并初始化外星怪物，同时指定多种属性
void Enemy::initWithWorld(b2World *world, cocos2d::CCPoint location, std::string spriteFileName, bool isRotationFixed, bool getDamageFromGround, bool doesGetDamageFromDamageEnabledStackObjects, int breaksFromHowMuchContact, bool hasDifferentSpritesForDamage, int numberOfFramesToAnimateOnBreak, float desity, int createHow, int points, int simpleScoreType)
{
    _world = world;
    _initialLocation = location;
    _baseImageName = CCString::create(spriteFileName);
    _baseImageName->retain();
    _spriteImageName = CCString::createWithFormat("arts/game_main_scenes/%s.png", _baseImageName->getCString());
    _spriteImageName->retain();
    
    _damageFromGroundContact = getDamageFromGround; // 从地面受到伤害
    
    _damageLevel = 0; // 初始化为0,如果breaksAfterHowMuchContact也等于0，则敌人在首次被碰后就会消失
    _breakAfterHowMuchContact = breaksFromHowMuchContact; // 在碰撞几次后分解
    _differentSpriteForDamage = hasDifferentSpritesForDamage; // 如果是true，则会显示受伤害的动画帧
    
    _currentFrame = 0;
    _framesToAnimateOnBreak = numberOfFramesToAnimateOnBreak; // 要分解的动画帧数
    
    _density = desity;
    _shapeCreationMethod = createHow;
    
    _isRotationFixed = isRotationFixed;
    
    _pointValue = points;
    _simpleScore = simpleScoreType;
    
    _damageFromDamageEnabledStackObjects = doesGetDamageFromDamageEnabledStackObjects;
    
    if (_damageLevel == _breakAfterHowMuchContact) {
        _breakOnNextDamage = true;
    } else {
        _breakOnNextDamage = false;
    }
    
    createEnemy();
}

// 创建外星怪的具体方法
void Enemy::createEnemy()
{
    // Define the dynamic body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = _isRotationFixed;
    bodyDef.position.Set(_initialLocation.x/PTM_RATIO, _initialLocation.y/PTM_RATIO);
    
    b2PolygonShape shape;
    b2CircleShape shapeCircle;
    
    if (_shapeCreationMethod == useDiameterOfImageForCicle) {
        CCSprite *tempSprite = CCSprite::create(_spriteImageName->getCString());
        float radiusInMeters = (((tempSprite->getContentSize()).width)/PTM_RATIO) * 0.5f;
     
        shapeCircle.m_radius = radiusInMeters;
    } else if (_shapeCreationMethod == useShapeOfSourceImage) {
        CCSprite *tempSprite = CCSprite::create(_spriteImageName->getCString());

        int num = 4;
        CCSize tempSpriteContentSize = tempSprite->getContentSize();
        b2Vec2 vertices[] = {
            b2Vec2((tempSpriteContentSize.width/-2)/PTM_RATIO, (tempSpriteContentSize.height/2)/PTM_RATIO), // top left corner
            b2Vec2((tempSpriteContentSize.width/-2)/PTM_RATIO, (tempSpriteContentSize.height/-2)/PTM_RATIO), // bottom left corner
            b2Vec2((tempSpriteContentSize.width/2)/PTM_RATIO, (tempSpriteContentSize.height/-2)/PTM_RATIO), // right top corner
            b2Vec2((tempSpriteContentSize.width/2)/PTM_RATIO, (tempSpriteContentSize.height/2)/PTM_RATIO) // right bottom corner
        };
        shape.Set(vertices, num);
    } else if (_shapeCreationMethod == useTriangle) {
        CCSprite *tempSprite = CCSprite::create(_spriteImageName->getCString());
        
        int num = 3;
        CCSize tempSpriteContentSize = tempSprite->getContentSize();
        b2Vec2 verties[] = {
            b2Vec2((tempSpriteContentSize.width/-2)/PTM_RATIO, (tempSpriteContentSize.height/-2)/PTM_RATIO), // bottom left corner
            b2Vec2((tempSpriteContentSize.width/2)/PTM_RATIO, (tempSpriteContentSize.height/2)/PTM_RATIO), // bottom right corner
            b2Vec2(0.0f, (tempSpriteContentSize.height/2)/PTM_RATIO) // top center of image
        };
        shape.Set(verties, num);
    } else if (_shapeCreationMethod == customeCoordinates) { // use own custom coordinates froma program lick Vertex Helper Pro
        
        int num = 4;
        b2Vec2 vertices[] = {
            b2Vec2(-64.0f / PTM_RATIO, 16.0f / PTM_RATIO),
            b2Vec2(-64.0f / PTM_RATIO, -16.0f / PTM_RATIO),
            b2Vec2(64.0f / PTM_RATIO, -16.0f / PTM_RATIO),
            b2Vec2(64.0f / PTM_RATIO, 16.0f / PTM_RATIO)
        };
        shape.Set(vertices, num);
    }
    
    // Define the dynamic body fixtue
    b2FixtureDef fixtureDef;
    if (_shapeCreationMethod == useDiameterOfImageForCicle) {
        fixtureDef.shape = &shapeCircle;
    } else {
        fixtureDef.shape = &shape;
    }
    
    fixtureDef.density = _density;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.1f;
    
    PhysicsNode::createBodyWitSpriteAndFixture(_world, &bodyDef, &fixtureDef, _spriteImageName->getCString());
}

// 外星怪物受到伤害
void Enemy::damageEnemy()
{
    if (_enemyCannotBeDamagedForShortInterval == false) {
        _damageLevel++;
        _enemyCannotBeDamagedForShortInterval = true;
        this->runAction(CCSequence::create(CCDelayTime::create(1.0f), CCCallFunc::create(this, callfunc_selector(Enemy::enemyCanBeDamangeAgain)),NULL));
        
        if (_differentSpriteForDamage == true) {
            PhysicsNode::getSprite()->setTexture(CCSprite::create(CCString::createWithFormat("arts/game_main_scenes/%s_damage%i.png", _baseImageName->getCString(), _damageLevel)->getCString())->getTexture());
        }
        
        if (_damageLevel == _breakAfterHowMuchContact) {
            _breakOnNextDamage = true;
        }
    }
}

// 判断外星怪物是否可再次受到伤害
void Enemy::enemyCanBeDamangeAgain() {
    _enemyCannotBeDamagedForShortInterval = false;
}

// 外星怪物分解
void Enemy::breakEnemy()
{
    this->schedule(schedule_selector(Enemy::startBreakAnimation), 1.0f/30.0f);
}

// 启动分解动画
void Enemy::startBreakAnimation(float delta)
{
    if (_currentFrame == 0) {
        removeBody();
    }
    _currentFrame++; // 当前帧++
    
    if (_currentFrame <= _framesToAnimateOnBreak) { // 如果已提供用于显示分解的动画帧，且当前帧数小于要播放的帧数最大值
        if (_currentFrame < 10) {
            getSprite()->setTexture(CCSprite::create(CCString::createWithFormat("arts/game_main_scenes/%s_break000%i.png", _baseImageName->getCString(), _currentFrame)->getCString())->getTexture());
        } else if (_currentFrame < 100) {
            getSprite()->setTexture(CCSprite::create(CCString::createWithFormat("arts/game_main_scenes/%s_break00%i.png", _baseImageName->getCString(), _currentFrame)->getCString())->getTexture());
        }
    }
    
    if (_currentFrame > _framesToAnimateOnBreak) {
        // 如果_currentFrame和要演示的动画帧数相同，则删除数来
        removeSprite();
        unschedule(schedule_selector(Enemy::startBreakAnimation));
    }
}

// 设置不可获得分数
void Enemy::makeUnScoreable()
{
    _pointValue = 0;
}


#pragma mark getter&&setter
bool Enemy::getDamageFromGroundContact()
{
    return _damageFromGroundContact;
}
void Enemy::setDamageFromGroundContact(bool damageFromGroundContact)
{
    _damageFromGroundContact = damageFromGroundContact;
}

bool Enemy::getDamageFromDamageEnabledStackObjects()
{
    return _damageFromDamageEnabledStackObjects;
}
void Enemy::setDamageFromDamageEnabledStackObjects(bool damageFromDamageEnabledStackObjects)
{
    _damageFromDamageEnabledStackObjects = damageFromDamageEnabledStackObjects;
}

bool Enemy::getBreakOnNextDamage()
{
    return _breakOnNextDamage;
}
void Enemy::setBreakOnNextDamage(bool breakOnNextDamage)
{
    _breakOnNextDamage = breakOnNextDamage;
}

int Enemy::getPointValue()
{
    return _pointValue;
}
void Enemy::setPointValue(int pointValue)
{
    _pointValue = pointValue;
}

int Enemy::getSimpleScore()
{
    return _simpleScore;
}
void Enemy::setSimpleScore(int simpleScore)
{
    _simpleScore = simpleScore;
}

int Enemy::getEnemyLeft()
{
    return _enemyLeft;
}
void Enemy::setEnemyLeft(int enemyLeft)
{
    _enemyLeft = enemyLeft;
}