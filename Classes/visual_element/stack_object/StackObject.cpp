//
//  StackObject.cpp
//  AngryPanda
//
//  Created by renxueaiw on 13-12-22.
//
//

#include "StackObject.h"

USING_NS_CC;

StackObject::~StackObject()
{
    CC_SAFE_RELEASE(_spriteImageName);
    CC_SAFE_RELEASE(_baseImageName);
}

StackObject* StackObject::createWithWorld(b2World *world, cocos2d::CCPoint location, std::string spriteFrameName, bool breakOnGround, bool breakFromPanda, bool hasAnimatedBreakFrames, bool damageEnemy, float density, int createHow, int angleChange, bool makeImmovable, int points, int simpleScoreType) {
    StackObject *stackObject = new StackObject();
    stackObject->initWithWorld(world, location, spriteFrameName, breakOnGround, breakFromPanda, hasAnimatedBreakFrames, damageEnemy, density, createHow, angleChange, makeImmovable, points, simpleScoreType);
    stackObject->autorelease();
    return stackObject;
}

// 创建并初始化遮挡物， 并设置相关属性
void StackObject::initWithWorld(b2World *world, cocos2d::CCPoint location, std::string spriteFrameName, bool breakOnGround, bool breakFromPanda, bool hasAnimatedBreakFrames, bool damageEnemy, float density, int createHow, int angleChange, bool makeImmovable, int points, int simpleScoreType)
{
    _world = world;
    _initialLocation = location;
    _baseImageName = CCString::create(spriteFrameName.c_str());
    _baseImageName->retain();
    _spriteImageName = CCString::createWithFormat("arts/game_main_scenes/%s.png", _baseImageName->getCString());
    _spriteImageName->retain();
    
    _breakOnGroundContact = breakOnGround;
    _breakOnPandaContact = breakFromPanda;
    _addedAnimatedBreakFrames = hasAnimatedBreakFrames;
    _canDamageEnemy = damageEnemy;
    _density = density;
    _shapeCreationMethod = createHow;
    _angle = angleChange;
    _isStatic = makeImmovable;
    
    _currentFrame = 0;
    _framesToAnimate =  10;
    
    _pointValue = points;
    _simpleScore = simpleScoreType;
    
    createStackObject();
}

// 创建物体的具体实现方法
void StackObject::createStackObject()
{
    // 创建物体定义
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.position.Set(_initialLocation.x/PTM_RATIO, _initialLocation.y/PTM_RATIO);
    
    b2PolygonShape shape;
    b2CircleShape shapeCircle;
    
    // 根据不同的形状类型来设置物体形状
    if (_shapeCreationMethod == useDiameterOfImageForCicle) {
        CCSprite *tempSprite = CCSprite::create(_spriteImageName->getCString());
        float radiusInMeters = tempSprite->getContentSize().width/PTM_RATIO*0.5f;
        
        shapeCircle.m_radius = radiusInMeters;
    } else if (_shapeCreationMethod == useShapeOfSourceImage) {
        CCSprite *tempSprite = CCSprite::create(_spriteImageName->getCString());

        int num = 4;
        CCSize tempSpriteContentSize = tempSprite->getContentSize();
        b2Vec2 vertices[] = {
            b2Vec2((tempSpriteContentSize.width/-2)/PTM_RATIO, (tempSpriteContentSize.height/2)/PTM_RATIO),
            b2Vec2((tempSpriteContentSize.width/-2)/PTM_RATIO, (tempSpriteContentSize.height/-2)/PTM_RATIO),
            b2Vec2((tempSpriteContentSize.width/2)/PTM_RATIO, (tempSpriteContentSize.height/-2)/PTM_RATIO),
            b2Vec2((tempSpriteContentSize.width/2)/PTM_RATIO, (tempSpriteContentSize.height/2)/PTM_RATIO)
        };
        shape.Set(vertices, num);
    } else if (_shapeCreationMethod == useTriangle) {
        CCSprite *tempSprite = CCSprite::create(_spriteImageName->getCString());
        
        int num = 3;
        CCSize tempSpriteContentSize = tempSprite->getContentSize();
        b2Vec2 vertices[] = {
            b2Vec2((tempSpriteContentSize.width/-2)/PTM_RATIO, (tempSpriteContentSize.height/-2)/PTM_RATIO),
            b2Vec2((tempSpriteContentSize.width/2)/PTM_RATIO, (tempSpriteContentSize.height/-2)/PTM_RATIO),
            b2Vec2(0.0f, (tempSpriteContentSize.height/2)/PTM_RATIO)
        };
        shape.Set(vertices, num);
    } else if (_shapeCreationMethod == customeCoordinates) { //可以使用类似Vertex Helper Pro等软件来创建定制的顶点坐标
        int num = 4;
        b2Vec2 vertices[] = {
            b2Vec2(-64.0f / PTM_RATIO, 16.0f / PTM_RATIO),
            b2Vec2(-64.0f / PTM_RATIO, -16.0f / PTM_RATIO),
            b2Vec2(64.0f / PTM_RATIO, -16.0f / PTM_RATIO),
            b2Vec2(64.0f / PTM_RATIO, 16.0f / PTM_RATIO)
        };
        shape.Set(vertices, num);
    }
    
    // 创建物体夹具定义
    b2FixtureDef fixtureDef;
    if (_shapeCreationMethod == useDiameterOfImageForCicle) {
        fixtureDef.shape = &shapeCircle;
    } else {
        fixtureDef.shape = &shape;
    }
    
    fixtureDef.density = _density;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.1f;
    
    PhysicsNode::createBodyWitSpriteAndFixture(_world, &bodydef, &fixtureDef, _spriteImageName->getCString());
    
    if (_angle != 0) {
        int currentAngle = getBody()->GetAngle();
        b2Vec2 locationInMeters = getBody()->GetPosition();
        getBody()->SetTransform(locationInMeters, CC_DEGREES_TO_RADIANS(currentAngle+_angle));
    }
    
    if (_isStatic == true) {
        makeBodyStatic();
    }
}

