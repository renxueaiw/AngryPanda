//
//  LevelParser.h
//  AngryPanda
//
//  Created by renxueaiw on 13-12-9.
//
//

#ifndef __AngryPanda__LevelParser__
#define __AngryPanda__LevelParser__

#include "cocos2d.h"
#include "Levels.h"

class LevelParser: public cocos2d::CCObject
{
protected:
    static cocos2d::CCString* dataFilePath(int chapterNumber);
public:
    static Levels* loadLevelsForChapter(int chapterNumber);
    static void saveDataForChapter(Levels *saveData, int chapterNumber);
};
#endif /* defined(__AngryPanda__LevelParser__) */
