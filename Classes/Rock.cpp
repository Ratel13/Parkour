#include "Rock.h"
#include "Map.h"
#include "MapManager.h"
#include "Runner.h"
#include "Constant.h"

using namespace cocos2d;
using namespace cocos2d::extension;


Rock* Rock::create(CCSpriteBatchNode *spriteSheet, cpSpace *space, CCPoint position)
{
    Rock *rock = new Rock(spriteSheet, space, position);
    rock->autorelease();
    return rock;
}

Rock::Rock(CCSpriteBatchNode *spriteSheet, cpSpace *space, CCPoint position)
{
    if ( position.y >= (MapManager::getGroundHeight() + Runner::getCrouchContentSize().height) )
	{
        this->initWithSpriteFrameName("hathpace.png");
    }
	else
	{
        this->initWithSpriteFrameName("rock.png");
    }

    // init physics
	m_pSpace = space;
    m_pBody = cpBodyNewStatic();
    cpBodySetPos(m_pBody, cpv(position.x, position.y));
    this->setCPBody(m_pBody);

	m_pShape = cpBoxShapeNew(m_pBody, this->getContentSize().width, this->getContentSize().height);
	m_pShape->collision_type = SpriteTagrock;
	m_pShape->sensor = true;
    cpSpaceAddStaticShape(m_pSpace, m_pShape);
    //for collision
    cpShapeSetUserData(m_pShape, this);
    
    spriteSheet->addChild(this);
}

void Rock::removeFromParent()
{
    cpSpaceRemoveStaticShape(m_pSpace, m_pShape);  
    cpShapeFree(m_pShape);
    cpBodyFree(m_pBody);
    
    CCPhysicsSprite::removeFromParent();
}