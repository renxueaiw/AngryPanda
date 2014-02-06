//
//  Panda.h
//  AngryPanda
//
//  Created by renxueaiw on 13-12-19.
//
//

#ifndef __AngryPanda__Panda__
#define __AngryPanda__Panda__

/*
 该类用于创建和管理游戏中的熊猫角色 (玩家控制角色)
 该类将在ShootingTargets类中创建，它继承自PhysicsNode,其中所定义的几个实例方法分别用于在Box2D中创建熊猫
 在创建时，无需添加.png文件后缀名
 无需在代码中为支持Retina添加-hd，也无需为在代码中为ipad版本添加-ipad
 */
#include "../physics_node/PhysicsNode.h"

class Panda: public PhysicsNode
{
    CC_PROPERTY(bool, _onGround, OnGround);
private:
    b2World* _world;
    cocos2d::CCString *_baseImageName;
    cocos2d::CCString *_spriteImageName;
    cocos2d::CCPoint _initialLocation;
    
//    bool _onGround;
    unsigned char _counter;
    
public:
    virtual ~Panda(void);
    
    static Panda* createWithWorld(b2World *world, cocos2d::CCPoint p, std::string baseFileName);
    void initWithWorld(b2World *world, cocos2d::CCPoint p, std::string baseFileName);
    void createPanda();
    
};

#endif /* defined(__AngryPanda__Panda__) */
