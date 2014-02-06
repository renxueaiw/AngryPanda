//
//  GameData.cpp
//  AngryPanda
//
//  Created by renxueaiw on 13-11-27.
//
//

#include "GameData.h"

USING_NS_CC;

static GameData *_sharedData = NULL;

GameData* GameData::sharedData(void) {
    
    if (_sharedData == NULL) {
        _sharedData = new GameData();
        _sharedData->init();
    }
    return _sharedData;
}


GameData::GameData(void)
{
}

GameData::~GameData()
{
    CC_SAFE_RELEASE(_levelsCompleted);
    CC_SAFE_RELEASE(_chaptersCompleted);
    
    CC_SAFE_RELEASE(_selectedChapter);
    CC_SAFE_RELEASE(_selectedLevel);
    
    CC_SAFE_RELEASE(_soundEffectMuted);
    CC_SAFE_RELEASE(_backgroundMusicMuted);
    CC_SAFE_RELEASE(_notFirstTimePlayThisGame);
    CC_SAFE_RELEASE(_notFirstTimeEnterStore);
    CC_SAFE_RELEASE(_gamePaused);
    
    CC_SAFE_RELEASE(_highScoreLevel1);
    CC_SAFE_RELEASE(_highScoreLevel2);
    CC_SAFE_RELEASE(_highScoreLevel3);
    CC_SAFE_RELEASE(_highScoreLevel4);
    CC_SAFE_RELEASE(_highScoreLevel5);
    CC_SAFE_RELEASE(_highScoreLevel6);
    CC_SAFE_RELEASE(_highScoreLevel7);
    CC_SAFE_RELEASE(_highScoreLevel8);
    CC_SAFE_RELEASE(_highScoreLevel9);
    CC_SAFE_RELEASE(_highScoreLevel10);
    
    CC_SAFE_RELEASE(_currentLevel);
    CC_SAFE_RELEASE(_currentLevelScore);
    CC_SAFE_RELEASE(_scoresToPassLevel);
    CC_SAFE_RELEASE(_scoresForAllLevels);
    
    CC_SAFE_RELEASE(_currentLevelToSolved);
    CC_SAFE_RELEASE(_enemyNumberForCurrentLevel);
    
    CC_SAFE_RELEASE(_isAndroid);
    
    // 没设置器和访问器的单独变量
    CC_SAFE_RELEASE(_currentLevelstars);
    CC_SAFE_RELEASE(_currentLevelName);
    CC_SAFE_RELEASE(_pandasToTossThisLevel);
    CC_SAFE_RELEASE(_levelsInLevelpack);
    CC_SAFE_RELEASE(_bonusPerPanda);
//    CC_SAFE_RELEASE(_default);
}