// 当遮挡物碰撞熊猫时播放动画
void StackObject::playBreakAnimationFromPandaContact()
{
    if (_breakOnPandaContact) {
        schedule(schedule_selector(StackObject::startBreakAnimation), 1.0f/30.f);
    }
}

// 当遮挡物碰撞地面时播放动画
void StackObject::playBreakAnimationFromGroundContact()
{
    if (_breakOnGroundContact) {
        schedule(schedule_selector(StackObject::startBreakAnimation), 1.0f/30.0f);
    }
}

// 启动分解动画
void StackObject::startBreakAnimation(float delta)
{
    if (_currentFrame == 0) {
        removeBody();
    }
    _currentFrame++; // 当前帧++
    
    if (_currentFrame <= _framesToAnimate && _addedAnimatedBreakFrames == true) { // 如果提供了分解动画帧，且当前帧小于最大帧数
        if (_currentFrame < 10) {
            getSprite()->setTexture(CCSprite::create(CCString::createWithFormat("arts/game_main_scenes/%s_000%i.png", _baseImageName->getCString(), _currentFrame)->getCString())->getTexture());
        } else if (_currentFrame < 100) {
            getSprite()->setTexture(CCSprite::create(CCString::createWithFormat("arts/game_main_scenes/%s_00%i.png", _baseImageName->getCString(), _currentFrame)->getCString())->getTexture());
        }
    }
    
    if (_currentFrame > _framesToAnimate || _addedAnimatedBreakFrames == false) {
        removeSprite();
        unschedule(schedule_selector(StackObject::startBreakAnimation));
    }
}

// 设置碰到遮挡物时不会得分
void StackObject::makeUnScoreable()
{
    _pointValue = 0;
}


#pragma mark getter&&setter
bool StackObject::getIsStatic()
{
    return _isStatic;
}
void StackObject::setIsStatic(bool isStatic)
{
    _isStatic = isStatic;
}

bool StackObject::getBreakOnGroundContact()
{
    return _breakOnGroundContact;
}
void StackObject::setBreakOnGroundContact(bool breakOnGroundContact)
{
    _breakOnGroundContact = breakOnGroundContact;
}

bool StackObject::getCanDamageEnemy()
{
    return _canDamageEnemy;
}
void StackObject::setCanDamageEnemy(bool canDamangeEnemy)
{
    _canDamageEnemy = canDamangeEnemy;
}

int StackObject::getPointValue()
{
    return _pointValue;
}
void StackObject::setPointValue(int pointValue)
{
    _pointValue = pointValue;
}

int StackObject::getSimpleScore()
{
    return _simpleScore;
}
void StackObject::setSimpleScore(int simpleScore)
{
    _simpleScore = simpleScore;
}
