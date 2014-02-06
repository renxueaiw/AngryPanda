//
//  ShootingTargets.cpp
//  AngryPanda
//
//  Created by renxueaiw on 13-12-23.
//
//

#include "ShootingTargets.h"
#include "../physics_node/PhysicsNode.h"
#include "../stack_object/StackObject.h"
#include "../../game_data/game_constants/Constants.h"
#include "../../game_data/game_state/GameData.h"
#include "../enemy/Enemy.h"

USING_NS_CC;

// 判断设置属于iphone还是ipad
//#define IS_IPHONE (!IS_IPAD)
//#define IS_IPAD (UI_USER_INTEFACE_IDIOM != UIUserInterfceIdiomPhone)

ShootingTargets::~ShootingTargets()
{
    
}

ShootingTargets* ShootingTargets::createWithWorld(b2World *world)
{
    ShootingTargets *shootingTargets = new ShootingTargets();
    shootingTargets->initWithWorld(world);
    shootingTargets->autorelease();
    return shootingTargets;
}

void ShootingTargets::initWithWorld(b2World *world)
{
    _world = world;
    
    // 在Apple设置上配置
//    if (IS_IPAD) {
//        _stackLocationX = 1400;  //整个stack在iPad中x轴上的起始位置
//        _stackLocationY = 100; //整个stack在iPad中y轴上的起始位置
//    } else if(IS_IPHONE){
//        _stackLocationX = 900;  //整个stack在iPhone中x轴上的起始位置
//        _stackLocationY = 35; //整个stack在iPhone中y轴上的起始位置
//    }
    _enemyNumber = 0;
    
    _stackLocationX = 900; // 整个stack在android的x轴上的起始位置
    _stackLocationY = 35; // 整个stack在android的y轴上的起始位置
    
    _currentLevelNumber = GameData::sharedData()->getSelectedLevel()->getValue();
    _currentChapterNumber = GameData::sharedData()->getSelectedChapter()->getNumber();
    
    // 根据大场景和关卡的不同来放置障碍物
    if (_currentChapterNumber == 1) {
        switch (_currentLevelNumber) {
            case 1:
                createChapter1Level1();
                break;
            case 2:
                createChapter1Level2();
                break;
            case 3:
                createChapter1Level3();
                break;
            case 4:
                createChapter1Level4();
                break;
            case 5:
                createChapter1Level5();
                break;
            case 6:
                createChapter1Level6();
                break;
            case 7:
                createChapter1Level7();
                break;
            case 8:
                createChapter1Level8();
                break;
            case 9:
                createChapter1Level9();
                break;
            case 10:
                createChapter1Level10();
                break;
                
            default:
                createChapter1Level1();
                break;
        }
    }  else if (_currentChapterNumber == 2) {
        switch (_currentLevelNumber) {
            case 1:
                createChapter2Level1();
                break;
            case 2:
                createChapter2Level2();
                break;
            case 3:
                createChapter2Level3();
                break;
            case 4:
                createChapter2Level4();
                break;
            case 5:
                createChapter2Level5();
                break;
            case 6:
                createChapter2Level6();
                break;
            case 7:
                createChapter2Level7();
                break;
            case 8:
                createChapter2Level8();
                break;
            case 9:
                createChapter2Level9();
                break;
            case 10:
                createChapter2Level10();
                break;
                
            default:
                createChapter2Level1();
                break;
        }
    } else if (_currentChapterNumber == 3) {
        switch (_currentLevelNumber) {
            case 1:
                createChapter3Level1();
                break;
            case 2:
                createChapter3Level2();
                break;
            case 3:
                createChapter3Level3();
                break;
            case 4:
                createChapter3Level4();
                break;
            case 5:
                createChapter3Level5();
                break;
            case 6:
                createChapter3Level6();
                break;
            case 7:
                createChapter3Level7();
                break;
            case 8:
                createChapter3Level8();
                break;
            case 9:
                createChapter3Level9();
                break;
            case 10:
                createChapter3Level10();
                break;
                
            default:
                createChapter3Level1();
                break;
        }
    } else if (_currentChapterNumber == 4) {
        switch (_currentLevelNumber) {
            case 1:
                createChapter4Level1();
                break;
            case 2:
                createChapter4Level2();
                break;
            case 3:
                createChapter4Level3();
                break;
            case 4:
                createChapter4Level4();
                break;
            case 5:
                createChapter4Level5();
                break;
            case 6:
                createChapter4Level6();
                break;
            case 7:
                createChapter4Level7();
                break;
            case 8:
                createChapter4Level8();
                break;
            case 9:
                createChapter4Level9();
                break;
            case 10:
                createChapter4Level10();
                break;
                
            default:
                createChapter4Level1();
                break;
        }
    } else if (_currentChapterNumber == 5) {
        switch (_currentLevelNumber) {
            case 1:
                createChapter5Level1();
                break;
            case 2:
                createChapter5Level2();
                break;
            case 3:
                createChapter5Level3();
                break;
            case 4:
                createChapter5Level4();
                break;
            case 5:
                createChapter5Level5();
                break;
            case 6:
                createChapter5Level6();
                break;
            case 7:
                createChapter5Level7();
                break;
            case 8:
                createChapter5Level8();
                break;
            case 9:
                createChapter5Level9();
                break;
            case 10:
                createChapter5Level10();
                break;
                
            default:
                createChapter5Level1();
                break;
        }
    }
}