bool GameData::init()
{
    bool bRet = false;
    do {
        // 没设置器和访问器的单独变量初始化
        _currentLevelstars = CCInteger::create(0);
        _currentLevelstars->retain();
        _currentLevelName = CCString::create("");
        _currentLevelName->retain();
        _pandasToTossThisLevel = CCInteger::create(0);
        _pandasToTossThisLevel->retain();
        _levelsInLevelpack = CCInteger::create(0);
        _levelsInLevelpack->retain();
        _bonusPerPanda = CCInteger::create(0);
        _bonusPerPanda->retain();
        
        _enemyNumberForCurrentLevel = CCInteger::create(0);
        _enemyNumberForCurrentLevel->retain();
        _scoresToPassLevel = CCInteger::create(0);
        _scoresToPassLevel->retain();
        _scoresForAllLevels = CCInteger::create(0);
        _scoresForAllLevels->retain();
        
        _currentLevel = CCInteger::create(0);
        _currentLevel->retain();
        _currentLevelScore = CCInteger::create(0);
        _currentLevelScore->retain();
        
        _highScoreLevel1 = CCInteger::create(0);
        _highScoreLevel1->retain();
        _highScoreLevel2 = CCInteger::create(0);
        _highScoreLevel2->retain();
        _highScoreLevel3 = CCInteger::create(0);
        _highScoreLevel3->retain();
        _highScoreLevel4 = CCInteger::create(0);
        _highScoreLevel4->retain();
        _highScoreLevel5 = CCInteger::create(0);
        _highScoreLevel5->retain();
        _highScoreLevel6 = CCInteger::create(0);
        _highScoreLevel6->retain();
        _highScoreLevel7 = CCInteger::create(0);
        _highScoreLevel7->retain();
        _highScoreLevel8 = CCInteger::create(0);
        _highScoreLevel8->retain();
        _highScoreLevel9 = CCInteger::create(0);
        _highScoreLevel9->retain();
        _highScoreLevel10 = CCInteger::create(0);
        _highScoreLevel10->retain();
        
        // 读取配置
        _default = CCUserDefault::sharedUserDefault();

        _isAndroid = CCBool::create(_default->getBoolForKey("isAndroid"));
        _isAndroid->retain();
        
        _soundEffectMuted = CCBool::create(_default->getBoolForKey("soundEffectMuted"));
        _soundEffectMuted->retain();
        _backgroundMusicMuted = CCBool::create(_default->getBoolForKey("backgroundMusicMuted"));
        _backgroundMusicMuted->retain();

        
        _gamePaused = CCBool::create(_default->getBoolForKey("gamePaused"));
        _gamePaused->retain();
        
        _notFirstTimePlayThisGame = CCBool::create(_default->getBoolForKey("notFirstTimePlayThisGame"));
        _notFirstTimePlayThisGame->retain();
        _notFirstTimeEnterStore = CCBool::create(_default->getBoolForKey("notFirstTimeEnterStore"));
        _notFirstTimeEnterStore->retain();
       
        _levelsCompleted = CCInteger::create(_default->getIntegerForKey("levelCompletedTotal"));
        _levelsCompleted->retain();
        _chaptersCompleted = CCInteger::create(_default->getIntegerForKey("chaptersCompleted"));
        _chaptersCompleted->retain();
        
        _currentLevelToSolved = CCBool::create(_default->getBoolForKey("currentLevelSolved"));
        _currentLevelToSolved->retain();
        
        // 默认选择的关卡
        _selectedChapter = NULL;
        _selectedLevel = CCInteger::create(1);
        _selectedLevel->retain();
        bRet = true;
    }while (0);
    
    return bRet;
}

//#### 主要逻辑部分

//void GameData::sumOfScoresForAllLevels(cocos2d::CCInteger* scoreForCurrentLevel)
//{
//}


#pragma mark 关卡的历史最高记录

// 返回不同关卡的历史最高得分

int GameData::returnHighScoreForCurrentLevel()
{
    int highScore = 0;
    switch (_selectedLevel->getValue()) {
        case 0:
            highScore = 0;
            break;
        case 1:
            highScore = _highScoreLevel1->getValue();
            break;
        case 2:
            highScore = _highScoreLevel2->getValue();
            break;
        case 3:
            highScore = _highScoreLevel3->getValue();
            break;
        case 4:
            highScore = _highScoreLevel4->getValue();
            break;
        case 5:
            highScore = _highScoreLevel5->getValue();
            break;
        case 6:
            highScore = _highScoreLevel6->getValue();
            break;
        case 7:
            highScore = _highScoreLevel7->getValue();
            break;
        case 8:
            highScore = _highScoreLevel8->getValue();
            break;
        case 9:
            highScore = _highScoreLevel9->getValue();
            break;
        case 10:
            highScore = _highScoreLevel10->getValue();
            break;
            
            
        default:
            highScore = 0;
            break;
    }
    return 0;
}

