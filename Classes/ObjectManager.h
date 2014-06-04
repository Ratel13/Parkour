#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "chipmunk.h"

class ObjectManager
{
public:
	ObjectManager(cocos2d::CCSpriteBatchNode* spriteSheet, cpSpace* space);
	~ObjectManager();

	void initObjectOfMap(int mapIndex, float mapWidth);

	void removeObjectOfMap(int mapIndex);

	void remove(cocos2d::CCSprite* obj);

private:
    cpSpace* m_pSpace;

    cocos2d::CCSpriteBatchNode* m_pSpriteSheet;

    std::list<cocos2d::CCSprite*> m_objects;
};

