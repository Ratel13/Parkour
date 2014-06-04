#pragma once

#include "cocos2d.h"


class StatusLayer :  public cocos2d::CCLayer
{
public:
	CREATE_FUNC(StatusLayer);

    virtual bool init();

    void addCoin(int num);

    void updateMeter(int px);
   
private:

    cocos2d::CCLabelTTF* m_labelCoin;

    cocos2d::CCLabelTTF* m_labelMeter;

    unsigned long int m_coins;
};

