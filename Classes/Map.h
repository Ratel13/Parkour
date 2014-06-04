#pragma once

#include "cocos2d.h"


class Map : public cocos2d::CCSprite
{
public:
	Map(int index);
	~Map();

    static Map* create(int index);
    
    void reload(int index);

private:
    const char* getMapName(int index);

    const char* getGroundName(int index);
};
