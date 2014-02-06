//
//  FirePlatform.cpp
//  AngryPanda
//
//  Created by renxueaiw on 13-12-20.
//
//

#include "FirePlatform.h"

USING_NS_CC;

FirePlatform::~FirePlatform()
{
    CC_SAFE_RELEASE(_spriteImageName);
}

FirePlatform* FirePlatform::createWithWorld(b2World *world, cocos2d::CCPoint location, std::string spriteFileName)
{
    FirePlatform *firePlatform = new FirePlatform();
    firePlatform->initWithWorld(world, location, spriteFileName);
    firePlatform->autorelease();
    return firePlatform;
}

// 使用精灵图片来创建Box2D世界中的平台物体
void FirePlatform::initWithWorld(b2World *world, cocos2d::CCPoint location, std::string spriteFrameName)
{
    _world = world;
    _initialLocation = location;
    _spriteImageName = CCString::create(spriteFrameName);
    _spriteImageName->retain();
    
    createPlatform();
}

// 创建平台物体的具体实现方法
void FirePlatform::createPlatform()
{
    // 创建物体定义
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(_initialLocation.x/PTM_RATIO, _initialLocation.y/PTM_RATIO);
    
    b2PolygonShape shape;
    int num = 4;
    b2Vec2 vertices[] = {
        b2Vec2(-102.0f/PTM_RATIO, -49.5f/PTM_RATIO),
        b2Vec2(-113.0f/PTM_RATIO, -81.5f/PTM_RATIO),
        b2Vec2(113.0f/PTM_RATIO, -84.5f/PTM_RATIO),
        b2Vec2(106.0f/PTM_RATIO,-47.5f/PTM_RATIO)
    };
    shape.Set(vertices, num);
    
    // 创建物体夹具定义
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.1f;
    
    PhysicsNode::createBodyWitSpriteAndFixture(_world, &bodyDef, &fixtureDef, _spriteImageName->getCString());
}
