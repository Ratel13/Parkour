#include "MainScene.h"
#include "PlayScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

CCScene* MainLayer::scene()
{
    CCScene *scene = CCScene::create();
    MainLayer *layer = MainLayer::create();
    scene->addChild(layer);
    return scene;
}

bool MainLayer::init()
{
    if (!CCLayer::init())
	{
        return false;
    }

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    CCSprite *spriteBG = CCSprite::create("MainBG.png");
    spriteBG->setPosition(ccp(winSize.width/2, winSize.height/2));
	float scaleX = winSize.width/spriteBG->getContentSize().width;
	float scaleY = winSize.height/spriteBG->getContentSize().height;
	float scale = (scaleX >= scaleY) ? scaleX : (scaleY);
	spriteBG->setScale(scale);
    this->addChild(spriteBG, 0);
	
	//
    CCMenuItemImage *menuItemPlay = CCMenuItemImage::create("start_n.png", "start_s.png", this, menu_selector(MainLayer::onPlay));
    menuItemPlay->setPosition(ccp(winSize.width/2, winSize.height/2));
    CCMenu* pMenu = CCMenu::create(menuItemPlay, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    //preload music
    CocosDenshion::SimpleAudioEngine *audioEngine = CocosDenshion::SimpleAudioEngine::sharedEngine();
    audioEngine->preloadBackgroundMusic("Sound/background.mp3");
    audioEngine->preloadEffect("Sound/jump.mp3");
    audioEngine->preloadEffect("Sound/crouch.mp3");
	audioEngine->preloadEffect("Sound/pickup_coin.mp3");
	audioEngine->setBackgroundMusicVolume(0.5f);
	audioEngine->setEffectsVolume(0.5f);

    return true;
}

void MainLayer::onPlay(CCObject* pSender)
{
    //CocosDenshion::SimpleAudioEngine *audioEngine = CocosDenshion::SimpleAudioEngine::sharedEngine();
    //audioEngine->playBackgroundMusic("Sound/background.mp3",true);
    CCDirector::sharedDirector()->replaceScene(PlayLayer::scene());
}
