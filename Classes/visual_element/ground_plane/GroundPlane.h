//
//  GroundPlane.h
//  AngryPanda
//
//  Created by renxueaiw on 13-12-24.
//
//

#ifndef __AngryPanda__GroundPlane__
#define __AngryPanda__GroundPlane__

/*
 用于创建游戏中的地平面物体
 
 和创建其它Box2d物体不同，GroundPlane在创建物体时无需添加.png后缀
 无需在代码中为支持Retina添加-hd，也无需为在代码中为ipad版本添加-ipad
 */

#include "../physics_node/PhysicsNode.h"

class GroundPlane: public PhysicsNode
{
private:
    b2World *_world;
    cocos2d::CCString *_spriteImageName;
    cocos2d::CCPoint _initialLocation;
public:
    virtual ~GroundPlane(void);
    
    static GroundPlane* createWithWorld(b2World *world, cocos2d::CCPoint location, std::string spriteImageName);
    void initWithWorld(b2World *world, cocos2d::CCPoint location, std::string spriteImageName);
    void createGround(void);
};

#endif /* defined(__AngryPanda__GroundPlane__) */
