#include "ObjectManager.h"
#include "MapManager.h"
#include "Runner.h"
#include "Coin.h"
#include "Rock.h"

using namespace cocos2d;
using namespace cocos2d::extension;


ObjectManager::ObjectManager(CCSpriteBatchNode* spriteSheet, cpSpace* space)
{
	m_pSpace = space;    
	m_pSpriteSheet = spriteSheet;
}

ObjectManager::~ObjectManager()
{
    std::list<CCSprite *>::iterator itList;
    for (itList = m_objects.begin(); itList != m_objects.end(); itList++)
	{
        CCSprite *sprite = (CCSprite *)*itList;
        sprite->removeFromParent();
    }
}

void ObjectManager::initObjectOfMap(int mapIndex, float mapWidth)
{
    int initCoinNum = 7;
	float jumpRockHeight = Runner::getCrouchContentSize().height + MapManager::getGroundHeight();
	float coinHeight = Coin::getCoinContentSize().height + MapManager::getGroundHeight();
    
	//random the center point of 7 coins.
	int randomCoinFactor = CCRANDOM_0_1()*(CCRANDOM_0_1()*2 + 1);
	int randomRockFactor = CCRANDOM_0_1()*(CCRANDOM_0_1()*2 + 1);

	float jumpRockFactor = 0;
    
	float coinPoint_x = mapWidth/4*randomCoinFactor + mapWidth*mapIndex;
	float RockPoint_x = mapWidth/4*randomRockFactor + mapWidth*mapIndex;
    
	float coinWidth = Coin::getCoinContentSize().width;
	float rockWith = Rock::getRockContentSize().width;
	float rockHeight =  Rock::getRockContentSize().height;
    
	float startx = coinPoint_x - coinWidth/2*11;
	float xIncrement = coinWidth/2*3;
	//add a rock
    Rock *rock = Rock::create(m_pSpriteSheet, m_pSpace, ccp(RockPoint_x, MapManager::getGroundHeight() + rockHeight/2));
    rock->setTag(mapIndex);
    m_objects.push_back(rock);
	if(mapIndex == 0 && randomCoinFactor==1)
	{
		randomCoinFactor = 2;
	}

	//add coins
	for(int i = 0; i < initCoinNum; i++)
	{
        Coin *coin = NULL;
		if((startx + i*xIncrement > RockPoint_x-rockWith/2)
           &&(startx + i*xIncrement < RockPoint_x+rockWith/2))
		{
            coin = Coin::create(this->m_pSpriteSheet, this->m_pSpace, ccp(startx + i*xIncrement, coinHeight+rockHeight));
		}
		else
		{
            coin = Coin::create(this->m_pSpriteSheet, this->m_pSpace, ccp(startx + i*xIncrement, coinHeight));
		}
        coin->setTag(mapIndex);
        m_objects.push_back(coin);
	}
    
	for(int i=1;i<4;i++)
	{
		if((i!=randomCoinFactor) && (i!=randomRockFactor))
		{
			jumpRockFactor = i;
		}
	}

	float JumpRockPoint_x = mapWidth/4 * jumpRockFactor + mapWidth*mapIndex;
    Rock *jumpRock = Rock::create(m_pSpriteSheet, m_pSpace, ccp(JumpRockPoint_x, jumpRockHeight+rockHeight/2));
    jumpRock->setTag(mapIndex);
    m_objects.push_back(jumpRock);
}

void ObjectManager::removeObjectOfMap(int mapIndex)
{
    std::list<CCSprite *>::iterator itList;
    for (itList = m_objects.begin(); itList != m_objects.end();)
	{
        CCSprite *sprite = (CCSprite *)*itList;
        if(mapIndex == sprite->getTag())
		{
            sprite->removeFromParent();
            itList = m_objects.erase(itList);
        }
		else
		{
            itList++;
        }
    }
}

void ObjectManager::remove(CCSprite *obj)
{
    obj->removeFromParent();
    m_objects.remove(obj);
}
