//
//  LevelResult.h
//  AngryPanda
//
//  Created by renxueaiw on 13-12-16.
//
//

#ifndef __AngryPanda__LevelResult__
#define __AngryPanda__LevelResult__

#include "cocos2d.h"

class LevelResult: public cocos2d::CCLayer
{
private:
    // 当前关卡名称
    cocos2d::CCString *_levelName;
    // 当前关卡得分
    int _levelScore;
    // 当前关卡历史最高得分
    int _highScore;
    // 当前关卡是否成功通过
    bool _levelClear;
    // 当前关卡编号
    int _levelNumber;
    // 当前场景编号
    int _chapterNumber;
    
    // 已通过的关卡数量
    int _levelSolved;
    // 背景精灵图片
    cocos2d::CCSprite *_resultBg;
public:
    static cocos2d::CCScene* scene(void);
    CREATE_FUNC(LevelResult);
    virtual bool init(void);
    ~LevelResult(void);
    
    // 读取LevelManager中的数据
    void readData(void);
    // 添加背景并设置透明度
    void addResultBg(void);
    // 显示上面的方框
    void addToBar(void);
    // 显示下面的方框
    void addDownBar(void);
    // 显示关卡名称的历史最高得分
    void addLevelTitle(void);
    // 显示游戏结果
    void addResult(void);
    // 返回关卡选择界面
    void backToLevelSelection(cocos2d::CCObject *pSender);
    // 重玩当前关卡
    void replayCurrentLevel(cocos2d::CCObject *pSender);
    // 进入下一个关卡
    void playNextLevel(cocos2d::CCObject *pSender);
    // 显示三个菜单选项
    void addMenuItems(void);
    // 播放背景音乐
    void playBgMusic(void);
};

#endif /* defined(__AngryPanda__LevelResult__) */
