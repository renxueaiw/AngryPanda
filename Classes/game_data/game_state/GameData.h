//
//  GameData.h
//  AngryPanda
//
//  Created by renxueaiw on 13-11-27.
//
//

#ifndef __AngryPanda__GameData__
#define __AngryPanda__GameData__


#include "cocos2d.h"
#include "../scene_data/Chapter.h"


class GameData: public cocos2d::CCObject{    
private:
    cocos2d::CCUserDefault *_default;
    
    // 当前关卡的评价(非历史最佳万贯，而是此次通关时的评价，历史最佳成绩保存在Levels-Chapter1.xml中)
    cocos2d::CCInteger *_currentLevelstars;
    
    // 当前关卡名称
    cocos2d::CCString *_currentLevelName;
    
    // 当前关卡要抛射的熊猫数据
    cocos2d::CCInteger *_pandasToTossThisLevel;
    cocos2d::CCInteger *_levelsInLevelpack;//第个关卡部分包含多少子关卡
    
    // 当前关卡要抛射的熊猫数据
    cocos2d::CCInteger *_bonusPerPanda;//剩下熊猫所得到的奖励分值
public:
    // 音效相关
    CC_PROPERTY(cocos2d::CCBool*, _soundEffectMuted, SoundEffectMuted);// 音效是否打开 bool soundEffectMuted;
    CC_PROPERTY(cocos2d::CCBool*, _backgroundMusicMuted, BackgroundMusicMuted);// 背景音乐是否打开 bool backgroundMusicMuted;
    
    // 游戏相关
    
    // 是否第一次玩这款游戏
    CC_PROPERTY(cocos2d::CCBool*, _notFirstTimeEnterStore, NotFirstTimeEnterStore);//bool notFirstTimeEnterStore;
    CC_PROPERTY(cocos2d::CCBool*, _notFirstTimePlayThisGame, NotFirstTimePlayThisGame);//bool notFirstTimePlayThisGame;
    
    // 是否暂停游戏
    CC_PROPERTY(cocos2d::CCBool*, _gamePaused, GamePaused);//bool gamePaused;
    
    // 系统默认设置
    //    cocos2d::CCUserDefault *default;
    
    // 关卡相关
    CC_PROPERTY(cocos2d::CCInteger*, _levelsCompleted, LevelsCompleted);//已通过的关卡数据 int levelsCompleted;
    CC_PROPERTY(cocos2d::CCInteger*, _chaptersCompleted, ChaptersCompleted);// 已完成的场景数据 int chapterCompleted;
    CC_PROPERTY(cocos2d::CCBool*, _currentLevelToSolved, CurrentLevelToSolved);// 当前关卡是否已通过 bool currentLevelToSolved;
    
    // 所选场景和关卡
    CC_PROPERTY(Chapter*, _selectedChapter, SelectedChapter);//int _selectedChapter;
    CC_PROPERTY(cocos2d::CCInteger*, _selectedLevel, SelectedLevel);//int _selectedLevel;
    
    // 该游戏专用
    CC_PROPERTY(cocos2d::CCInteger*, _enemyNumberForCurrentLevel, EnemyNumberForCurrentLevel);//int enemyNumberForCurrentLevel;
    
    
    // 当前关卡要抛射的熊猫数据
    CC_PROPERTY(cocos2d::CCInteger*, _scoresToPassLevel;, ScoresToPassLevel);//通过该关卡所需的分数 int scoresToPassLevel;
    
    CC_PROPERTY(cocos2d::CCInteger*, _scoresForAllLevels, ScoresForAllLevels);//所有关卡得分 int scoresForAllLevels;
    
    // 当前关卡
    CC_PROPERTY(cocos2d::CCInteger*, _currentLevel, CurrentLevel);//int currentLevel;
    
    // 当前关卡得分
    CC_PROPERTY(cocos2d::CCInteger*, _currentLevelScore, CurrentLevelScore);//int currentLevelScore;
    
    // 判断设备类型
    CC_PROPERTY(cocos2d::CCBool*, _isAndroid, IsAndroid);// bool isAndroid; 原码是isDeviceIphone5
    
    // 各关卡的历史最高得分
    CC_PROPERTY(cocos2d::CCInteger*, _highScoreLevel1, HighScoreLevel1);
    CC_PROPERTY(cocos2d::CCInteger*, _highScoreLevel2, HighScoreLevel2);
    CC_PROPERTY(cocos2d::CCInteger*, _highScoreLevel3, HighScoreLevel3);
    CC_PROPERTY(cocos2d::CCInteger*, _highScoreLevel4, HighScoreLevel4);
    CC_PROPERTY(cocos2d::CCInteger*, _highScoreLevel5, HighScoreLevel5);
    CC_PROPERTY(cocos2d::CCInteger*, _highScoreLevel6, HighScoreLevel6);
    CC_PROPERTY(cocos2d::CCInteger*, _highScoreLevel7, HighScoreLevel7);
    CC_PROPERTY(cocos2d::CCInteger*, _highScoreLevel8, HighScoreLevel8);
    CC_PROPERTY(cocos2d::CCInteger*, _highScoreLevel9, HighScoreLevel9);
    CC_PROPERTY(cocos2d::CCInteger*, _highScoreLevel10, HighScoreLevel10);
public:
    static GameData* sharedData(void);
    GameData(void);
    virtual ~GameData(void);
    virtual bool init(void);
    
    // 与游戏中的得分相关
//    void sumOfScoresForAllLevels(cocos2d::CCInteger* scoreForCurrentLevel);
    
    // 设置和返回当前关卡的历史最高得分
    int returnHighScoreForCurrentLevel(void);
    void setHighScoreForCurrentLevel(cocos2d::CCInteger* theScore);
    
    // 升级到下一关
//    void levelComplete(void);
};


#endif /* defined(__AngryPanda__GameData__) */
