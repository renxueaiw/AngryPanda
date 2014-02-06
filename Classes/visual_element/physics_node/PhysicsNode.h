//
//  PhysicsNode.h
//  AngryPanda
//
//  Created by renxueaiw on 13-12-19.
//
//

#ifndef __AngryPanda__PhysicsNode__
#define __AngryPanda__PhysicsNode__

/*
 该类直接继承自CCNode类，是CCNode类和b2Body类的拓展，其中的实例方法分别用于使用精灵帧来创建物体，删除物体，删除精灵，淡出并消失，让物体成为静态，删除精灵和物体。
 */
#include "cocos2d.h"
#include "Box2D.h"
#include "../../game_data/game_constants/Constants.h"

class PhysicsNode: public cocos2d::CCNode
{
    CC_PROPERTY(b2Body*, _body, Body);
    CC_PROPERTY(cocos2d::CCSprite*, _sprite, Sprite);
public:
//    CREATE_FUNC(PhysicsNode);
    virtual ~PhysicsNode(void);
//    virtual bool init(void);
    
    // 使用精灵帧图片来创建物体
    void createBodyWitSpriteAndFixture(b2World* world, b2BodyDef* bodyDef, b2FixtureDef* fixtureDef, std::string spriteName);

    void removeBody(void);
    void removeSprite(void);
    void removeSpriteAndbody(CCObject* pSender);
    void fadeThenRemove(void);

    void makeBodyStatic(void);
    void makeBodyDynamic(void);
};
#endif /* defined(__AngryPanda__PhysicsNode__) */