// 设置不同关卡的历史最高得分
void GameData::setHighScoreForCurrentLevel(cocos2d::CCInteger* theScore)
{
    switch (_selectedLevel->getValue()) {
        case 0:
            // do nothing
            break;
        case 1:
            if (theScore->getValue() > _highScoreLevel1->getValue()) {
                setHighScoreLevel1(theScore);
                _default->setIntegerForKey("highScoreLevel1", theScore->getValue());
            }
            break;
        case 2:
            if (theScore->getValue() > _highScoreLevel2->getValue()) {
                setHighScoreLevel2(theScore);
                _default->setIntegerForKey("highScoreLevel2", theScore->getValue());
            }
            break;
        case 3:
            if (theScore->getValue() > _highScoreLevel3->getValue()) {
                setHighScoreLevel3(theScore);
                _default->setIntegerForKey("highScoreLevel3", theScore->getValue());
            }
            break;
        case 4:
            if (theScore->getValue() > _highScoreLevel4->getValue()) {
                setHighScoreLevel4(theScore);
                _default->setIntegerForKey("highScoreLevel4", theScore->getValue());
            }
            break;
        case 5:
            if (theScore->getValue() > _highScoreLevel5->getValue()) {
                setHighScoreLevel5(theScore);
                _default->setIntegerForKey("highScoreLevel5", theScore->getValue());
            }
            break;
        case 6:
            if (theScore->getValue() > _highScoreLevel6->getValue()) {
                setHighScoreLevel6(theScore);
                _default->setIntegerForKey("highScoreLevel6", theScore->getValue());
            }
            break;
        case 7:
            if (theScore->getValue() > _highScoreLevel7->getValue()) {
                setHighScoreLevel7(theScore);
                _default->setIntegerForKey("highScoreLevel7", theScore->getValue());
            }
            break;
        case 8:
            if (theScore->getValue() > _highScoreLevel8->getValue()) {
                setHighScoreLevel8(theScore);
                _default->setIntegerForKey("highScoreLevel8", theScore->getValue());
            }
            break;
        case 9:
            if (theScore->getValue() > _highScoreLevel9->getValue()) {
                setHighScoreLevel9(theScore);
                _default->setIntegerForKey("highScoreLevel9", theScore->getValue());
            }
            break;
        case 10:
            if (theScore->getValue() > _highScoreLevel10->getValue()) {
                setHighScoreLevel10(theScore);
                _default->setIntegerForKey("highScoreLevel10", theScore->getValue());
            }
            break;
        default:
            break;
    }
}

//void GameData::levelComplete()
//{
//    
//}

//#### 访问器和设置器
CCInteger* GameData::getLevelsCompleted()
{
    return _levelsCompleted;
}
void GameData::setLevelsCompleted(cocos2d::CCInteger* levelsCompleted)
{
    if (_levelsCompleted != levelsCompleted) {
        CC_SAFE_RETAIN(levelsCompleted);
        CC_SAFE_RELEASE(_levelsCompleted);
        _levelsCompleted = levelsCompleted;
    }
}

CCInteger* GameData::getChaptersCompleted()
{
    return _chaptersCompleted;
}
void GameData::setChaptersCompleted(cocos2d::CCInteger* chaptersCompleted)
{
    if (_chaptersCompleted != chaptersCompleted) {
        CC_SAFE_RETAIN(chaptersCompleted);
        CC_SAFE_RELEASE(_chaptersCompleted);
        _chaptersCompleted = chaptersCompleted;
    }
}

Chapter* GameData::getSelectedChapter()
{
    return _selectedChapter;
}
void GameData::setSelectedChapter(Chapter* selectedChapter)
{
    if (_selectedChapter != selectedChapter) {
        CC_SAFE_RETAIN(selectedChapter);
        CC_SAFE_RELEASE(_selectedChapter);
        _selectedChapter = selectedChapter;
    }
}

CCInteger* GameData::getSelectedLevel()
{
    return _selectedLevel;
}
void GameData::setSelectedLevel(cocos2d::CCInteger* selectedLevel)
{
    if (_selectedLevel != selectedLevel) {
        CC_SAFE_RETAIN(selectedLevel);
        CC_SAFE_RELEASE(_selectedLevel);
        _selectedLevel = selectedLevel;
    }
}

CCBool* GameData::getSoundEffectMuted()
{
    return _soundEffectMuted;
}
void GameData::setSoundEffectMuted(cocos2d::CCBool* soundEffectMuted)
{
    if (_soundEffectMuted != soundEffectMuted) {
        CC_SAFE_RETAIN(soundEffectMuted);
        CC_SAFE_RELEASE(_soundEffectMuted);
        _soundEffectMuted = soundEffectMuted;
    }
}

CCBool* GameData::getBackgroundMusicMuted()
{
    return _backgroundMusicMuted;
}
void GameData::setBackgroundMusicMuted(cocos2d::CCBool* backgroundMusicMuted)
{
    if (_backgroundMusicMuted != backgroundMusicMuted) {
        CC_SAFE_RETAIN(backgroundMusicMuted);
        CC_SAFE_RELEASE(_backgroundMusicMuted);
        _backgroundMusicMuted = backgroundMusicMuted;
    }
}

