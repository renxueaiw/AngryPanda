//
//  LoadingScreen.h
//  AngryPanda
//
//  Created by renxueaiw on 13-12-23.
//
//

#ifndef __AngryPanda__LoadingScreen__
#define __AngryPanda__LoadingScreen__

#include "cocos2d.h"

class LoadingScreen: public cocos2d::CCLayer
{
private:
    cocos2d::CCSize _winSize;
    cocos2d::CCPoint _winCenter;
    
    cocos2d::CCProgressTimer *_progress;
    float _progressInterval;
    int _assetCount;
public:
    static cocos2d::CCScene* scene(void);
    CREATE_FUNC(LoadingScreen);
    virtual bool init(void);
    virtual ~LoadingScreen(void);
    
    virtual void onEnterTransitionDidFinish();
    
    void loadMusic(cocos2d::CCArray *musicFiles);
    void loadSounds(cocos2d::CCArray *soundClips);
    // there are any sprite sheets to load
    void loadSpriteSheets(cocos2d::CCArray *spriteSheets);
    // Images can be cache of background or any else.
    void loadImages(cocos2d::CCArray *images);
    // Assets basically are anything not of the the above.
    void loadAssets(cocos2d::CCArray *assets);
    // updates the progress bar with the next step
    void progressUpdate(void);
    // Called by progressUpdate when all assets are loaded from the manifest.
    void loadingComplete(void);
    void toStartGameScene(void);
};

#endif /* defined(__AngryPanda__LoadingScreen__) */