#pragma mark chapter1
void ShootingTargets::createChapter1Level1()
{
    _stackAjustmentX = 0;
    _stackLocationX = _stackLocationX - _stackAjustmentX;
    
    _stackAjustmentY = 0;
    _stackLocationY = _stackLocationY - _stackAjustmentY;
    
    StackObject *object1 = StackObject::createWithWorld(_world, ccp(0+_stackLocationX, 65+_stackLocationY), "woodShape1", false, true, true, false, 0.25f, useShapeOfSourceImage, 90, false, 100, breakEffectSmokePuffs);
    addChild(object1, zOrderStack);
    
    StackObject *object2 = StackObject::createWithWorld(_world, ccp(95+_stackLocationX, 65+_stackLocationY), "woodShape1", false, true, true, false, 0.25f, useShapeOfSourceImage, 90, false, 100, breakEffectSmokePuffs);
    addChild(object2, zOrderStack);
    
    StackObject *object3 = StackObject::createWithWorld(_world, ccp(47+_stackLocationX, 145+_stackLocationY), "woodShape1", false, true, true, false, 0.25f, useShapeOfSourceImage, 0, false, 100, breakEffectSmokePuffs);
    addChild(object3, zOrderStack);
    
    StackObject *object4 = StackObject::createWithWorld(_world, ccp(0+_stackLocationX, 225+_stackLocationY), "woodShape1", false, true, true, false, 0.25f, useShapeOfSourceImage, 90, false, 100, breakEffectSmokePuffs);
    addChild(object4, zOrderStack);
    
    StackObject *object5 = StackObject::createWithWorld(_world, ccp(95+_stackLocationX, 225+_stackLocationY), "woodShape1", false, true, true, false, 0.25f, useShapeOfSourceImage, 90, false, 100, breakEffectSmokePuffs);
    addChild(object5, zOrderStack);
    
    Enemy *enemy1 = Enemy::createWithWorld(_world, ccp(45+_stackLocationX, 200+_stackLocationY), "dragon", true, true, true, 0, true, 10, 1.0f, useShapeOfSourceImage, 10000, breakEffectSmokePuffs);
    addChild(enemy1, zOrderStack);
    
    _enemyNumber++;
    GameData::sharedData()->setEnemyNumberForCurrentLevel(CCInteger::create(_enemyNumber));
}

void ShootingTargets::createChapter1Level2()
{
    
}

void ShootingTargets::createChapter1Level3()
{
    
}

void ShootingTargets::createChapter1Level4()
{
    
}

void ShootingTargets::createChapter1Level5()
{
    
}

void ShootingTargets::createChapter1Level6()
{
    
}

void ShootingTargets::createChapter1Level7()
{
    
}

void ShootingTargets::createChapter1Level8()
{
    
}

void ShootingTargets::createChapter1Level9()
{
    
}

void ShootingTargets::createChapter1Level10()
{
    
}

#pragma mark chapter2
void ShootingTargets::createChapter2Level1()
{
    
}

void ShootingTargets::createChapter2Level2()
{
    
}

void ShootingTargets::createChapter2Level3()
{
    
}

void ShootingTargets::createChapter2Level4()
{
    
}

void ShootingTargets::createChapter2Level5()
{
    
}

void ShootingTargets::createChapter2Level6()
{
    
}

void ShootingTargets::createChapter2Level7()
{
    
}

void ShootingTargets::createChapter2Level8()
{
    
}

void ShootingTargets::createChapter2Level9()
{
    
}

void ShootingTargets::createChapter2Level10()
{
    
}

#pragma mark chapter3
void ShootingTargets::createChapter3Level1()
{
    
}

void ShootingTargets::createChapter3Level2()
{
    
}

void ShootingTargets::createChapter3Level3()
{
    
}

void ShootingTargets::createChapter3Level4()
{
    
}

void ShootingTargets::createChapter3Level5()
{
    
}

void ShootingTargets::createChapter3Level6()
{
    
}

void ShootingTargets::createChapter3Level7()
{
    
}

void ShootingTargets::createChapter3Level8()
{
    
}

void ShootingTargets::createChapter3Level9()
{
    
}

void ShootingTargets::createChapter3Level10()
{
    
}

#pragma mark chapter4
void ShootingTargets::createChapter4Level1()
{
    
}

void ShootingTargets::createChapter4Level2()
{
    
}

void ShootingTargets::createChapter4Level3()
{
    
}

void ShootingTargets::createChapter4Level4()
{
    
}

void ShootingTargets::createChapter4Level5()
{
    
}

void ShootingTargets::createChapter4Level6()
{
    
}

void ShootingTargets::createChapter4Level7()
{
    
}

void ShootingTargets::createChapter4Level8()
{
    
}

void ShootingTargets::createChapter4Level9()
{
    
}

void ShootingTargets::createChapter4Level10()
{
    
}

#pragma mark chapter5
void ShootingTargets::createChapter5Level1()
{
    
}

void ShootingTargets::createChapter5Level2()
{
    
}

void ShootingTargets::createChapter5Level3()
{
    
}

void ShootingTargets::createChapter5Level4()
{
    
}

void ShootingTargets::createChapter5Level5()
{
    
}

void ShootingTargets::createChapter5Level6()
{
    
}

void ShootingTargets::createChapter5Level7()
{
    
}

void ShootingTargets::createChapter5Level8()
{
    
}

void ShootingTargets::createChapter5Level9()
{
    
}

void ShootingTargets::createChapter5Level10()
{
    
}