//
//  Enemy.h
//  AngryPanda
//
//  Created by renxueaiw on 13-12-21.
//
//

#ifndef __AngryPanda__Enemy__
#define __AngryPanda__Enemy__

/*
 该类将用于创建和管理游戏中的敌人角色
 该类将在ShootingTargets类中创建，它继承自PhysicsNode
 
 在创建时无需添加.png的文件后缀名
 无需在代码中为支持Retina添加-hd，也无需为在代码中为ipad版本添加-ipad
 */
#include "../physics_node/PhysicsNode.h"
#include "../../game_assist/game_audio_manager/GameSounds.h"

class Enemy: public PhysicsNode
{
    CC_PROPERTY(bool, _damageFromGroundContact, DamageFromGroundContact); // 碰到地面是否受伤
    CC_PROPERTY(bool, _damageFromDamageEnabledStackObjects, DamageFromDamageEnabledStackObjects); // 碰到障碍物体是否受伤
    
    CC_PROPERTY(bool, _breakOnNextDamage, BreakOnNextDamage);   // 是否在下次伤害分解
    CC_PROPERTY(int, _pointValue, PointValue);
    CC_PROPERTY(int, _simpleScore, SimpleScore); // 在Constants中定义，当敌人分解时使用何种视觉效果
    CC_PROPERTY(int, _enemyLeft, EnemyLeft);
    
private:
    b2World *_world;
    cocos2d::CCString *_spriteImageName;
    cocos2d::CCString *_baseImageName;
    cocos2d::CCPoint _initialLocation;
    
    int _breakAfterHowMuchContact;   // 如果是0，则在首次接触后将敌人分解
    int _damageLevel;   // 记录已完成伤害程序
    
    float _isRotationFixed; // 如果设置为true，则外星怪物不会旋转
    float _density;
    unsigned char _shapeCreationMethod; // 和所有遮挡物体相同，在Constants.h中检查形状定义
    bool _differentSpriteForDamage; // 怪物是否有受伤害的动画帧数
    
    int _currentFrame;
    int _framesToAnimateOnBreak; // 如果设置为0，则不显示任何分解动画帧
    
    bool _enemyCannotBeDamagedForShortInterval; // 在伤害发生后，外星怪物会获得一定时间的无敌状态
    
    
public:
    virtual ~Enemy(void);
    
    static Enemy* createWithWorld(b2World *world, cocos2d::CCPoint location, std::string spriteFileName, bool isRotationFixed, bool getDamageFromGround, bool doesGetDamageFromDamageEnabledStackObjects, int breaksFromHowMuchContact, bool hasDifferentSpritesForDamage, int numberOfFramesToAnimateOnBreak, float desity, int createHow, int points, int simpleScoreType);
    
    void initWithWorld(b2World *world, cocos2d::CCPoint location, std::string spriteFileName, bool isRotationFixed, bool getDamageFromGround, bool doesGetDamageFromDamageEnabledStackObjects, int breaksFromHowMuchContact, bool hasDifferentSpritesForDamage, int numberOfFramesToAnimateOnBreak, float desity, int createHow, int points, int simpleScoreType);
    
    void createEnemy(void);
    void damageEnemy(void);
    void breakEnemy(void);
    void makeUnScoreable(void); // 设置不可获得分数
    
    // 外星怪物是否可再次受到伤害
    void enemyCanBeDamangeAgain();
    // 启动分解动画
    void startBreakAnimation(float delta);
};

#endif /* defined(__AngryPanda__Enemy__) */
