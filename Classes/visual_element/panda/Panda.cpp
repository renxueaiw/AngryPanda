//
//  Panda.cpp
//  AngryPanda
//
//  Created by renxueaiw on 13-12-19.
//
//

#include "Panda.h"

USING_NS_CC;

Panda::~Panda()
{
    CC_SAFE_RELEASE(_baseImageName);
    CC_SAFE_RELEASE(_spriteImageName);
}

Panda* Panda::createWithWorld(b2World *world, cocos2d::CCPoint p, std::string baseFileName)
{
    Panda *panda = new Panda();
    panda->initWithWorld(world, p, baseFileName);
    panda->autorelease();
    return panda;
}

// 在Box2D世界中创建并初始化熊猫
void Panda::initWithWorld(b2World *world, cocos2d::CCPoint p, std::string baseFileName)
{
    _world = world;
    _initialLocation = p;
    _baseImageName = CCString::create(baseFileName);
    _baseImageName->retain();
    
    this->createPanda();
}

// 创建熊猫物体的具体实现方法
void Panda::createPanda()
{
    _spriteImageName = CCString::createWithFormat("arts/game_main_scenes/%s_standing.png", _baseImageName->getCString());
    _spriteImageName->retain();
    
    _onGround = false;

    // 创建物体定义
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(_initialLocation.x/PTM_RATIO, _initialLocation.y/PTM_RATIO);
    
    b2CircleShape shape;
    float radiusInMeters = (40/PTM_RATIO) * 0.5f;
    shape.m_radius = radiusInMeters;
    
    // 创建物体夹具
    b2FixtureDef fixtureDef;
    fixtureDef.shape= &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 1.0f;
    fixtureDef.restitution = 0.1f;

    PhysicsNode::createBodyWitSpriteAndFixture(_world, &bodyDef, &fixtureDef, _spriteImageName->getCString());
}

#pragma mark getter&&setter
bool Panda::getOnGround()
{
    return _onGround;
}
void Panda::setOnGround(bool onGround)
{
    _onGround = onGround;
}