//
//  ChpaterParser.h
//  AngryPanda
//
//  Created by renxueaiw on 13-12-6.
//
//

#ifndef __AngryPanda__ChpaterParser__
#define __AngryPanda__ChpaterParser__

#include "cocos2d.h"
class Chapters;

class ChapterParser: public cocos2d::CCObject
{
public:
//    static cocos2d::CCString* dataFilePath(bool forSave);
    static Chapters* loadData(void);
};

#endif /* defined(__AngryPanda__ChpaterParser__) */
