#include "StatusLayer.h"

using namespace cocos2d;


bool StatusLayer::init()
{
    if (!CCLayer::init())
	{
        return false;
	}
    
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    m_coins = 0;
	m_labelCoin = CCLabelTTF::create("Coins:0", "Helvetica", 25);
	m_labelCoin->setAnchorPoint(ccp(0, 1));
	m_labelCoin->setPosition(ccp(5, winSize.height-5));
    this->addChild(m_labelCoin);
    
	m_labelMeter = CCLabelTTF::create("0M", "Helvetica", 25);
	m_labelMeter->setAnchorPoint(ccp(0, 1));
	m_labelMeter->setPosition(ccp(5, winSize.height-50));
    this->addChild(m_labelMeter);
    
    return true;
}

void StatusLayer::addCoin(int num)
{
    m_coins += num;
    m_labelCoin->setString(CCString::createWithFormat("Coins:%ld",m_coins)->getCString());
}

void StatusLayer::updateMeter(int px)
{
    m_labelMeter->setString(CCString::createWithFormat("%d:%s", px/10, "M")->getCString());
}