#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "chipmunk.h"


class Rock : public cocos2d::extension::CCPhysicsSprite
{
public:
    static Rock *create(cocos2d::CCSpriteBatchNode *spriteSheet, cpSpace *space, cocos2d::CCPoint position);

    Rock(cocos2d::CCSpriteBatchNode *spriteSheet, cpSpace *space, cocos2d::CCPoint position);

    virtual void removeFromParent();
    
    static const cocos2d::CCSize getRockContentSize()
    {
        cocos2d::extension::CCPhysicsSprite *sprite = cocos2d::extension::CCPhysicsSprite::createWithSpriteFrameName("rock.png");
        return sprite->getContentSize();
    };

private:
    cpSpace* m_pSpace;
    cpShape* m_pShape;
    cpBody* m_pBody;
};

