//
//  About.h
//  AngryPanda
//
//  Created by renxueaiw on 13-12-2.
//
//

#ifndef __AngryPanda__About__
#define __AngryPanda__About__

#include "cocos2d.h"

class About: public cocos2d::CCLayer
{
public:
    static cocos2d::CCScene* scene(void);
    CREATE_FUNC(About);
    virtual ~About(void);
    virtual bool init(void);
    
    // 返回游戏开始界面
    void backToStart(cocos2d::CCObject *pSender);
    // 添加返回按钮
    void addBackItem(void);
    // 添加背景图片
    void addBg(void);
    // 添加背景音乐
    void addBgMusic(void);
    // 添加文字标签
    void addTextLabel(void);
    // 添加到新浪微博的链接
    void visitMySinaMicroBlog(cocos2d::CCObject *pSender);
    // 添加到新浪博客的链接
    void visitMySinaBlog(cocos2d::CCObject *pSender);
    // 添加菜单选项，以访问作者的微博链接
    void addSinaMicroBlogLinkMenu(void);
    // 添加菜单选项，以访问作者的博客链接
    void addSinaBlogLinkMenu(void);
    //添加菜单选择，以给作者写邮件
    void addMailToMeMenu(void);
    // 给作者写邮件
    void mailToMe(cocos2d::CCObject *pSender);
    
    // 添加菜单选项，社交网络分享
    void addShareButton(void);
    // 社交网络分享
    void shareButtonTouched(cocos2d::CCObject *pSender);
    void shareToSocialNetwork(void);
};

#endif /* defined(__AngryPanda__About__) */
