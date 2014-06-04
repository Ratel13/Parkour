#pragma once

#include "cocos2d.h"


class MainLayer : public cocos2d::CCLayer
{
public:

    CREATE_FUNC(MainLayer);
    virtual bool init();
    static cocos2d::CCScene* scene();

private:

    void onPlay(CCObject* pSender);
};

