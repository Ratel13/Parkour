#pragma once

#include "cocos2d.h"

class GameOverLayer : public cocos2d::CCLayerColor
{
public:
    static GameOverLayer* create(const cocos2d::ccColor4B& color);

    virtual bool initWithColor(const cocos2d::ccColor4B& color);

private:

    void onRestart(cocos2d::CCObject* pSender);
};

