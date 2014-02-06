//
//  ShootingTargets.h
//  AngryPanda
//
//  Created by renxueaiw on 13-12-23.
//
//

#ifndef __AngryPanda__ShootingTargets__
#define __AngryPanda__ShootingTargets__

/*
 该类将用于在各关卡场景中创建遮挡物和敌人
 游戏中的遮挡物和敌人将使用该类创建
 该类仅次于MainScene的类，因为游戏的关卡设计将在此进行
 */
#include "cocos2d.h"
#include "Box2D.h"

class ShootingTargets: public cocos2d::CCNode
{
private:
    b2World *_world;
    int _currentLevelNumber;
    int _currentChapterNumber;
    
    int _stackLocationX; // stack在x轴上的起始位置
    int _stackLocationY; // stack在y轴上的起始位置
    
    int _stackAjustmentX; // 根据关卡来进行调整
    int _stackAjustmentY; // 根据关卡来进行调整
    
    int _enemyNumber;
public:
    virtual ~ShootingTargets(void);
    
    static ShootingTargets* createWithWorld(b2World *world);
    void initWithWorld(b2World *world);
    
    // 第一章
    void createChapter1Level1(void);
    void createChapter1Level2(void);
    void createChapter1Level3(void);
    void createChapter1Level4(void);
    void createChapter1Level5(void);
    void createChapter1Level6(void);
    void createChapter1Level7(void);
    void createChapter1Level8(void);
    void createChapter1Level9(void);
    void createChapter1Level10(void);
    
    // 第二章
    void createChapter2Level1(void);
    void createChapter2Level2(void);
    void createChapter2Level3(void);
    void createChapter2Level4(void);
    void createChapter2Level5(void);
    void createChapter2Level6(void);
    void createChapter2Level7(void);
    void createChapter2Level8(void);
    void createChapter2Level9(void);
    void createChapter2Level10(void);
    
    // 第三章
    void createChapter3Level1(void);
    void createChapter3Level2(void);
    void createChapter3Level3(void);
    void createChapter3Level4(void);
    void createChapter3Level5(void);
    void createChapter3Level6(void);
    void createChapter3Level7(void);
    void createChapter3Level8(void);
    void createChapter3Level9(void);
    void createChapter3Level10(void);
    
    // 第四章
    void createChapter4Level1(void);
    void createChapter4Level2(void);
    void createChapter4Level3(void);
    void createChapter4Level4(void);
    void createChapter4Level5(void);
    void createChapter4Level6(void);
    void createChapter4Level7(void);
    void createChapter4Level8(void);
    void createChapter4Level9(void);
    void createChapter4Level10(void);
    
    // 第五章
    void createChapter5Level1(void);
    void createChapter5Level2(void);
    void createChapter5Level3(void);
    void createChapter5Level4(void);
    void createChapter5Level5(void);
    void createChapter5Level6(void);
    void createChapter5Level7(void);
    void createChapter5Level8(void);
    void createChapter5Level9(void);
    void createChapter5Level10(void);
};

#endif /* defined(__AngryPanda__ShootingTargets__) */
