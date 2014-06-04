#pragma once

#include "cocos2d.h"
#include "chipmunk.h"

class Map;

class MapManager
{
public:

	MapManager(cocos2d::CCLayer* parent, cpSpace* pSpace);

	~MapManager();

	static float getGroundHeight() {return 100.0;};

	float getMapWidth() {return m_spriteWidth;};

	int getCurMap() {return m_curMap;};

	bool checkAndReload(float eyeX);

private:
    cpSpace* m_space;

	Map* m_map0;

	Map* m_map1;

	int m_curMap;

    float m_spriteWidth;
};