CCBool* GameData::getNotFirstTimePlayThisGame()
{
    return _notFirstTimePlayThisGame;
}
void GameData::setNotFirstTimePlayThisGame(CCBool* notFirstTimePlayThisGame)
{
    if (_notFirstTimePlayThisGame != notFirstTimePlayThisGame) {
        CC_SAFE_RETAIN(notFirstTimePlayThisGame);
        CC_SAFE_RELEASE(_notFirstTimePlayThisGame);
        _notFirstTimePlayThisGame = notFirstTimePlayThisGame;
    }
}

CCBool* GameData::getNotFirstTimeEnterStore()
{
    return _notFirstTimeEnterStore;
}
void GameData::setNotFirstTimeEnterStore(CCBool* notFirstTimeEnterStore)
{
    if (_notFirstTimeEnterStore != notFirstTimeEnterStore) {
        CC_SAFE_RETAIN(notFirstTimeEnterStore);
        CC_SAFE_RELEASE(_notFirstTimeEnterStore);
        _notFirstTimeEnterStore = notFirstTimeEnterStore;
    }
}

CCBool* GameData::getGamePaused()
{
    return _gamePaused;
}
void GameData::setGamePaused(CCBool* gamePaused)
{
    if (_gamePaused != gamePaused) {
        CC_SAFE_RETAIN(gamePaused);
        CC_SAFE_RELEASE(_gamePaused);
        _gamePaused = gamePaused;
    }
}

CCInteger* GameData::getHighScoreLevel1()
{
    return _highScoreLevel1;
}
void GameData::setHighScoreLevel1(CCInteger* highScoreLevel1)
{
    if (_highScoreLevel1 != highScoreLevel1) {
        CC_SAFE_RETAIN(highScoreLevel1);
        CC_SAFE_RELEASE(_highScoreLevel1);
        _highScoreLevel1 = highScoreLevel1;
    }
}

CCInteger* GameData::getHighScoreLevel2()
{
    return _highScoreLevel2;
}
void GameData::setHighScoreLevel2(CCInteger* highScoreLevel2)
{
    if (_highScoreLevel2 != highScoreLevel2) {
        CC_SAFE_RETAIN(highScoreLevel2);
        CC_SAFE_RELEASE(_highScoreLevel2);
        _highScoreLevel2 = highScoreLevel2;
    }
}

CCInteger* GameData::getHighScoreLevel3()
{
    return _highScoreLevel3;
}
void GameData::setHighScoreLevel3(CCInteger* highScoreLevel3)
{
    if (_highScoreLevel3 != highScoreLevel3) {
        CC_SAFE_RETAIN(highScoreLevel3);
        CC_SAFE_RELEASE(_highScoreLevel3);
        _highScoreLevel3 = highScoreLevel3;
    }
}

CCInteger* GameData::getHighScoreLevel4()
{
    return _highScoreLevel4;
}
void GameData::setHighScoreLevel4(CCInteger* highScoreLevel4)
{
    if (_highScoreLevel4 != highScoreLevel4) {
        CC_SAFE_RETAIN(highScoreLevel4);
        CC_SAFE_RELEASE(_highScoreLevel4);
        _highScoreLevel4 = highScoreLevel4;
    }
}

CCInteger* GameData::getHighScoreLevel5()
{
    return _highScoreLevel5;
}
void GameData::setHighScoreLevel5(CCInteger* highScoreLevel5)
{
    if (_highScoreLevel5 != highScoreLevel5) {
        CC_SAFE_RETAIN(highScoreLevel5);
        CC_SAFE_RELEASE(_highScoreLevel5);
        _highScoreLevel5 = highScoreLevel5;
    }
}

CCInteger* GameData::getHighScoreLevel6()
{
    return _highScoreLevel6;
}
void GameData::setHighScoreLevel6(CCInteger* highScoreLevel6)
{
    if (_highScoreLevel6 != highScoreLevel6) {
        CC_SAFE_RETAIN(highScoreLevel6);
        CC_SAFE_RELEASE(_highScoreLevel6);
        _highScoreLevel6 = highScoreLevel6;
    }
}

CCInteger* GameData::getHighScoreLevel7()
{
    return _highScoreLevel7;
}
void GameData::setHighScoreLevel7(CCInteger* highScoreLevel7)
{
    if (_highScoreLevel7 != highScoreLevel7) {
        CC_SAFE_RETAIN(highScoreLevel7);
        CC_SAFE_RELEASE(_highScoreLevel7);
        _highScoreLevel7 = highScoreLevel7;
    }
}

