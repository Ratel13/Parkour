#include "MapManager.h"
#include "Map.h"
#include "Constant.h"

using namespace cocos2d;


MapManager::MapManager(CCLayer* parent, cpSpace* pSpace)
	: m_spriteWidth(0)
	, m_curMap(0)
{
    m_space = pSpace;

    m_map0 = Map::create(0);
	m_map1 = Map::create(1);
    parent->addChild(m_map0);
	parent->addChild(m_map1);

    m_spriteWidth = m_map0->getContentSize().width;
}

MapManager::~MapManager()
{
}

bool MapManager::checkAndReload(float eyeX)
{
    int newCur = eyeX / m_spriteWidth;

    if (m_curMap == newCur)
	{
        return false;
    }

    Map* currentMap = NULL;
    if (0 == newCur%2)
	{
        // change mapSecond
        currentMap = m_map1;
    }
	else
	{
        // change mapFirst
        currentMap = m_map0;
    }

    m_curMap = newCur;
    CCLOG("load map : %d",(newCur + 1));
    currentMap->reload(m_curMap + 1);

    return true;
}
