//
//  ChpaterParser.cpp
//  AngryPanda
//
//  Created by renxueaiw on 13-12-6.
//
//

#include "ChpaterParser.h"
#include "Chapters.h"
#include "Chapter.h"
#include "../../Utilities/LZDBUtils.h"
#include "../../Utilities/sqlite3/sqlite3.h"

USING_NS_CC;

Chapters* ChapterParser::loadData(void)
{
//    CCString *name;
//    int number;
//    bool unlocked;
//    CCString *image;
//    CCString *intro;
    
    Chapters *chapters = Chapters::create();
    
//    CCDictionary* rooDict = CCDictionary::createWithContentsOfFile("datas/Chapters.plist");
//    
//    char key[32];
//    for (int i = 1; i < 6; i++) // 共有5章  1～5
//    {
//        sprintf(key, "Chapter%d", i);
//        
//        CCDictionary *chapterdict = dynamic_cast<CCDictionary*>(rooDict->objectForKey(key));
//        name = dynamic_cast<CCString*>(chapterdict->objectForKey("Name"));
//        number = dynamic_cast<CCString*>(chapterdict->objectForKey("Number"))->intValue();
//        unlocked = dynamic_cast<CCString*>(chapterdict->objectForKey("Unlocked"))->boolValue();
//        image = dynamic_cast<CCString*>(chapterdict->objectForKey("Image"));
//        intro = dynamic_cast<CCString*>(chapterdict->objectForKey("Intro"));
//        
//        Chapter *chapter = Chapter::create();
//        chapter->initWithName(name, number, unlocked, image, intro);
//        chapters->getChapters()->addObject(chapter);
//    }
    // 读取数据库
    int row, col;
    char **result;
    std::string sql = "select * from chapter;";
    LZDBUtils::sharedDBUtils()->queryData(sql, &result, &row, &col);
    CCLog("chapter row: %d, col: %d \n", row, col);
//    for(int i=0;i<(row+1)*col;i++)
//        printf("result[%d]=%s\t",i,result[i]);
    for (int r = 1; r < row+1; r++) {
        int r_end = (r+1)*col;
        Chapter *chapter = Chapter::create();
        for (int ci = r*col+1; ci < r_end; ci++)  {   // ci:current index 当前下标
            int case_index = ci % col;
            
//            CCLog("%d, %s \t", case_index, result[ci]);
            switch (case_index)
            {
                case 1:
                    chapter->setName(CCString::create(result[ci]));
                    break;
                case 2:
                    chapter->setNumber(atoi(result[ci]));
                    break;
                case 3:
                    chapter->setUnlocked(atoi(result[ci]));
                    break;
                case 4:
                    chapter->setImage(CCString::create(result[ci]));
                    break;
                case 5:
                    chapter->setIntro(CCString::create(result[ci]));
                    break;
            }
        }
        chapters->getChapters()->addObject(chapter);
    }
    
    return chapters;
}
