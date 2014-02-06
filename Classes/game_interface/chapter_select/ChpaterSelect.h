//
//  ChpaterSelect.h
//  AngryPanda
//
//  Created by renxueaiw on 13-12-3.
//
//

#ifndef __AngryPanda__ChpaterSelect__
#define __AngryPanda__ChpaterSelect__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "../../game_data/scene_data/ChpaterParser.h"

class ChapterSelect: public cocos2d::CCLayer, public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate
{
private:
    // 各菜单选项的位置
    cocos2d::CCPoint _backButtonLocation;
    cocos2d::CCPoint _storeButtonLocation;
    
    // 场景文字描述的位置
    cocos2d::CCPoint _textLocation;
    
    // 章节的位置
    cocos2d::CCPoint _chapterLocation;
    
    // 背景图片的位置
    cocos2d::CCPoint _bgLocation;
    
    // 屏幕大小
    cocos2d::CCSize _screenSize;
    
    // 章节集合
    Chapters *_chapters;
    
public:
    static cocos2d::CCScene* scene();
    CREATE_FUNC(ChapterSelect);
    virtual ~ChapterSelect(void);
    virtual bool init(void);
    
    // 获取屏幕大小
    void getScreenSize(void);
    
    // 设置菜单的位置
    void setMenuLocation(void);
    
    // 添加背景图片
    void addBackground(void);
    
    // 播放背景音乐
    void playBackgroundMusic(void);
    
    // 返回起始画面
    void backToStart(cocos2d::CCObject *pSender);
    
    // 添加返回按钮
    void addBackButton(void);
    
    // 添加滚动章节
    void addScrollChapters(void);
    
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {
//        cocos2d::CCLog("scrollViewDidScroll");
    };
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {
//        cocos2d::CCLog("scrollViewDidZoom");
    }
    //单元格点击事件
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    //单元格尺寸设定
    virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    //单元格索引
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    //单元格数量设定
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
};

#endif /* defined(__AngryPanda__ChpaterSelect__) */
