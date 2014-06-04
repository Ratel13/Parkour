#include "GameOverLayer.h"
#include "PlayScene.h"

using namespace cocos2d;


GameOverLayer* GameOverLayer::create(const ccColor4B& color)
{
    GameOverLayer *pRet = new GameOverLayer();
    pRet->initWithColor(color);
    pRet->autorelease();
    return pRet;
}

bool GameOverLayer::initWithColor(const ccColor4B& color)
{
    if (!CCLayerColor::initWithColor(color))
	{
        return false;
    }

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    CCMenuItemSprite *menuItemRestart = CCMenuItemSprite::create(CCSprite::create("restart_n.png"), CCSprite::create("restart_s.png"),this, menu_selector(GameOverLayer::onRestart));
    CCMenu *menu = CCMenu::create(menuItemRestart, NULL);
    menu->setPosition(ccp(winSize.width*0.5f, winSize.height*0.5f));
    this->addChild(menu);
    
    return true;
}

void GameOverLayer::onRestart(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(PlayLayer::scene());
    CCDirector::sharedDirector()->resume();
}