//
//  GroundPlane.cpp
//  AngryPanda
//
//  Created by renxueaiw on 13-12-24.
//
//

#include "GroundPlane.h"

USING_NS_CC;

GroundPlane::~GroundPlane()
{
    CC_SAFE_RELEASE(_spriteImageName);
}

GroundPlane* GroundPlane::createWithWorld(b2World *world, cocos2d::CCPoint location, std::string spriteImageName)
{
    GroundPlane *groundPlane = new GroundPlane();
    groundPlane->initWithWorld(world, location, spriteImageName);
    groundPlane->autorelease();
    return groundPlane;
}

// 在Box2D世界中使用精灵图片创建并初始化地平面
void GroundPlane::initWithWorld(b2World *world, cocos2d::CCPoint location, std::string spriteImageName)
{
    _world = world;
    _initialLocation = location;
    _spriteImageName = CCString::createWithFormat("arts/game_main_scenes/%s.png", spriteImageName.c_str());
    _spriteImageName->retain();
    
    createGround();
}

// 创建地平面物体具体实现方法
void GroundPlane::createGround()
{
    // 创建物体定义
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    
    bodyDef.position.Set(_initialLocation.x/PTM_RATIO, _initialLocation.y/PTM_RATIO);
    
    b2PolygonShape shape;
    
    int num = 4;
    b2Vec2 vertices[] = {
        b2Vec2(-1220.0f / PTM_RATIO, 54.0f / PTM_RATIO),
        b2Vec2(-1220.0f / PTM_RATIO, -52.0f / PTM_RATIO),
        b2Vec2(1019.0f / PTM_RATIO, -52.0f / PTM_RATIO),
        b2Vec2(1019.0f / PTM_RATIO, 54.0f / PTM_RATIO)
    };
    shape.Set(vertices, num);
    
    // 创建物体夹具
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 1.0f;
    fixtureDef.restitution = 0.1f;
    
PhysicsNode:createBodyWitSpriteAndFixture(_world, &bodyDef, &fixtureDef, _spriteImageName->getCString());
}
