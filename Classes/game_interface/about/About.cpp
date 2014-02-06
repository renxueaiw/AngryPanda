//
//  About.cpp
//  AngryPanda
//
//  Created by renxueaiw on 13-12-2.
//
//

#include "About.h"
//#include "../start/StartGameScene.h"
#include "../../game_assist/game_scene_unify_switch_manager/SceneManager.h"
#include "SimpleAudioEngine.h"
#include "../../game_data/game_state/GameData.h"
#include "../../game_data/game_constants/Constants.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

CCScene* About::scene()
{
    CCScene *scene = CCScene::create();
    About *layer = About::create();
    scene->addChild(layer);
    return scene;
}

About::~About()
{
    
}

// 场景初始化
bool About::init()
{
    if (!CCLayer::init())
        return false;
    
    addBg();
    addBackItem();
    addBgMusic();
    addTextLabel();
//    addShareButton();
    
    addSinaBlogLinkMenu();
    addSinaMicroBlogLinkMenu();
    addMailToMeMenu();
    
    return true;
}

#pragma mark 添加基本视觉元素

// 返回游戏开始界面
void About::backToStart(CCObject *pSender)
{
//    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, StartGameScene::scene()));
    SceneManager::goStartGame();
}

// 添加返回按钮
void About::addBackItem()
{
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    
    CCMenuItem *backButton = CCMenuItemImage::create("arts/generally_buttons/back.png", "arts/generally_buttons/back.png", this, menu_selector(About::backToStart));
    backButton->setPosition(ccp(70, screenSize.height*0.8));
    CCMenu *menu = CCMenu::create(backButton, NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
}

// 添加背景图片
void About::addBg()
{
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite *finalBg = CCSprite::create("arts/about_interfaces/bg_about.png");
    finalBg->setPosition(ccp(screenSize.width/2, screenSize.height/2));
    this->addChild(finalBg);
}

// 添加背景音乐
void About::addBgMusic()
{
    GameData *data = GameData::sharedData();
    if (data->getBackgroundMusicMuted()->getValue() == false) {
        if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying() == false) {
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background_music/bg_startgamescene.mp3", true);
        }
    }
}

// 添加文字标签
void About::addTextLabel()
{
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCLabelTTF *label1 = CCLabelTTF::create("本游戏仅供娱乐,谢谢品玩", "Arial-BoldMT", 16);
    label1->setPosition(ccp(screenSize.width/2, screenSize.height*1.3));
    label1->setScale(0.7f);
    label1->runAction(CCSequence::create(CCMoveTo::create(6.0, ccp(screenSize.width/2, screenSize.height*0.7)), CCScaleTo::create(3.0f, 1.1),NULL));
    this->addChild(label1);
}

// 添加菜单选项，以访问作者的新浪微博链接 (非微博sdk分享)
void About::addSinaMicroBlogLinkMenu()
{
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCMenuItem *microBlogLinkItem = CCMenuItemImage::create("arts/about_interfaces/weibo.png","arts/about_interfaces/weibo.png",this, menu_selector(About::visitMySinaMicroBlog));
    microBlogLinkItem->setPosition(ccp(screenSize.width*0.4, screenSize.height*0.2));
    microBlogLinkItem->runAction(CCScaleTo::create(3.0f, 1.5));
    
    CCMenu *menu = CCMenu::create(microBlogLinkItem, NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
}

// 添加菜单选项，以访问作者的博客链接
void About::addSinaBlogLinkMenu()
{
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCMenuItem *blogLinkItem = CCMenuItemImage::create("arts/about_interfaces/sinablog.png", "arts/about_interfaces/sinablog.png", this, menu_selector(About::visitMySinaBlog));
    blogLinkItem->setPosition(ccp(screenSize.width*0.7,screenSize.height*0.2));
    blogLinkItem->runAction(CCScaleTo::create(3.0f, 1.5f));
    
    CCMenu *menu = CCMenu::create(blogLinkItem, NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
}

// 添加菜单选项，给作者写电子邮件
void About::addMailToMeMenu()
{
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCMenuItem *mailToMeItem = CCMenuItemImage::create("arts/about_interfaces/email.png", "arts/about_interfaces/email.png", this, menu_selector(About::mailToMe));
    mailToMeItem->setPosition(ccp(screenSize.width*0.8,screenSize.height*0.8));
    mailToMeItem->runAction(CCScaleTo::create(3.0f, 1.1f));
    
    CCMenu *menu = CCMenu::create(mailToMeItem, NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
}

#pragma mark 社交网络分享
void About::addShareButton()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // 创建分享按钮
    CCMenuItem *shareButton = CCMenuItemSprite::create(CCSprite::create("arts/about_interfaces/button_share.png"), NULL, this, menu_selector(About::shareButtonTouched));
    shareButton->setPosition(ccp(size.width*0.5,size.height*0.4));
    CCMenu *menu = CCMenu::create(shareButton, NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
    
    CCLabelTTF *shareText = CCLabelTTF::create("分享给好友", "ArialRoundedMTBold", 20);
    shareText->setPosition(ccp(size.width/2, size.height*0.2));
    this->addChild(shareText);
}

void About::shareButtonTouched(CCObject *pSender)
{
    this->runAction(CCSequence::create(CCDelayTime::create(0.5f), CCCallFunc::create(this, callfunc_selector(About::shareToSocialNetwork)), NULL));
}

void About::shareToSocialNetwork()
{
    CCLog("cocos2d 访问 Email");
//    NSURL *url = [NSURL URLWithString:@"mailto://eseedo@gmail.com"];
//    [[UIApplication sharedApplication]openURL:url];
}

// 访问作者的新浪微博链接
void About::visitMySinaMicroBlog(CCObject *pSender)
{
    CCLog("cocos2d-x url访问 microblog");
}

// 访问作者的博客链接
void About::visitMySinaBlog(CCObject *pSender)
{
    CCLog("cocos2d-x url blog");
}

// 给作者写邮件
void About::mailToMe(CCObject *pSender)
{
    CCLog("cocos2d-x email");
}
