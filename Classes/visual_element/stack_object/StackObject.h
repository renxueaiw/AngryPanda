//
//  StackObject.h
//  AngryPanda
//
//  Created by renxueaiw on 13-12-22.
//
//

#ifndef __AngryPanda__StackObject__
#define __AngryPanda__StackObject__

/* 
 该类将用于创建及管理游戏中的遮挡物
 该类在ShootingTargets类中创建，它继承自PhysicsNode
 在创建时，无需添加.png的文件后缀名
 无需在代码中为支持Retina添加-hd，也无需为在代码中为ipad版本添加-ipad
 */

#include "PhysicsNode.h"
#include "../../game_assist/game_audio_manager/GameSounds.h"

class StackObject: public PhysicsNode
{
    CC_PROPERTY(bool, _isStatic, IsStatic); // 是否是静态物体
    CC_PROPERTY(bool, _breakOnGroundContact, BreakOnGroundContact);
    CC_PROPERTY(bool, _canDamageEnemy, CanDamageEnemy);
    
    CC_PROPERTY(int, _pointValue, PointValue);
    CC_PROPERTY(int, _simpleScore, SimpleScore);
private:
    b2World *_world;
    cocos2d::CCString *_spriteImageName;
    cocos2d::CCString *_baseImageName;
    cocos2d::CCPoint _initialLocation;
    
    bool _addedAnimatedBreakFrames;
    bool _breakOnPandaContact;
    float _density;
    unsigned char _shapeCreationMethod;
    
    int _angle;
    
    int _currentFrame;
    int _framesToAnimate;
public:
    virtual ~StackObject(void);
    
    static StackObject* createWithWorld(b2World *world, cocos2d::CCPoint location, std::string spriteFrameName, bool breakOnGround, bool breakFromPanda, bool hasAnimatedBreakFrames, bool damageEnemy, float density, int createHow, int angleChange, bool makeImmovable, int points, int simpleScoreType);
    void initWithWorld(b2World *world, cocos2d::CCPoint location, std::string spriteFrameName, bool breakOnGround, bool breakFromPanda, bool hasAnimatedBreakFrames, bool damageEnemy, float density, int createHow, int angleChange, bool makeImmovable, int points, int simpleScoreType);
    
    void createStackObject(void);
    
    void startBreakAnimation(float delta);
    void playBreakAnimationFromGroundContact(void);
    void playBreakAnimationFromPandaContact(void);
    void makeUnScoreable(void);
    
    
};



#endif /* defined(__AngryPanda__StackObject__) */