CCInteger* GameData::getHighScoreLevel8()
{
    return _highScoreLevel8;
}
void GameData::setHighScoreLevel8(CCInteger* highScoreLevel8)
{
    if (_highScoreLevel8 != highScoreLevel8) {
        CC_SAFE_RETAIN(highScoreLevel8);
        CC_SAFE_RELEASE(_highScoreLevel8);
        _highScoreLevel8 = highScoreLevel8;
    }
}

CCInteger* GameData::getHighScoreLevel9()
{
    return _highScoreLevel9;
}
void GameData::setHighScoreLevel9(CCInteger* highScoreLevel9)
{
    if (_highScoreLevel9 != highScoreLevel9) {
        CC_SAFE_RETAIN(highScoreLevel9);
        CC_SAFE_RELEASE(_highScoreLevel9);
        _highScoreLevel9 = highScoreLevel9;
    }
}

CCInteger* GameData::getHighScoreLevel10()
{
    return _highScoreLevel10;
}
void GameData::setHighScoreLevel10(CCInteger* highScoreLevel10)
{
    if (_highScoreLevel10 != highScoreLevel10) {
        CC_SAFE_RETAIN(highScoreLevel10);
        CC_SAFE_RELEASE(_highScoreLevel10);
        _highScoreLevel10 = highScoreLevel10;
    }
}

CCInteger* GameData::getCurrentLevel()
{
    return _currentLevel;
}
void GameData::setCurrentLevel(cocos2d::CCInteger* currentLevel)
{
    if (_currentLevel != currentLevel) {
        CC_SAFE_RETAIN(currentLevel);
        CC_SAFE_RELEASE(_currentLevel);
        _currentLevel = currentLevel;
    }
}

CCInteger* GameData::getCurrentLevelScore()
{
    return _currentLevelScore;
}
void GameData::setCurrentLevelScore(cocos2d::CCInteger* currentLevelScore)
{
    if (_currentLevelScore != currentLevelScore) {
        CC_SAFE_RETAIN(currentLevelScore);
        CC_SAFE_RELEASE(_currentLevelScore);
        _currentLevelScore = currentLevelScore;
    }
}

CCInteger* GameData::getScoresToPassLevel()
{
    return _scoresToPassLevel;
}
void GameData::setScoresToPassLevel(CCInteger* scoresToPassLevel) {
    if (_scoresToPassLevel != scoresToPassLevel) {
        CC_SAFE_RETAIN(scoresToPassLevel);
        CC_SAFE_RELEASE(_scoresToPassLevel);
        _scoresToPassLevel = scoresToPassLevel;
    }
}

CCInteger* GameData::getScoresForAllLevels()
{
    return _scoresForAllLevels;
}
void GameData::setScoresForAllLevels(CCInteger* scoresForAllLevels)
{
    if (_scoresForAllLevels != scoresForAllLevels) {
        CC_SAFE_RETAIN(scoresForAllLevels);
        CC_SAFE_RELEASE(_scoresForAllLevels);
        _scoresForAllLevels = scoresForAllLevels;
    }
}

CCBool* GameData::getCurrentLevelToSolved()
{
    return _currentLevelToSolved;
}
void GameData::setCurrentLevelToSolved(CCBool* currentLevelToSolved)
{
    if (_currentLevelToSolved != currentLevelToSolved) {
        CC_SAFE_RETAIN(currentLevelToSolved);
        CC_SAFE_RELEASE(_currentLevelToSolved);
        _currentLevelToSolved = currentLevelToSolved;
    }
}

CCInteger* GameData::getEnemyNumberForCurrentLevel()
{
    return _enemyNumberForCurrentLevel;
}
void GameData::setEnemyNumberForCurrentLevel(CCInteger* enemyNumberForCurrentLevel)
{
    if (_enemyNumberForCurrentLevel != enemyNumberForCurrentLevel) {
        CC_SAFE_RETAIN(enemyNumberForCurrentLevel);
        CC_SAFE_RELEASE(_enemyNumberForCurrentLevel);
        _enemyNumberForCurrentLevel = enemyNumberForCurrentLevel;
    }
}

CCBool* GameData::getIsAndroid()
{
    return _isAndroid;
}
void GameData::setIsAndroid(CCBool* isAndroid)
{
    if (_isAndroid != isAndroid) {
        CC_SAFE_RETAIN(isAndroid);
        CC_SAFE_RELEASE(_isAndroid);
        _isAndroid = isAndroid;
    }
}
