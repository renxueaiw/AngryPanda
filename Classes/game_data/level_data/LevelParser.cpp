//
//  LevelParser.cpp
//  AngryPanda
//
//  Created by renxueaiw on 13-12-9.
//
//

#include "LevelParser.h"
#include "Levels.h"
#include "Level.h"
#include "../../Utilities/LZDBUtils.h"

USING_NS_CC;

CCString* LevelParser::dataFilePath(int chapterNumber)
{
    CCString *fileName = CCString::createWithFormat("datas/Levels-Chapter%d.plist", chapterNumber);
    return fileName;
}

Levels* LevelParser::loadLevelsForChapter(int chapterNumber)
{
//    CCString *name;
//    int number;
//    bool unlocked;
//    int stars;
//    CCString *data;
//    bool levelClear;
    
    Levels *levels = Levels::create();
    
//    CCDictionary* rootDict = CCDictionary::createWithContentsOfFile(dataFilePath(chapterNumber)->getCString());
//    
//    char key[32];
//    for (int i = 1; i < 11; i++) // 共有10关 1～10
//    {
//        sprintf(key, "Level%d", i);
//        
//        CCDictionary *levelDict = dynamic_cast<CCDictionary*>(rootDict->objectForKey(key));
//        name = dynamic_cast<CCString*>(levelDict->objectForKey("Name"));
//        number = dynamic_cast<CCString*>(levelDict->objectForKey("Number"))->intValue();
//        unlocked = dynamic_cast<CCString*>(levelDict->objectForKey("Unlocked"))->boolValue();
//        stars = dynamic_cast<CCString*>(levelDict->objectForKey("Stars"))->intValue();
//        data = dynamic_cast<CCString*>(levelDict->objectForKey("Data"));
//        levelClear = dynamic_cast<CCString*>(levelDict->objectForKey("LevelClear"))->boolValue();
//        
//        Level *level = Level::create();
//        level->initWithName(name, number, unlocked, stars, data, levelClear);
//        levels->getLevels()->addObject(level);
//    }
    
    // 读取数据库
    int row, col;
    char **result;
//    std::string sql = "select chapter_number, name,number,unlocked,stars,data,level_clear from level where chapter_number="+chapterNumber+";";
    char sql[128];
    sprintf(sql, "select * from level where chapter_number=%d;", chapterNumber);
    
    LZDBUtils::sharedDBUtils()->queryData(sql, &result, &row, &col);
    CCLog("level row: %d, col: %d \n", row, col);
    for (int r = 1; r < row+1; r++) {
        int r_end = (r+1)*col;
        Level *level = Level::create();
        for (int ci = r*col+1; ci < r_end; ci++)  {   // ci:current index 当前下标
            int case_index = ci % col;
            
//            CCLog("%d, %d, %s \t", ci, case_index,result[ci]);
            switch (case_index)
            {
                case 1:
                    level->setChapterNumber(chapterNumber);
                    break;
                case 2:
                    level->setName(CCString::create(result[ci]));
                    break;
                case 3:
                    level->setNumber(atoi(result[ci]));
                    break;
                case 4:
                    level->setUnlocked(atoi(result[ci]));
                    break;
                case 5:
                    level->setStars(atoi(result[ci]));
                    break;
                case 6:
                    level->setData(CCString::create(result[ci]));
                    break;
                case 7:
                    level->setLevelClear(atoi(result[ci]));
                    break;
            }
        }
        levels->getLevels()->addObject(level);
    }

    
    return levels;
}

void LevelParser::saveDataForChapter(Levels *saveData, int chapterNumber)
{
    Level *level;
    CCObject *obj;
    CCARRAY_FOREACH(saveData->getLevels(), obj) {
        level = dynamic_cast<Level*>(obj);
        CCString *sql = CCString::createWithFormat("update level set unlocked=%d, stars=%d,level_clear=%d where chapter_number=%d and number=%d;", level->getUnlocked(), level->getStars(), level->getLevelClear(),chapterNumber, level->getNumber());
        LZDBUtils::sharedDBUtils()->updateData(sql->getCString());
    }
}