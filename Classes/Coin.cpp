#include "Coin.h"
#include "Constant.h"

using namespace cocos2d;
using namespace cocos2d::extension;


Coin* Coin::create(CCSpriteBatchNode *spriteSheet, cpSpace *space, CCPoint position)
{
    Coin* coin = new Coin(spriteSheet, space, position);
    coin->autorelease();
    return coin;
}

Coin::Coin(CCSpriteBatchNode *spriteSheet, cpSpace *space, CCPoint position)
{
	this->initWithSpriteFrameName("coin0.png");

	m_pSpace = space;

	// init physics
	float radius = 0.95 * this->getContentSize().width / 2;
	m_pBody = cpBodyNewStatic();
	cpBodySetPos(m_pBody, cpv(position.x, position.y));
	this->setCPBody(m_pBody);

	m_pShape = cpCircleShapeNew(m_pBody, radius, cpvzero);
	m_pShape->collision_type = SpriteTagcoin;
	m_pShape->sensor = true;

	cpSpaceAddStaticShape(m_pSpace, m_pShape);
	// for collision
	cpShapeSetUserData(m_pShape, this);

	//
    CCArray *animFrames = CCArray::create();
    for (int i = 0; i < 8; i++)
    {
        CCString *name = CCString::createWithFormat("coin%d.png",i);
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        animFrames->addObject(frame);
    }
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1);
    CCAction *action =CCRepeatForever::create(CCAnimate::create(animation));
    this->runAction(action);
    spriteSheet->addChild(this);
}

void Coin::removeFromParent()
{
    cpSpaceRemoveStaticShape(this->m_pSpace, this->m_pShape);
    cpShapeFree(this->m_pShape);
    cpBodyFree(this->m_pBody);
    
    CCPhysicsSprite::removeFromParent();
}