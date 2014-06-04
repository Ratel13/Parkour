#include "Runner.h"
#include "MapManager.h"
#include "Constant.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace cocos2d::extension;


#define RUNING_MODE "running"

Runner* Runner::create(cpSpace* space)
{
    Runner *runner = new Runner(space);
    runner->autorelease();
    return runner;
}

Runner::Runner(cpSpace* space)
	: m_offsetPx(150.0)
{
    this->space = space;
    this->shape = NULL;

    this->initWithSpriteFrameName("runner0.png");
	
    CCPhysicsSprite* tmpSprite = CCPhysicsSprite::createWithSpriteFrameName("runnerCrouch0.png");
	m_runningSize = this->getContentSize();
	m_crouchSize = tmpSprite->getContentSize();
	m_state = RunnerStateRunning;
    
    initBody();
    initShape(RUNING_MODE);
	initAction();

    this->setCPBody(body);
    this->runAction(m_actionRunning);
}

Runner::~Runner()
{
    m_actionRunning->release();
    m_actionJumpUp->release();
    m_actionJumpDown->release();
    m_actionCrouch->release();

    cpShapeFree(shape);
	cpBodyFree(body);
}

void Runner::initBody()
{
	body = cpBodyNew(1, cpMomentForBox(1,this->m_runningSize.width, this->m_runningSize.height));
	body->p = cpv(m_offsetPx, MapManager::getGroundHeight() + this->m_runningSize.height / 2);
	body->v = cpv(150, 0);//run speed
	cpSpaceAddBody(space, body);
}

void Runner::initShape(const char* type)
{
	if (shape)
	{
		cpSpaceRemoveShape(space, shape);
	}

	if (0 == strcmp(type, RUNING_MODE))
	{
		shape = cpBoxShapeNew(body, m_runningSize.width-14, this->m_runningSize.height);
	}
	else
	{
		// crouch
		this->shape = cpBoxShapeNew(body, this->m_crouchSize.width, this->m_crouchSize.height);
	}

	cpSpaceAddShape(space, shape);
	cpShapeSetCollisionType(shape, SpriteTagrunner);
}

void Runner::initAction()
{
    //init runningAction
    CCArray *animFrames = CCArray::create();
    for (int i = 0; i < 8; i++)
    {
        CCString* name = CCString::createWithFormat("runner%d.png",i);
        CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        animFrames->addObject(frame);
    }
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1);
    m_actionRunning =CCRepeatForever::create(CCAnimate::create(animation));
    m_actionRunning->retain();

    // init jumpUpAction
    animFrames = CCArray::create();
    for (int i=0; i<4; i++)
	{
        CCString* name = CCString::createWithFormat("runnerJumpUp%d.png",i);
        CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        animFrames->addObject(frame);
    }
    animation = CCAnimation::createWithSpriteFrames(animFrames, 0.2);
	m_actionJumpUp = CCAnimate::create(animation);
	m_actionJumpUp->retain();

    // init jumpDownAction
    animFrames->removeAllObjects();
    for (int i=0; i<2; i++)
	{
        CCString *name = CCString::createWithFormat("runnerJumpDown%d.png",i);
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        animFrames->addObject(frame);
    }
    animation = CCAnimation::createWithSpriteFrames(animFrames, 0.3);
	m_actionJumpDown = CCAnimate::create(animation);
	m_actionJumpDown->retain();

    // init crouchAction
    animFrames->removeAllObjects();
    for (int i=0; i<1; i++)
	{
        CCString *name = CCString::createWithFormat("runnerCrouch%d.png",i);
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        animFrames->addObject(frame);
    }
    animation = CCAnimation::createWithSpriteFrames(animFrames, 0.3);
	m_actionCrouch = CCAnimate::create(animation);
	m_actionCrouch->retain();
}

void Runner::levelUp()
{
    //run faster
    cpBodyApplyImpulse(body, cpv(10, 0), cpv(0, 0));
}

void Runner::jump()
{
    if (m_state == RunnerStateRunning)
	{
        m_state = RunnerStateJumpUp;
        cpBodyApplyImpulse(body, cpv(0, 400), cpv(0, 0));
        this->stopAllActions();
        this->runAction(m_actionJumpUp);
        
        CocosDenshion::SimpleAudioEngine *audioEngine = CocosDenshion::SimpleAudioEngine::sharedEngine();
        audioEngine->playEffect("Sound/jump.mp3");
    }
}

void Runner::crouch()
{
    m_state = RunnerStateCrouch;
    this->initShape("crouch");
    this->stopAllActions();
    this->runAction(m_actionCrouch);
    this->scheduleOnce(schedule_selector(Runner::loadNormal), 1.5);
    CocosDenshion::SimpleAudioEngine *audioEngine = CocosDenshion::SimpleAudioEngine::sharedEngine();
    audioEngine->playEffect("Sound/crouch.mp3");
}

void Runner::loadNormal(float dt)
{
	initShape(RUNING_MODE);
	this->stopAllActions();
	this->runAction(m_actionRunning);
	m_state = RunnerStateRunning;
}

void Runner::step(float dt)
{
    cpVect vel = cpBodyGetVel(body);
    if (m_state == RunnerStateJumpUp)
	{
        if (vel.y < 0.1)
		{
            m_state = RunnerStateJumpDown;
            this->stopAllActions();
            this->runAction(m_actionJumpDown);
        }
        return;
    }
    if (m_state == RunnerStateJumpDown)
	{
        if (vel.y == 0)
		{
            m_state = RunnerStateRunning;
            this->stopAllActions();
            this->runAction(m_actionRunning);
        }
        return;
    }
}