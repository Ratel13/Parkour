#pragma once

#include "cocos2d.h"
#include "chipmunk.h"

class Runner;
class MapManager;
class ObjectManager;
class CBSimpleRecognizer;

enum
{
    TAG_STATUSLAYER = 10,
    TAG_GAMEOVER,
    TAG_PLAYER,
};

class PlayLayer : public cocos2d::CCLayer
{
public:
	PlayLayer();
	~PlayLayer();

	static cocos2d::CCScene* scene();

    CREATE_FUNC(PlayLayer);
    virtual bool init();
	virtual void onExit();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void update(float dt);

private:
	void notifiCoin(cocos2d::CCObject *unuse);
	void notifiRock(cocos2d::CCObject *unuse);
    
private:
    cpSpace* m_space;
    cpShape* m_wallBottom;

    cocos2d::CCSpriteBatchNode* m_batchNode;
    Runner* m_runner;

    MapManager* m_mapManager;
    ObjectManager* m_objectManager;

    float m_lastEyeX;
    
    cocos2d::CCPoint m_touchBeganPoint;
	cocos2d::CCPoint m_touchEndedPoint;
    std::list<cocos2d::CCPoint> m_pointList;
    
    CBSimpleRecognizer* m_recognizer;
};
