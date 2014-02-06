//
//  PhysicsNode.cpp
//  AngryPanda
//
//  Created by renxueaiw on 13-12-19.
//
//

#include "PhysicsNode.h"

USING_NS_CC;

PhysicsNode::~PhysicsNode()
{
    removeBody();
    removeSprite();
}

//bool PhysicsNode::init()
//{
//    if (!CCNode::init())
//        return false;
//    
//    
//    return true;
//}

// 使用精灵帧图片来创建物体
void PhysicsNode::createBodyWitSpriteAndFixture(b2World *world, b2BodyDef *bodyDef, b2FixtureDef *fixtureDef, std::string spriteName)
{
    removeBody(); // remove the body if it already exists
    removeSprite(); // remove the sprite if it aleady exists
    
    _sprite = CCSprite::create(spriteName.c_str());
    _sprite->retain();
    this->addChild(_sprite);
    
    _body = world->CreateBody(bodyDef);
    _body->SetUserData(this);
    
    if (fixtureDef != NULL) {
        _body->CreateFixture(fixtureDef);
    }
}

// 将物体类型设置为静态物体
void PhysicsNode::makeBodyStatic()
{
    _body->SetType(b2_staticBody);
}

// 将物体类型设置为动态物体
void PhysicsNode::makeBodyDynamic()
{
    _body->SetType(b2_dynamicBody);
}

// 执行序列动作，让精灵和物体淡出并消失
void PhysicsNode::fadeThenRemove()
{
    CCSequence *seq = CCSequence::create(CCFadeTo::create(1.0f, 0), CCCallFunc::create(this, callfunc_selector(PhysicsNode::removeSpriteAndbody)), NULL);
    _sprite->runAction(seq);
}

// 从Box2D世界中删除物体
void PhysicsNode::removeBody()
{
    if (_body != NULL) {
        _body->GetWorld()->DestroyBody(_body);
        _body = NULL;
    }
}

// 从Cocos2d中删除精灵
void PhysicsNode::removeSprite()
{
    if (_sprite != NULL) {
        this->removeAllChildrenWithCleanup(true);
        CC_SAFE_RELEASE(_sprite);
        _sprite = NULL;
    }
}

// 删除物体和精灵
void PhysicsNode::removeSpriteAndbody(cocos2d::CCObject *pSender)
{
    removeBody();
    removeSprite();
}

#pragma mark getter&&setter
b2Body* PhysicsNode::getBody()
{
    return _body;
}
void PhysicsNode::setBody(b2Body* body)
{
    if (_body != body) {
        _body = body;
    }
}

CCSprite* PhysicsNode::getSprite()
{
    return _sprite;
}
void PhysicsNode::setSprite(CCSprite* sprite)
{
    if (_sprite != sprite) {
        CC_SAFE_RETAIN(sprite);
        CC_SAFE_RELEASE(_sprite);
        _sprite = sprite;
    }
}