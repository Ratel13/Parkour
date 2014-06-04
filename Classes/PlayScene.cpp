#include "PlayScene.h"
#include "Constant.h"
#include "MapManager.h"
#include "ObjectManager.h"
#include "Runner.h"
#include "StatusLayer.h"
#include "GameOverLayer.h"
#include "CBSimpleRecognizer.h"
#include "SimpleAudioEngine.h"
#include <limits>

using namespace cocos2d;
using namespace cocos2d::extension;

#ifndef MAX_FLOAT
#define MAX_FLOAT (std::numeric_limits<float>::max)()
#endif

#define NOTIFI_MEET_COIN "notification_meet_coin"
#define NOTIFI_MEET_ROCK "notification_meet_rock"

//c function for chipmunk
static void postStepRemove(cpSpace *m_space, cpShape *shape, void *param)
{
    ObjectManager *objectManager = (ObjectManager *)param;
    switch (shape->collision_type)
	{
        case SpriteTagcoin:
            CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFI_MEET_COIN);
            objectManager->remove((CCSprite *)shape->data);
            break;
        case SpriteTagrock:
            CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFI_MEET_ROCK);
            break;
        default:
            break;
    }
}

static int collisionBegin(cpArbiter *arb, cpSpace *m_space, void *param)
{
    //we get shapes here, so postStepRemove's second param is cpShape
    CP_ARBITER_GET_SHAPES(arb, a, b);
    cpSpaceAddPostStepCallback(m_space, (cpPostStepFunc)postStepRemove, b, param);
    return 0;
}


CCScene* PlayLayer::scene()
{
    CCScene *scene = CCScene::create();
    
    PlayLayer *playLayer = PlayLayer::create();
    playLayer->setTag(TAG_PLAYER);
    scene->addChild(playLayer);
    
    StatusLayer *statusLayer = StatusLayer::create();
    statusLayer->setTag(TAG_STATUSLAYER);
    scene->addChild(statusLayer);

    return scene;
}

PlayLayer::PlayLayer()
{

}

PlayLayer::~PlayLayer()
{
	delete m_mapManager;
	delete m_objectManager;
	delete m_recognizer;

	cpShapeFree(m_wallBottom);
	cpSpaceFree(m_space);
}

bool PlayLayer::init()
{
    if (!CCLayer::init())
	{
        return false;
    }
    
    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);

	m_lastEyeX = 0;

    m_recognizer = new CBSimpleRecognizer();
    
    //initPhysics, must init first
    m_space = cpSpaceNew();
    m_space->gravity = cpv(0, -200);

    m_wallBottom = cpSegmentShapeNew(m_space->staticBody, cpv(0, MapManager::getGroundHeight()), cpv(MAX_FLOAT, MapManager::getGroundHeight()), 0.0f);
    cpSpaceAddStaticShape(m_space, m_wallBottom);

    m_mapManager = new MapManager(this, m_space);
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("parkour.plist");
    m_batchNode = CCSpriteBatchNode::create("parkour.png");
    this->addChild(m_batchNode);
    
    m_runner = Runner::create(m_space);
    m_batchNode->addChild(m_runner);
    
    m_objectManager = new ObjectManager(m_batchNode, m_space);
    m_objectManager->initObjectOfMap(1, m_mapManager->getMapWidth());

    //must after objectManager inited
    cpSpaceAddCollisionHandler(m_space, SpriteTagrunner, SpriteTagcoin, collisionBegin, NULL, NULL, NULL, m_objectManager);
    cpSpaceAddCollisionHandler(m_space, SpriteTagrunner, SpriteTagrock, collisionBegin, NULL, NULL, NULL, m_objectManager);
    
    //make updater() to be called
    this->scheduleUpdate();
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(PlayLayer::notifiCoin), NOTIFI_MEET_COIN, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(PlayLayer::notifiRock), NOTIFI_MEET_ROCK, NULL);

    //CCPhysicsDebugNode是为了更方便debug的类，将它设置为显示之后，在场景内定义的精灵的碰撞形状块就显示出来了
	if (false)
	{
		CCPhysicsDebugNode* debugLayer = cocos2d::extension::CCPhysicsDebugNode::create(m_space);
		addChild(debugLayer, 100);
		debugLayer->setVisible(true);
	}

    return true;
}

bool PlayLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint pos = pTouch->getLocation();
    m_recognizer->beginPoint(pos.x, pos.y);
    return true;
}

void PlayLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint pos = pTouch->getLocation();
}

void PlayLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint pos = pTouch->getLocation();
    GestureDirection gestures = m_recognizer->endPoint(pos.x, pos.y);

    switch (gestures)
	{
	case kGestureDirectionUp:
		CCLOG("kGestureDirectionUp");
        m_runner->jump();
        break;
	case kGestureDirectionDown:
		CCLOG("kGestureDirectionDown");
        m_runner->crouch();
        break;
	default:
        break;
    }
}

void PlayLayer::onExit()
{
	CCLayer::onExit();
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, NOTIFI_MEET_COIN);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, NOTIFI_MEET_ROCK);
}

void PlayLayer::notifiCoin(CCObject *unuse)
{
    CocosDenshion::SimpleAudioEngine* audioEngine = CocosDenshion::SimpleAudioEngine::sharedEngine();
    audioEngine->playEffect("Sound/pickup_coin.mp3");
    StatusLayer* statusLayer = (StatusLayer*)getParent()->getChildByTag(TAG_STATUSLAYER);
    statusLayer->addCoin(1);
}

void PlayLayer::notifiRock(CCObject *unuse)
{
    GameOverLayer *gameoverLayer = GameOverLayer::create(ccc4(0, 0, 0, 180));
    gameoverLayer->setTag(TAG_GAMEOVER);
    getParent()->addChild(gameoverLayer);
    CCDirector::sharedDirector()->pause();
}

void PlayLayer::update(float dt)
{
    //chipmunk step
	int steps = 3;
	for(int i=0; i<steps; i++)
	{
		cpSpaceStep(m_space, dt);
	}
    
    
    //check and reload map
    if (true == m_mapManager->checkAndReload(m_lastEyeX))
	{
		m_objectManager->removeObjectOfMap(m_mapManager->getCurMap() - 1);
		m_objectManager->initObjectOfMap(m_mapManager->getCurMap() + 1, m_mapManager->getMapWidth());
        //level up
        m_runner->levelUp();
    }
    
    m_runner->step(dt);

    //move Camera
    m_lastEyeX = m_runner->getPositionX() - m_runner->getoffsetPx();
    CCCamera *camera = this->getCamera();
    float eyeZ = camera->getZEye();
    camera->setEyeXYZ(m_lastEyeX, 0, eyeZ);
    camera->setCenterXYZ(m_lastEyeX, 0, 0);
    
    StatusLayer *statusLayer = (StatusLayer*)getParent()->getChildByTag(TAG_STATUSLAYER);
    statusLayer->updateMeter(m_lastEyeX);
}

