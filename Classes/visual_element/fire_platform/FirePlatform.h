//
//  FirePlatform.h
//  AngryPanda
//
//  Created by renxueaiw on 13-12-20.
//
//

#ifndef __AngryPanda__FirePlatform__
#define __AngryPanda__FirePlatform__

/*
 该类用于创建抛投熊猫所使用的平台物体
 在创建时，需要添加.png的文件后缀名
 无需在代码中为支持Retina添加-hd，也无需为在代码中为ipad版本添加-ipad
 */
#include "../physics_node/PhysicsNode.h"

class FirePlatform: public PhysicsNode
{
private:
    b2World *_world;
    cocos2d::CCString *_spriteImageName;
    cocos2d::CCPoint _initialLocation;
public:
    virtual ~FirePlatform(void);
    static FirePlatform* createWithWorld(b2World *world, cocos2d::CCPoint location, std::string spriteFileName);
    void initWithWorld(b2World *world, cocos2d::CCPoint location, std::string spriteFrameName);
    void createPlatform(void);
};
#endif /* defined(__AngryPanda__FirePlatform__) */
