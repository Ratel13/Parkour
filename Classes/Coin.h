#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "chipmunk.h"


class Coin : public cocos2d::extension::CCPhysicsSprite
{
public:
    static Coin* create(cocos2d::CCSpriteBatchNode *spriteSheet, cpSpace *space, cocos2d::CCPoint position);

    Coin(cocos2d::CCSpriteBatchNode *spriteSheet, cpSpace *space, cocos2d::CCPoint position);

    virtual void removeFromParent();
    
    static const cocos2d::CCSize getCoinContentSize()
	{
        cocos2d::extension::CCPhysicsSprite *sprite = CCPhysicsSprite::createWithSpriteFrameName("coin0.png");
        return sprite->getContentSize();
	}
	
private:
    cpSpace* m_pSpace;

    cpShape* m_pShape;

    cpBody* m_pBody;
};
